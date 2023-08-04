#include "E/EObjectItemModel.h"
namespace s21 {
EObjectItemModel::EObjectItemModel(QObject *parent)
    : QAbstractItemModel{parent} {
  root_item_ = new EObjectTreeItem({tr("Engine objects:")}, nullptr);
}

QModelIndex EObjectItemModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  EObjectTreeItem *parentItem;

  if (!parent.isValid())
    parentItem = root_item_;
  else
    parentItem = static_cast<EObjectTreeItem *>(parent.internalPointer());

  EObjectTreeItem *childItem = parentItem->child(row);
  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
}

QModelIndex EObjectItemModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  EObjectTreeItem *childItem =
      static_cast<EObjectTreeItem *>(index.internalPointer());
  EObjectTreeItem *parentItem = childItem->parentItem();

  if (parentItem == root_item_) return QModelIndex();
  if (parentItem == nullptr) return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

int EObjectItemModel::rowCount(const QModelIndex &parent) const {
  EObjectTreeItem *parentItem;
  if (parent.column() > 0) return 0;

  if (!parent.isValid())
    parentItem = root_item_;
  else
    parentItem = static_cast<EObjectTreeItem *>(parent.internalPointer());
  return parentItem->childCount();
}

int EObjectItemModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<EObjectTreeItem *>(parent.internalPointer())
        ->columnCount();
  return root_item_->columnCount();
}

Qt::ItemFlags EObjectItemModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}
QVariant EObjectItemModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return root_item_->data(section);

  return QVariant();
}

QVariant EObjectItemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());

  return item->data(index.column());
}

std::string EObjectItemModel::GetTitle(EObjectType type) {
  switch (type) {
    case kNone:
      return "";
      break;
    case kCamera:
      return (QString("Camera_") + QString().number(camera_ptrs_.size()))
          .toStdString();
      break;
    case kObject3D:
      return (QString("Object3D_") + QString().number(object3D_ptrs_.size()))
          .toStdString();
      break;
    case kTransform:
      return "Transform";
      break;
    case kMesh:
      return "Mesh";
      break;
  }
}
void EObjectItemModel::FindAndSelectIndex(const QModelIndex &index) {
  if (!index.isValid()) return;
  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());
  if (!item) return;
  auto obj_ptr = item->GetObjectPtr();

  if (camera_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
  if (transform_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
  if (mesh_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
  if (object3D_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
}

void EObjectItemModel::PrintIndexObject(const QModelIndex &index) {
  if (!index.isValid()) return;
  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());
  if (!item) return;
  qDebug() << "Type:" << item->GetType();
  auto obj_ptr = item->GetObjectPtr();
  if (all_objects_.contains(obj_ptr)) qDebug() << " Pointer" << obj_ptr;
}
void EObjectItemModel::AddItem(EObject *item, EObjectTreeItem *parent,
                               std::string title) {
  if (!item || item->GetType() == kNone) return;
  if (!parent) parent = root_item_;
  auto type = item->GetType();
  auto row = rowCount();
  string Title = title == "" ? GetTitle(type) : title;
  beginInsertRows(QModelIndex(), row + 1, row + 1);
  auto new_item = new EObjectTreeItem({tr(Title.c_str())}, item, parent);
  PushObjectInVectors(item);
  endInsertRows();
  if (type == kObject3D) {
    auto object3d = static_cast<Object3D *>(item);
    AddItem(&object3d->GetTrasform(), new_item);
    for (const auto &mesh : object3d->GetMeshes())
      AddItem(&*mesh, new_item, mesh->GetName());
  }
}

void EObjectItemModel::DeleteItem(EObjectTreeItem *item) {
  if (!item) return;
  if (item == root_item_) return;
  auto ptr = item->GetObjectPtr();
  if (!ptr) return;

  auto row = item->row();
  auto parent_ptr = item->parentItem();
  auto obj_ptr = item->GetObjectPtr();
  auto parent_index = QModelIndex();

  int delete_count = EObjectTreeItem::RecursiveChildCount(item);

  beginRemoveRows(parent_index, row, row + delete_count);
  parent_ptr->RemoveChild(item);
  if (all_objects_.contains(obj_ptr)) all_objects_.removeAll(obj_ptr);
  if (camera_ptrs_.contains(obj_ptr)) camera_ptrs_.removeAll(obj_ptr);
  if (object3D_ptrs_.contains(obj_ptr)) object3D_ptrs_.removeAll(obj_ptr);
  if (transform_ptrs_.contains(obj_ptr)) transform_ptrs_.removeAll(obj_ptr);
  delete item;
  endRemoveRows();
}

EObjectTreeItem *EObjectItemModel::FindItem(EObject *object) {
  if (!root_item_) return nullptr;
  return root_item_->RecursiveFindChildByPtr(object);
}
void EObjectItemModel::PushObjectInVectors(EObject *item) {
  if (!item) return;
  all_objects_ << item;
  switch (item->GetType()) {
    case kNone:
      return;
      break;
    case kCamera:
      camera_ptrs_ << static_cast<Camera *>(item);
      break;
    case kObject3D:
      object3D_ptrs_ << static_cast<Object3D *>(item);
      break;
    case kTransform:
      transform_ptrs_ << static_cast<Transform *>(item);
      break;
    case kMesh:
      mesh_ptrs_ << static_cast<Mesh *>(item);
      break;
  }
}
}  // namespace s21

#include "E/EObjectItemModel.h"

EObjectItemModel::EObjectItemModel(QObject *parent)
    : QAbstractItemModel{parent} {
  rootItem_ = new EObjectTreeItem({tr("Object")}, nullptr);
}

QModelIndex EObjectItemModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  EObjectTreeItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem_;
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

  if (parentItem == rootItem_) return QModelIndex();
  if (parentItem == nullptr) return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

int EObjectItemModel::rowCount(const QModelIndex &parent) const {
  EObjectTreeItem *parentItem;
  if (parent.column() > 0) return 0;

  if (!parent.isValid())
    parentItem = rootItem_;
  else
    parentItem = static_cast<EObjectTreeItem *>(parent.internalPointer());
  return parentItem->childCount();
}

int EObjectItemModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<EObjectTreeItem *>(parent.internalPointer())
        ->columnCount();
  return rootItem_->columnCount();
}

Qt::ItemFlags EObjectItemModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}
QVariant EObjectItemModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem_->data(section);

  return QVariant();
}

QVariant EObjectItemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());

  return item->data(index.column());
}

std::string EObjectItemModel::GetCameraTitle() {
  return (QString("Camera_") + QString().number(camera_ptrs_.size()))
      .toStdString();
}

std::string EObjectItemModel::GetObject3DTitle() {
  return (QString("Object3D_") + QString().number(object3D_ptrs_.size()))
      .toStdString();
}

std::string EObjectItemModel::GetTransformTitle() {
  return (QString("Transform_") + QString().number(transform_ptrs_.size()))
      .toStdString();
}

std::string EObjectItemModel::GetMeshTitle() {
  return (QString("Mesh_") + QString().number(mesh_ptrs_.size())).toStdString();
}

void EObjectItemModel::FindAndSelectIndex(const QModelIndex &index) {
  if (!index.isValid()) return;
  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());
  if (!item) return;
  auto obj_ptr = item->GetObjectPtr();

  if (camera_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
  if (transform_ptrs_.contains(obj_ptr)) emit ObjectSelected(obj_ptr);
}

void EObjectItemModel::PrintIndexObject(const QModelIndex &index) {
  if (!index.isValid()) return;
  EObjectTreeItem *item =
      static_cast<EObjectTreeItem *>(index.internalPointer());
  if (!item) return;
  qDebug() << "Type:" << item->GetType();
  auto obj_ptr = item->GetObjectPtr();
  try {
    if (mesh_ptrs_.contains(obj_ptr))
      qDebug() << " Pointer" << mesh_ptrs_.at(mesh_ptrs_.indexOf(obj_ptr));
    if (camera_ptrs_.contains(obj_ptr))
      qDebug() << " Pointer" << camera_ptrs_.at(camera_ptrs_.indexOf(obj_ptr));
    if (object3D_ptrs_.contains(obj_ptr))
      qDebug() << " Pointer"
               << object3D_ptrs_.at(object3D_ptrs_.indexOf(obj_ptr));
    if (transform_ptrs_.contains(obj_ptr))
      qDebug() << " Pointer"
               << transform_ptrs_.at(transform_ptrs_.indexOf(obj_ptr));
  } catch (...) {
  }
}

void EObjectItemModel::AddItem(Camera *item, EObjectTreeItem *parent) {
  if (!parent) parent = rootItem_;
  auto row = rowCount();
  beginInsertRows(QModelIndex(), row + 1, row + 1);

  new EObjectTreeItem({tr(GetCameraTitle().c_str())}, item, parent);
  camera_ptrs_ << item;
  endInsertRows();
}

void EObjectItemModel::AddItem(Object3D *item, EObjectTreeItem *parent) {
  if (!parent) parent = rootItem_;
  auto row = rowCount();
  beginInsertRows(QModelIndex(), row + 1, row + 1);

  auto new_item =
      new EObjectTreeItem({tr(GetObject3DTitle().c_str())}, item, parent);
  object3D_ptrs_ << item;
  endInsertRows();

  AddItem(&item->GetTrasform(), new_item);
  AddItem(&item->GetMesh(), new_item);
}

void EObjectItemModel::AddItem(Transform *item, EObjectTreeItem *parent) {
  if (!parent) parent = rootItem_;
  auto row = rowCount();
  beginInsertRows(QModelIndex(), row + 1, row + 1);

  new EObjectTreeItem({tr(GetTransformTitle().c_str())}, item, parent);
  transform_ptrs_ << item;
  endInsertRows();
}

void EObjectItemModel::AddItem(Mesh *item, EObjectTreeItem *parent) {
  if (!parent) parent = rootItem_;
  auto row = rowCount();
  beginInsertRows(QModelIndex(), row + 1, row + 1);
  new EObjectTreeItem({tr(GetMeshTitle().c_str())}, item, parent);
  mesh_ptrs_ << item;
  endInsertRows();
}

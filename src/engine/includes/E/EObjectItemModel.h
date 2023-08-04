#ifndef EOBJECTITEMMODEL_H
#define EOBJECTITEMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "EObjectTreeItem.h"
using std::string;
using std::vector;
namespace s21 {
class EObjectItemModel : public QAbstractItemModel {
  Q_OBJECT
  friend class Engine;

 public:
  explicit EObjectItemModel(QObject *parent = nullptr);
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  ~EObjectItemModel() {
    if (root_item_) delete root_item_;
  };
 signals:
  void ObjectSelected(s21::EObject *);
 public slots:
  void FindAndSelectIndex(const QModelIndex &index);
  void PrintIndexObject(const QModelIndex &index);
  void AddItem(s21::EObject *item, s21::EObjectTreeItem *parent = nullptr,
               std::string title = "");
  void DeleteItem(s21::EObjectTreeItem *item);
  EObjectTreeItem *FindItem(s21::EObject *object);
  void PushObjectInVectors(s21::EObject *item);

 private:
  QModelIndex FindParentIndex(EObjectTreeItem *item);
  EObjectTreeItem *root_item_;
  QVector<EObject *> all_objects_;
  QVector<Camera *> camera_ptrs_;
  QVector<Object3D *> object3D_ptrs_;
  QVector<Transform *> transform_ptrs_;
  QVector<Mesh *> mesh_ptrs_;

  std::string GetTitle(EObjectType type);
};
}  // namespace s21

#endif  // EOBJECTITEMMODEL_H

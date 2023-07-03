#ifndef EOBJECTITEMMODEL_H
#define EOBJECTITEMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "EObjectTreeItem.h"
using std::string;
using std::vector;
class EObjectItemModel : public QAbstractItemModel {
  Q_OBJECT
  friend class Engine;

 public:
  explicit EObjectItemModel(QObject *parent = nullptr);
  // Hold arrays of EObject* Camera* Object3D* and search for currently selected
  // ptr from EObjectTreeItem
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
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  ~EObjectItemModel() { delete root_item_; };
 signals:
  void ObjectSelected(EObject *);
 public slots:
  void FindAndSelectIndex(const QModelIndex &index);
  void PrintIndexObject(const QModelIndex &index);
  void AddItem(EObject *item, EObjectTreeItem *parent = nullptr);
  void PushObjectInVectors(EObject *item);

 private:
  EObjectTreeItem *root_item_;
  //  QVector<EObject*> all_objects;
  QVector<Camera *> camera_ptrs_;
  QVector<Object3D *> object3D_ptrs_;
  QVector<Transform *> transform_ptrs_;
  QVector<Mesh *> mesh_ptrs_;

  std::string GetTitle(EObjectType type);
};

#endif  // EOBJECTITEMMODEL_H

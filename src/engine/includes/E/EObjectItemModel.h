#ifndef EOBJECTITEMMODEL_H
#define EOBJECTITEMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "EObjectTreeItem.h"
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
  ~EObjectItemModel() { delete rootItem_; };
  std::string GetCameraTitle();
  std::string GetObject3DTitle();
  std::string GetTransformTitle();
  std::string GetMeshTitle();
 signals:
  void ObjectSelected(EObject *);
 public slots:
  void FindAndSelectIndex(const QModelIndex &index);
  void PrintIndexObject(const QModelIndex &index);
  void AddItem(Camera *item, EObjectTreeItem *parent = nullptr);
  void AddItem(Object3D *item, EObjectTreeItem *parent = nullptr);
  void AddItem(Transform *item, EObjectTreeItem *parent = nullptr);
  void AddItem(Mesh *item, EObjectTreeItem *parent = nullptr);

 private:
  EObjectTreeItem *rootItem_;
  //  QVector<EObject*> all_objects;
  QVector<Camera *> camera_ptrs_;
  QVector<Object3D *> object3D_ptrs_;
  QVector<Transform *> transform_ptrs_;
  QVector<Mesh *> mesh_ptrs_;
};

#endif  // EOBJECTITEMMODEL_H

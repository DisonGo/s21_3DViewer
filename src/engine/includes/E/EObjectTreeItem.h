#ifndef EOBJECTTREEITEM_H
#define EOBJECTTREEITEM_H
#include "E/Camera.h"
#include "E/Object3D.h"
#include "E/Transform.h"
#include "Spacers/CameraSpacer.h"
#include "Spacers/TransformSpacer.h"

class EObjectTreeItem {
 public:
  explicit EObjectTreeItem(const QList<QVariant> &data, EObject *object,
                           EObjectTreeItem *parent = nullptr);
  ~EObjectTreeItem();

  void appendChild(EObjectTreeItem *child);

  EObjectTreeItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  void SetParent(EObjectTreeItem *parent = nullptr);
  void RemoveChild(EObjectTreeItem *child);
  EObject *GetObjectPtr() { return object_ptr_; };
  int row() const;
  EObjectTreeItem *parentItem();
  EObjectType GetType() { return type_; };

 private:
  QList<EObjectTreeItem *> m_childItems;
  QList<QVariant> m_itemData;
  EObject *object_ptr_;
  EObjectType type_ = kNone;
  EObjectTreeItem *m_parentItem;
};

#endif  // EOBJECTTREEITEM_H

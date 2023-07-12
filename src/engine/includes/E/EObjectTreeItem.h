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

  void AppendChild(EObjectTreeItem *child);

  int childCount() const;
  static int RecursiveChildCount(EObjectTreeItem* item);
  int columnCount() const;
  int row() const;
  void SetParent(EObjectTreeItem *parent = nullptr);
  void RemoveChild(EObjectTreeItem *child);
  EObject *GetObjectPtr() { return object_ptr_; };
  QVariant data(int column) const;
  EObjectType GetType() { return type_; };
  EObjectTreeItem *child(int row);
  EObjectTreeItem *parentItem();
  void SetData(QList<QVariant>& data);

 private:
  QList<EObjectTreeItem *> m_child_items_;
  QList<QVariant> m_item_data_;
  EObject *object_ptr_;
  EObjectType type_ = kNone;
  EObjectTreeItem *m_parent_item_;
};

#endif  // EOBJECTTREEITEM_H

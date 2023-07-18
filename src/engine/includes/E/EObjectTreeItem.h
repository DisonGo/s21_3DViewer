#ifndef EOBJECTTREEITEM_H
#define EOBJECTTREEITEM_H
#include "E/Camera.h"
#include "E/Object3D.h"
#include "E/Transform.h"
#include "Spacers/CameraSpacer.h"
#include "Spacers/TransformSpacer.h"
namespace s21 {
class EObjectTreeItem {
 public:
  explicit EObjectTreeItem(const QList<QVariant> &data, EObject *object,
                           EObjectTreeItem *parent = nullptr);
  ~EObjectTreeItem();

  void AppendChild(EObjectTreeItem *child);

  EObjectTreeItem *child(int row);
  int childCount() const;
  static int RecursiveChildCount(EObjectTreeItem *item);
  int columnCount() const;
  QVariant data(int column) const;
  void SetParent(EObjectTreeItem *parent = nullptr);
  void RemoveChild(EObjectTreeItem *child);
  EObject *GetObjectPtr() { return object_ptr_; };
  EObjectTreeItem *RecursiveFindChildByPtr(EObject *object);
  int row() const;
  EObjectTreeItem *parentItem();
  EObjectType GetType() { return type_; };

 private:
  QList<EObjectTreeItem *> m_child_items_;
  QList<QVariant> m_item_data_;
  EObject *object_ptr_;
  EObjectType type_ = kNone;
  EObjectTreeItem *m_parent_item_;
};
}  // namespace s21

#endif  // EOBJECTTREEITEM_H

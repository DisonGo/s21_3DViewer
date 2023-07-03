#include "E/EObjectTreeItem.h"

EObjectTreeItem::EObjectTreeItem(const QList<QVariant> &data, EObject *object,
                                 EObjectTreeItem *parent)
    : m_item_data_(data), object_ptr_(object), m_parent_item_(parent) {
  if (object_ptr_) type_ = object->GetType();
  if (m_parent_item_) m_parent_item_->AppendChild(this);
}

EObjectTreeItem::~EObjectTreeItem() { qDeleteAll(m_child_items_); }

void EObjectTreeItem::AppendChild(EObjectTreeItem *item) {
  m_child_items_.append(item);
}

EObjectTreeItem *EObjectTreeItem::child(int row) {
  if (row < 0 || row >= m_child_items_.size()) return nullptr;
  return m_child_items_.at(row);
}

int EObjectTreeItem::childCount() const { return m_child_items_.count(); }

int EObjectTreeItem::row() const {
  if (m_parent_item_)
    return m_parent_item_->m_child_items_.indexOf(
        const_cast<EObjectTreeItem *>(this));

  return 0;
}

int EObjectTreeItem::columnCount() const { return m_item_data_.count(); }

QVariant EObjectTreeItem::data(int column) const {
  if (column < 0 || column >= m_item_data_.size()) return QVariant();
  return m_item_data_.at(column);
}

void EObjectTreeItem::SetParent(EObjectTreeItem *parent) {
  if (m_parent_item_) m_parent_item_->RemoveChild(this);
  m_parent_item_ = parent;
  if (m_parent_item_) m_parent_item_->AppendChild(this);
}

void EObjectTreeItem::RemoveChild(EObjectTreeItem *child) {
  if (m_child_items_.contains(child)) m_child_items_.removeAll(child);
}

EObjectTreeItem *EObjectTreeItem::parentItem() { return m_parent_item_; }

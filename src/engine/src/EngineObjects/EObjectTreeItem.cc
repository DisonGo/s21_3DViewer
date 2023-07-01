#include "E/EObjectTreeItem.h"

EObjectTreeItem::EObjectTreeItem(const QList<QVariant> &data, EObject *object,
                                 EObjectTreeItem *parent)
    : m_itemData(data), object_ptr_(object), m_parentItem(parent) {
  if (object_ptr_) type_ = object->GetType();
  if (m_parentItem) m_parentItem->appendChild(this);
}

EObjectTreeItem::~EObjectTreeItem() { qDeleteAll(m_childItems); }

void EObjectTreeItem::appendChild(EObjectTreeItem *item) {
  m_childItems.append(item);
}

EObjectTreeItem *EObjectTreeItem::child(int row) {
  if (row < 0 || row >= m_childItems.size()) return nullptr;
  return m_childItems.at(row);
}

int EObjectTreeItem::childCount() const { return m_childItems.count(); }

int EObjectTreeItem::row() const {
  if (m_parentItem)
    return m_parentItem->m_childItems.indexOf(
        const_cast<EObjectTreeItem *>(this));

  return 0;
}

int EObjectTreeItem::columnCount() const { return m_itemData.count(); }

QVariant EObjectTreeItem::data(int column) const {
  if (column < 0 || column >= m_itemData.size()) return QVariant();
  return m_itemData.at(column);
}

void EObjectTreeItem::SetParent(EObjectTreeItem *parent) {
  if (m_parentItem) m_parentItem->RemoveChild(this);
  m_parentItem = parent;
  if (m_parentItem) m_parentItem->appendChild(this);
}

void EObjectTreeItem::RemoveChild(EObjectTreeItem *child) {
  if (m_childItems.contains(child)) m_childItems.removeAll(child);
}

EObjectTreeItem *EObjectTreeItem::parentItem() { return m_parentItem; }

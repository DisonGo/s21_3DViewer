#include "EobjectItemModel.h"

EObjectItemModel::EObjectItemModel(QObject *parent)
    : QAbstractItemModel{parent} {}

QModelIndex EObjectItemModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  return parent.sibling(row, column);
}

QModelIndex EObjectItemModel::parent(const QModelIndex &index) const {
  return index.parent();
}

int EObjectItemModel::rowCount(const QModelIndex &parent) const {
  if (!indices.contains(parent)) return 0;
}

int EObjectItemModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant EObjectItemModel::data(const QModelIndex &index, int role) const {
  
}

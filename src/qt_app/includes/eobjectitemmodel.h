#ifndef EOBJECTITEMMODEL_H
#define EOBJECTITEMMODEL_H

#include <QAbstractItemModel>

class EObjectItemModel : public QAbstractItemModel
{
public:
  explicit EObjectItemModel(QObject *parent = nullptr);

  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
  int uind = 0;
  QList<QModelIndex> indices;
};

#endif // EOBJECTITEMMODEL_H

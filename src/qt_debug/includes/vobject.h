#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>
#include <QVector>
#include <QMatrix4x4>
class VObject : public QObject
{
  Q_OBJECT
public:
  explicit VObject(QObject *parent = nullptr);
signals:
private:
  QMatrix4x4 model;
};

#endif // VOBJECT_H

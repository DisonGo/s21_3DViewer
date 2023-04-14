#pragma once
#include <QVector3D>
struct Transform{
    QVector3D translate = QVector3D(0,0,0);
    QVector3D rotation = QVector3D(0,0,0);
    QVector3D scale = QVector3D(1,1,1);
    bool operator==(Transform a) const {
      return (translate == a.translate &&
          rotation == a.rotation &&
          scale == a.scale);
    }
};

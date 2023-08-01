#ifndef IMAGESAVER_H
#define IMAGESAVER_H

#include <qgifimage.h>
#include <qtmetamacros.h>

#include <QFileDialog>
#include <QImage>
#include <vector>
namespace s21 {
class ImageSaver {
 public:
  ImageSaver() {
    QString user_name_ = qgetenv("USER");
    if (user_name_.isEmpty()) user_name_ = qgetenv("USERNAME");
  }
  void SaveGif(std::vector<QImage> gifData, QSize resolution, unsigned FPS) {
    QGifImage gif(resolution);
    gif.setDefaultDelay(1000 / FPS);

    for (auto& frame : gifData) gif.addFrame(frame);

    QString save_path = QFileDialog::getSaveFileName(
        nullptr, "Save gif", "/Users/" + user_name_, "GIF (*.gif)");
    if (save_path.isEmpty()) return;
    gif.save(save_path);
  }
  void SaveScreenShot(QImage data) {
    QString save_path = QFileDialog::getSaveFileName(
        nullptr, "Save screenshot", "/Users/" + user_name_,
        "BMP Files (*.bmp);;JPEG Files (*.jpg)");
    if (save_path.isEmpty()) return;
    data.save(save_path);
  }

 private:
  QString user_name_ = "";
};
}  // namespace s21

#endif  // IMAGESAVER_H

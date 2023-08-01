#ifndef IMAGESAVERCONTROLER_H
#define IMAGESAVERCONTROLER_H
#include "ImageSaver.h"
namespace s21 {
class ImageSaverControler {
 public:
  ImageSaverControler(ImageSaver& saver) : saver_(saver){};
  void SaveGif(std::vector<QImage> gifData, QSize resolution, unsigned FPS) {
    saver_.SaveGif(gifData, resolution, FPS);
  };
  void SaveScreenShot(QImage data) { saver_.SaveScreenShot(data); }

 private:
  ImageSaver& saver_;
};
}  // namespace s21
#endif  // IMAGESAVERCONTROLER_H

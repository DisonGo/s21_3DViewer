#ifndef ENGINESPACER_H
#define ENGINESPACER_H
#include <Engine.h>
namespace s21 {
class EngineSpacer : public QObject {
  Q_OBJECT
 public:
  EngineSpacer(Engine& engine, QObject* parent = nullptr)
      : QObject(parent), engine_(engine){};
  void InitializeEngine();
  void RequestRenderCycle();
  void ImportOBJFile(std::string file_path);
  EObjectItemModel& GetEObjectItemModel();
  Camera* GetCurrentCamera();
  void SetCurrentCamera(Camera* camera);
 signals:
  void ConfigUpdated();
  void ObjectImported(unsigned long vertices_n, unsigned long indices_n,
                      std::string file_name);

 private:
  Engine& engine_;
};
}  // namespace s21
#endif  // ENGINESPACER_H

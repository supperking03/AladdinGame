#ifndef __EDITOR_CONTROLLER__
#define __EDITOR_CONTROLLER__

#include "core/GameObjectComponent.h"
#include "physics/Rigidbody.h"

ALA_CLASS_HEADER_1(EditorController, ala::GameObjectComponent)
private:
  int _currentIndex;
  std::vector<ala::GameObject*> _gameObjects;
  ala::Transform* _camera;
  ala::Logger _logger;
public:
  EditorController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~EditorController();
  void setGameObjects(const std::vector<ala::GameObject*>& gameObjects);
  void onInitialize() override;
  void onUpdate(const float delta) override;
};

#endif //!__EDITOR_CONTROLLER__

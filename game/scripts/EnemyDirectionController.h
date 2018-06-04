#ifndef __ENEMY_DIRECTION_CONTROLLER_H__
#define __ENEMY_DIRECTION_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(EnemyDirectionController, ala::GameObjectComponent)
private:
  int _directionScalar;

  ala::Transform* _transform;
  ala::Rigidbody* _body;

  ala::Transform* _aladdinTransform;
public:
  EnemyDirectionController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~EnemyDirectionController();

  bool isLeft() const;
  bool isRight() const;
  void setDirectionScalar(const int directionScalar);
  void setLeft();
  void setRight();
  void turn();

  int getAladdinDirection() const;

  void onInitialize() override;
};

#endif //!__ENEMY_DIRECTION_CONTROLLER_H__

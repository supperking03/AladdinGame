#ifndef __ALADDIN_CONTROLLER_H__
#define __ALADDIN_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AladdinController, ala::GameObjectComponent)
private:
  int _horizontalDirectionScalar;
  int _verticalDirectionScalar;

  bool _isHorizontalDirectionScalarChecking;
  bool _isVerticalDirectionScalarChecking;

  ala::Rigidbody* _body;

  ala::Collider* _collidingRope;
  ala::Collider* _collidingHanger;

  ala::StateManager* _stateManager;
  ala::ActionManager* _actionManager;

  bool _isCollidingGround;
  bool _isCollidingWallLeft;
  bool _isCollidingWallRight;
  bool _isCollidingRope;
  bool _isCollidingHanger;
  bool _isHoldingJump;

  int _health;

  bool _isRecovering;
  bool _isHit;

  ala::Transform* _jafar;
  ala::Transform* _transform;
public:
  AladdinController(ala::GameObject* gameObject,const int initialDirectionScalar = 1, const std::string& name = "");
  virtual ~AladdinController();

  int getHorizontalDirectionScalar() const;
  int getVerticalDirectionScalar() const;

  bool isHorizontalDirectionScalarActivated() const;
  void activateHorizontalDirectionScalarChecking();
  void deactivateHorizontalDirectionScalarChecking();

  bool isVerticalDirectionScalarActivated() const;
  void activateVerticalDirectionScalarChecking();
  void deactivateVerticalDirectionScalarChecking();
  void throwApple() const;

  void onInitialize() override;
  void onUpdate(const float delta) override;

  void onCollisionEnter(const ala::CollisionInfo& collision) override;
  void onCollisionStay(const ala::CollisionInfo& collision) override;
  void onCollisionExit(const ala::CollisionInfo& collision) override;
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerStay(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;
  bool isCollidingGround() const;
  bool isCollidingWallLeft() const;
  bool isCollidingWallRight() const;
  bool isCollidingRope() const;
  bool isCollidingHanger() const;

  void checkJump();
  bool isHoldingJump() const;

  bool isHit() const;

  void resetHit();

  ala::Collider* getCollidingRope() const;
  ala::Collider* getCollidingHanger() const;
};

#endif __ALADDIN_CONTROLLER_H__
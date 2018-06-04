#include "AladdinController.h"
#include "../GameData.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"
#include "WeaponController.h"
#include "extra/WaitForSeconds.h"

ALA_CLASS_SOURCE_1(AladdinController, ala::GameObjectComponent)

AladdinController::AladdinController(ala::GameObject* gameObject, const int initialScalar,const std::string& name)
  :GameObjectComponent(gameObject, name),
  _horizontalDirectionScalar(initialScalar),
  _verticalDirectionScalar(1),
  _isHorizontalDirectionScalarChecking(true),
  _isVerticalDirectionScalarChecking(false),
  _body(NULL),
  _collidingRope(NULL),
  _collidingHanger(NULL),
  _stateManager(NULL),
  _actionManager(NULL),
  _isCollidingGround(false),
  _isCollidingWallLeft(false),
  _isCollidingWallRight(false),
  _isCollidingRope(false),
  _isCollidingHanger(false),
  _isHoldingJump(false),
  _health(0),
  _isRecovering(false),
  _isHit(false),
  _jafar(NULL),
  _transform(NULL)
{
}

AladdinController::~AladdinController()
{
}

int AladdinController::getHorizontalDirectionScalar() const
{
  return _horizontalDirectionScalar;
}

int AladdinController::getVerticalDirectionScalar() const
{
  return _isVerticalDirectionScalarChecking;
}

bool AladdinController::isVerticalDirectionScalarActivated() const
{
  return _isVerticalDirectionScalarChecking;
}

void AladdinController::activateVerticalDirectionScalarChecking()
{
  _isVerticalDirectionScalarChecking = true;
}

void AladdinController::deactivateVerticalDirectionScalarChecking()
{
  _isVerticalDirectionScalarChecking = false;
}

bool AladdinController::isHorizontalDirectionScalarActivated() const
{
  return _isHorizontalDirectionScalarChecking;
}

void AladdinController::activateHorizontalDirectionScalarChecking()
{
  _isHorizontalDirectionScalarChecking = true;
}

void AladdinController::deactivateHorizontalDirectionScalarChecking()
{
  _isHorizontalDirectionScalarChecking = false;
}

void AladdinController::onUpdate(const float delta)
{
  const auto input = ala::Input::get();
  if(_isHoldingJump && !input->getKey("d"))
  {
    _isHoldingJump = false;
  }
  if(_isHorizontalDirectionScalarChecking)
  {
    if(input->getKey(ALA_KEY_LEFT_ARROW))
    {
      _horizontalDirectionScalar = -1;
      getGameObject()->getTransform()->setScaleX(-1);
      _body->setVelocity(ala::Vec2(-abs(_body->getVelocity().getX()), _body->getVelocity().getY()));
    }
    else if(input->getKey(ALA_KEY_RIGHT_ARROW))
    {
      _horizontalDirectionScalar = 1;
      getGameObject()->getTransform()->setScaleX(1);
      _body->setVelocity(ala::Vec2(abs(_body->getVelocity().getX()), _body->getVelocity().getY()));
    }
  }
  if (_isVerticalDirectionScalarChecking)
  {
    if (input->getKey(ALA_KEY_DOWN_ARROW))
    {
      _horizontalDirectionScalar = -1;
      _body->setVelocity(ala::Vec2(_body->getVelocity().getX(), -abs(_body->getVelocity().getY())));
    }
    else if (input->getKey(ALA_KEY_UP_ARROW))
    {
      _horizontalDirectionScalar = 1;
      _body->setVelocity(ala::Vec2(_body->getVelocity().getX(), abs(_body->getVelocity().getY())));
    }
  }
}

void AladdinController::onCollisionEnter(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG)
  {
    if (collision.getNormal().getY() > 0.1f)
    {
      _isCollidingGround = true;
    }
  }
  else if (collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG)
  {
    if (collision.getNormal().getY() < -0.1f)
    {
      _isCollidingGround = true;
    }
  }
  if (collision.getColliderA()->getGameObject()->getTag() == WALL_TAG || collision.getColliderB()->getGameObject()->getTag() == WALL_TAG)
  {
    if (collision.getColliderA()->getTag() == ALADDIN_TAG)
    {
      if (collision.getNormal().getY() == 0)
      {
        if (collision.getNormal() == ala::Vec2(1,0))
        {
          _isCollidingWallLeft = true;
        }
        else
        {
          _isCollidingWallRight = true;
        }
      }
    }
    else
    {
      if (collision.getNormal().getY() == 0)
      {
        if (collision.getNormal() == ala::Vec2(-1, 0))
        {
          _isCollidingWallLeft = true;
        }
        else
        {
          _isCollidingWallRight = true;
        }
      }
    }
  }
}

void AladdinController::onCollisionStay(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG)
  {
    if (collision.getNormal().getY() > 0.1f)
    {
      _isCollidingGround = true;
    }
  }
  else if (collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG)
  {
    if (collision.getNormal().getY() < -0.1f)
    {
      _isCollidingGround = true;
    }
  }
    
  if (collision.getColliderA()->getGameObject()->getTag() == WALL_TAG || collision.getColliderB()->getGameObject()->getTag() == WALL_TAG)
  {
    if (collision.getColliderA()->getTag() == ALADDIN_TAG)
    {
      if (collision.getNormal().getY() == 0)
      {
        if (collision.getNormal() == ala::Vec2(1, 0))
        {
          _isCollidingWallLeft = true;
        }
        else
        {
          _isCollidingWallRight = true;
        }
      }
    }
    else
    {
      if (collision.getNormal().getY() == 0)
      {
        if (collision.getNormal() == ala::Vec2(-1, 0))
        {
          _isCollidingWallLeft = true;
        }
        else
        {
          _isCollidingWallRight = true;
        }
      }
    }
  }
}

void AladdinController::onCollisionExit(const ala::CollisionInfo& collision)
{
  if(collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG || collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG)
    _isCollidingGround = false;
  if (collision.getColliderA()->getGameObject()->getTag() == WALL_TAG || collision.getColliderB()->getGameObject()->getTag() == WALL_TAG)
  {
    _isCollidingWallLeft = false;
    _isCollidingWallRight = false;
  }
}

void AladdinController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderB() : collision.getColliderA();
  const auto selfCollider = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderA() : collision.getColliderB();

  if (otherCollider->getTag() == ENEMY_WEAPON_TAG && selfCollider->getTag() == ALADDIN_TAG)
  {
    if (_isRecovering || _isHit) return;

    const auto weapon = otherCollider->getGameObject()->getComponentT<WeaponController>();

    if (weapon->getType() == WEAPON_TYPE_ENEMY_STEAL)
    {
      _isHit = true;

      _isRecovering = true;

      ala::GameManager::get()->getGlobalMessenger()->broadcast(APPLE_STOLEN_MESSAGE, new IntArg(weapon->getDamage()));

      _actionManager->play(new ala::Sequence({
        new ala::WaitForSeconds(0.5f),
        new ala::CallFunc([this] {
        _isRecovering = false;
        _isHit = false;
      })
      }));
    }
    else if (weapon->getType() == WEAPON_TYPE_ENEMY_SPELL)
    {
      if(!_jafar)
      {
        _jafar = ala::GameManager::get()->getObjectByTag(JAFAR_TAG)->getTransform();
      }
      _body->addVelocity(ala::Vec2(weapon->getDamage() * (_transform->getPositionX() - _jafar->getPositionX()) / abs(_transform->getPositionX() - _jafar->getPositionX()), 0));
    }
    else
    {
      _isHit = true;

      _isRecovering = true;

      ala::GameManager::get()->getGlobalMessenger()->broadcast(HEALTH_LOST_MESSAGE, new IntArg(1));

      _actionManager->play(new ala::Sequence({
        new ala::Blink(0.05f, 10),
        new ala::CallFunc([this] {
        _isRecovering = false;
        _isHit = false;
      })
      }));
    }
    return;
  }
  if ((collision.getColliderA()->getTag() == ROPE_CHECKER_TAG && collision.getColliderB()->getTag() == ROPE_TAG) ||
    (collision.getColliderB()->getTag() == ROPE_CHECKER_TAG && collision.getColliderA()->getTag() == ROPE_TAG))
  {
    if(collision.getColliderB()->getGameObject()->getTag() == ROPE_TAG)
    {
      _collidingRope = collision.getColliderB();
    }
    else
    {
      _collidingRope = collision.getColliderA();
    }
    _isCollidingRope = true;
  }

  if ((collision.getColliderA()->getTag() == HANGER_CHECKER_TAG && collision.getColliderB()->getTag() == HANGER_TAG) ||
    (collision.getColliderB()->getTag() == HANGER_CHECKER_TAG && collision.getColliderA()->getTag() == HANGER_TAG))
  {
    if (collision.getColliderB()->getGameObject()->getTag() == HANGER_TAG)
    {
      _collidingHanger = collision.getColliderB();
    }
    else
    {
      _collidingHanger = collision.getColliderA();
    }
    _isCollidingHanger = true;
  }
}

void AladdinController::onTriggerStay(const ala::CollisionInfo& collision)
{
  if ((collision.getColliderA()->getTag() == ROPE_CHECKER_TAG && collision.getColliderB()->getTag() == ROPE_TAG) ||
    (collision.getColliderB()->getTag() == ROPE_CHECKER_TAG && collision.getColliderA()->getTag() == ROPE_TAG))
  {
    _isCollidingRope = true;
  }
  if ((collision.getColliderA()->getTag() == HANGER_CHECKER_TAG && collision.getColliderB()->getTag() == HANGER_TAG) ||
    (collision.getColliderB()->getTag() == HANGER_CHECKER_TAG && collision.getColliderA()->getTag() == HANGER_TAG))
  {
    _isCollidingHanger = true;
  }
}

void AladdinController::onTriggerExit(const ala::CollisionInfo& collision)
{
  if ((collision.getColliderA()->getTag() == ROPE_CHECKER_TAG && collision.getColliderB()->getTag() == ROPE_TAG) ||
    (collision.getColliderB()->getTag() == ROPE_CHECKER_TAG && collision.getColliderA()->getTag() == ROPE_TAG))
  {
    _isCollidingRope = false;
  }

  if ((collision.getColliderA()->getTag() == HANGER_CHECKER_TAG && collision.getColliderB()->getTag() == HANGER_TAG) ||
    (collision.getColliderB()->getTag() == HANGER_CHECKER_TAG && collision.getColliderA()->getTag() == HANGER_TAG))
  {
    _isCollidingHanger = false;
  }
}

bool AladdinController::isCollidingGround() const
{
  return _isCollidingGround;
}

bool AladdinController::isCollidingWallLeft() const
{
  return _isCollidingWallLeft;
}

bool AladdinController::isCollidingWallRight() const
{
  return _isCollidingWallRight;
}

bool AladdinController::isCollidingRope() const
{
  return _isCollidingRope;
}

bool AladdinController::isCollidingHanger() const
{
  return _isCollidingHanger;
}

void AladdinController::checkJump()
{
  _isHoldingJump = true;
}

bool AladdinController::isHoldingJump() const
{
  return _isHoldingJump;
}

bool AladdinController::isHit() const
{
  return _isHit;
}

void AladdinController::resetHit()
{
  _isHit = false;
}

ala::Collider* AladdinController::getCollidingRope() const
{
  return _collidingRope;
}

ala::Collider* AladdinController::getCollidingHanger() const
{
  return _collidingHanger;
}

void AladdinController::throwApple() const
{
  if(GameData::get()->getInt(APPLE_DATA_KEY)<=0)
  {
    return;
  }

  ala::GameManager::get()->getGlobalMessenger()->broadcast(APPLE_THROWED_MESSAGE, NULL);

  const auto apple = ala::GameManager::get()->getPrefab("Throwing Apple")->instantiate();
  apple->getTransform()->setPosition(getGameObject()->getTransform()->getPositionX() + _horizontalDirectionScalar * 50,
    getGameObject()->getTransform()->getPositionY() + 25);
  apple->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(500 * _horizontalDirectionScalar, 0));
}

void AladdinController::onInitialize()
{
  _body = getGameObject()->getComponentT<ala::Rigidbody>();
  _stateManager = getGameObject()->getComponentT<ala::StateManager>();
  _actionManager = getGameObject()->getComponentT<ala::ActionManager>();
  _transform = getGameObject()->getTransform();
}

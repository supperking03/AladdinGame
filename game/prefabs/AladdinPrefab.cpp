#include "AladdinPrefab.h"
#include <stdlib.h>
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "../../aladdin/core/GameManager.h"
#include "extra/Timer.h"
#include "../Macros.h"
#include "../scripts/AladdinController.h"
#include "../GameData.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"
#include "../Macros.h"

void AladdinPrefab::doInstantiate(ala::GameObject * object) const
{
  const auto gameManager = ala::GameManager::get();

  const auto input = ala::Input::get();
  const auto swordOffset5 = ala::Vec2(-35, 20);
  const auto swordSize5 = ala::Size(25, 40);
  const auto swordOffset6 = ala::Vec2(35, 25);
  const auto swordSize6 = ala::Size(35, 45);

  new ala::ActionManager(object);

  new ala::SpriteRenderer(object, "aladdin.png");
  const auto animator = new ala::Animator(object, "idle1", "aladdin.anm");

  const auto aladdinController = new AladdinController(object, 1, "Aladdin Controller");

  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);
  const auto collider = new ala::Collider(object, false, ala::Vec2(0, 0), ala::Size(40, 50));
  new ala::ColliderRenderer(collider);
  collider->setTag(ALADDIN_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);

  const auto swordCollider = new ala::Collider(object, true, ala::Vec2(), ala::Size(0, 0), 0);
  swordCollider->setTag(ALADDIN_WEAPON_TAG);
  swordCollider->ignoreTag(ALADDIN_TAG);
  swordCollider->setActive(false);
  new ala::ColliderRenderer(swordCollider);

  const auto ropeChecker = new ala::Collider(object, true, ala::Vec2(), ala::Size(5, 50), 0);
  ropeChecker->setTag(ROPE_CHECKER_TAG);
  ropeChecker->ignoreTag(ALADDIN_TAG);
  ropeChecker->ignoreTag(ENEMY_WEAPON_TAG);
  ropeChecker->ignoreTag(ENEMY_TAG);
  ropeChecker->ignoreTag(ALADDIN_WEAPON_TAG);
  new ala::ColliderRenderer(ropeChecker);

  const auto hangerChecker = new ala::Collider(object, true, ala::Vec2(0,40), ala::Size(40, 2), 0);
  hangerChecker->setTag(HANGER_CHECKER_TAG);
  hangerChecker->ignoreTag(ALADDIN_TAG);
  hangerChecker->ignoreTag(GROUND_TAG);
  hangerChecker->ignoreTag(COLLECTABLE_ITEM_TAG);
  hangerChecker->ignoreTag(ROPE_TAG);
  hangerChecker->ignoreTag(ENEMY_WEAPON_TAG);
  hangerChecker->ignoreTag(ENEMY_TAG);
  hangerChecker->ignoreTag(ALADDIN_WEAPON_TAG);
  hangerChecker->ignoreTag(ROPE_CHECKER_TAG);
  new ala::ColliderRenderer(hangerChecker);

  const auto idleTimer = new ala::Timer(object);
  const auto jumpTimer = new ala::Timer(object);
  const auto dashTimer = new ala::Timer(object);
  const auto appleTimer = new ala::Timer(object);
  const auto swordTimer = new ala::Timer(object);
  const auto stateManager = new ala::StateManager(object, "stand");

  const auto transform = object->getTransform();

  object->setTag(ALADDIN_TAG);
  object->setLayer("Character");

  new WeaponController(object, WEAPON_TYPE_ALADDIN_SWORD, 2);

  new ala::State(stateManager, "stand",
    [=] {
    animator->setAction("idle1");
    body->setVelocity(ala::Vec2(0, body->getVelocity().getY()));
    swordCollider->setActive(false);
  }, 
    [=](float delta) {
    if (animator->getAction()->getActionName() == "idle1" && !animator->isPlaying() && idleTimer->isDone())
    {
      animator->setAction("idle2");
      idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
      return;
    }

    if (animator->getAction()->getActionName() == "idle2" && !animator->isPlaying() && idleTimer->isDone())
    {
      int random = rand() % 2;
      if (random == 0)
      {
        animator->setAction("idle1");
        idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
      }
      else
      {
        animator->setAction("idle3");
        idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
      }
      return;
    }
    if (animator->getAction()->getActionName() == "idle3" && !animator->isPlaying() && idleTimer->isDone())
    {
      animator->setAction("idle4");
      idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
    }

    if (animator->getAction()->getActionName() == "idle4" && !animator->isPlaying() && idleTimer->isDone())
    {
      int random = rand() % 2;
      if (random == 0)
      {
        animator->playFromStart();
        idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
      }
      else
      {
        animator->setAction("idle5");
        idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
      }
      return;
    }
    if (animator->getAction()->getActionName() == "idle5" && !animator->isPlaying() && idleTimer->isDone())
    {
      animator->setAction("idle4");
      idleTimer->start(1.0f * (200 + rand() % 900) / 1000);
    }
  }, 
    NULL);

  new ala::State(stateManager, "look-up",
    [=] {
    // animation effect 
      {
        if (stateManager->getPreviousStateName() == "look-up-attack" ||
          stateManager->getPreviousStateName() == "look-up-throw") {
          animator->setAction("face_is_up");
        }
        else {
          animator->setAction("look-up");
        }
      }
  },
    [=](float dt) {
    // direction
      
  }, NULL);

  new ala::State(stateManager, "look-up-attack",
    [=] {
    // animation effect
      {
        animator->setAction("slash-lookup");
      }


      // sword
      {
        swordCollider->setOffset(swordOffset5);
        swordCollider->setSize(swordSize5);
        swordCollider->setActive(false);
        swordTimer->start(0.2f);
      }
  },
    [=](float dt) {
    // sword
      {
        if (swordTimer->isDone()) {
          if (!swordCollider->isActive()) {
            swordCollider->setActive(true);
            swordTimer->start(0.25f);

            // audio 
            {
              ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("HighSword.wav"));
            }
          }
          else {
            swordCollider->setActive(false);
            if (swordCollider->getOffset() == swordOffset5) {
              swordCollider->setOffset(swordOffset6);
              swordCollider->setSize(swordSize6);
              swordTimer->start(0.15f);
            }
            else {
              swordTimer->start(5);
            }
          }
        }
      }
  },
    [=] {
    // sword
      {
        swordCollider->setActive(false);
      }
  });

  new ala::State(stateManager, "look-up-throw",
    [=] {
    // animation effect
      {
        animator->setAction("attack_3");
      }

      // throw
      {
        appleTimer->start(0.1f);
      }
  },
    [=](float) {

      // throw
      {
        if (appleTimer->isDone()) {
          aladdinController->throwApple();

          appleTimer->start(5.0f);

          // audio
          {
            gameManager->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
          }
        }
      }
  }, NULL);

  new ala::State(stateManager, "run",
    [=] {
    animator->setAction("run1");
    dashTimer->start(0.7f);
    body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    body->setGravityScale(1);
    },
    [=] (float delta) {
      body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));

    if (animator->getAction()->getActionName() == "run1" && !animator->isPlaying())
    {
      animator->setAction("run2");
    }
    },
    NULL);
  new ala::State(stateManager, "dash",
    [=] {
    animator->setAction("dash");
    body->setVelocity(ala::Vec2(25 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    aladdinController->deactivateHorizontalDirectionScalarChecking();
  }, 
    NULL, 
    [=]{
    aladdinController->activateHorizontalDirectionScalarChecking();
    });
 /* new ala::State(stateManager, "look-up",
    [=] {
    animator->setAction("look-up");
    body->setVelocity(ala::Vec2(0, 0));
  }, [=](float delta)
  {
  }, [=] {
  });*/

  new ala::State(stateManager, "hit",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("AladdinHurt.wav"));
    animator->setAction("damaged");
    body->setVelocity(ala::Vec2(0, body->getVelocity().getY()));
    aladdinController->resetHit();
  }, NULL, NULL);

  new ala::State(stateManager, "sitdown",
    [=] {
    if(stateManager->getPreviousStateName() == "throw-sit" || stateManager->getPreviousStateName() == "slash-sit")
    {
      animator->setAction("sitdown");
    }
    else
    {
      animator->setAction("sitdown0");

    }
    body->setVelocity(ala::Vec2(0, 0));
  }, 
    NULL, 
    NULL);
  new ala::State(stateManager, "throw-stand",
    [=] {
    appleTimer->start(0.3f);
    animator->setAction("throw-stand");
    body->setVelocity(ala::Vec2(0, 0));
  }, 
    [=](float dt)
  {
    if (appleTimer->isDone())
    {
      aladdinController->throwApple();
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
      appleTimer->start(1000);
    }
  }, 
    NULL);
  new ala::State(stateManager, "throw-sit",
    [=] {
    appleTimer->start(0.3f);
    animator->setAction("throw-sit");
    body->setVelocity(ala::Vec2(0, 0));
  },
    [=](float dt)
  {
    if (appleTimer->isDone())
    {
      aladdinController->throwApple();
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
      appleTimer->start(1000);
    }
  },
    NULL);
  
  new ala::State(stateManager, "slash-stand",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("HighSword.wav"));
    animator->setAction("slash-stand");
    body->setVelocity(ala::Vec2(0, 0));

    swordCollider->setOffset(ala::Vec2(45, 10));
    swordCollider->setSize(ala::Size(40, 45));
    swordCollider->setActive(false);
    swordTimer->start(0.2f);
  },
    [=] (float delta){
      if(swordTimer->isDone())
      {
        if (!swordCollider->isActive()) {
          swordCollider->setActive(true);
          swordTimer->start(0.1f);
        }
        else
        {
          swordCollider->setActive(false);
        }
      }
  },
    [=]{
    swordCollider->setActive(false);
    });

  new ala::State(stateManager, "slash-sit",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("LowSword.wav"));
    animator->setAction("slash-sit");		     
    body->setVelocity(ala::Vec2(0, 0));

    swordCollider->setOffset(ala::Vec2(55, -2.5f));
    swordCollider->setSize(ala::Size(40, 20));
    swordCollider->setActive(false);
    swordTimer->start(0.2f);
    }, 
    [=](float delta) {
      if (swordTimer->isDone()) {
        if (!swordCollider->isActive()) {
          swordCollider->setActive(true);
          swordTimer->start(0.2f);
        }
        else {
          swordCollider->setActive(false);
        }
      }

    },
    [=]{
      swordCollider->setActive(false);
    });
  //slash-run
  new ala::State(stateManager, "slash-run",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("HighSword.wav"));
    animator->setAction("slash-run");
    body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), 0));

    swordCollider->setOffset(ala::Vec2(25, 10));
    swordCollider->setSize(ala::Size(25, 40));
    swordCollider->setActive(false);
    swordTimer->start(0.1f);
  }, [=](float delta)
  {
    //body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    if (swordTimer->isDone()) {
      if (!swordCollider->isActive()) {
        swordCollider->setActive(true);
        swordTimer->start(0.1f);
      }
      else {
        swordCollider->setActive(false);
      }
    }
  }, 
    [=] {
    swordCollider->setActive(false);
  });

  //throw-run
  new ala::State(stateManager, "throw-run",
    [=] {
    appleTimer->start(0.3f);
    animator->setAction("throw-run");
    body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), 0));
  }, 
    [=](float dt)
  {
    body->setVelocity(ala::Vec2(150 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    if (appleTimer->isDone())
    {
      aladdinController->throwApple();
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
      appleTimer->start(1000);
    }
  }, 
    NULL);
  new ala::State(stateManager, "jump",
    [=] {
    jumpTimer->start(1);
    if(stateManager->getPreviousStateName() == "hang" || stateManager->getPreviousStateName() == "hang-move")
    {
      jumpTimer->start(0.5);
      body->setVelocity(ala::Vec2(0, 0));
      const auto distance = hangerChecker->getBoundingRect().getMaxY() - aladdinController->getCollidingHanger()->getBoundingRect().getMinY();
      transform->setPositionY(transform->getPositionY() - distance - 10);
    }
    else if(stateManager->getPreviousStateName() == "throw-jump" || stateManager->getPreviousStateName() == "slash-jump" || stateManager->getPreviousStateName() == "climb-jump")
    {
      
    }
    else
    {
      body->setVelocity(ala::Vec2(0, 220));
      aladdinController->checkJump();
    }

    animator->setAction("jump");

    }, 
    [=] (float delta){
      if(aladdinController->isHoldingJump())
      {
        jumpTimer->start(100);
        body->addVelocity(ala::Vec2(0,10));
      }
    if(input->getKey(ALA_KEY_LEFT_ARROW) || input->getKey(ALA_KEY_RIGHT_ARROW))
    {
      body->setVelocity(ala::Vec2(100* aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    }
    else
      {
      body->setVelocity(ala::Vec2(0, body->getVelocity().getY()));
      }
    },
    NULL);

  new ala::State(stateManager, "spin-jafar",
    [=] {

    animator->setAction("spin0");
    body->setVelocity(ala::Vec2(body->getVelocity().getX(), 450));
  },
    [=](float delta) {
    if (animator->getActionName() == "spin0" && !animator->isPlaying())
    {
      animator->setAction("spin");
    }
    if (input->getKey(ALA_KEY_LEFT_ARROW) || input->getKey(ALA_KEY_RIGHT_ARROW))
    {
      body->setVelocity(ala::Vec2(200 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    }
    else
    {
      body->setVelocity(ala::Vec2(300 * (object->getTransform()->getPositionX() - ala::GameManager::get()->getObjectByTag(JAFAR_TAG)->getTransform()->getPositionX()) / abs(ala::GameManager::get()->getObjectByTag(JAFAR_TAG)->getTransform()->getPositionX() - object->getTransform()->getPositionX()), body->getVelocity().getY()));
    }
  },
    NULL);


  new ala::State(stateManager, "spin",
    [=] {

    animator->setAction("spin0");

  },
    [=](float delta) {
    if(animator->getActionName() == "spin0" && !animator->isPlaying())
    {
      animator->setAction("spin");
    }
    if (input->getKey(ALA_KEY_LEFT_ARROW) || input->getKey(ALA_KEY_RIGHT_ARROW))
    {
      body->setVelocity(ala::Vec2(200 * aladdinController->getHorizontalDirectionScalar(), body->getVelocity().getY()));
    }
    else
    {
      body->setVelocity(ala::Vec2(0, body->getVelocity().getY()));
    }
  },
    NULL);
  new ala::State(stateManager, "fall",
    [=] {
    jumpTimer->start(0.8);
    body->setVelocity(ala::Vec2(0, 0));
    animator->setAction("jump");
  },NULL, NULL);

  new ala::State(stateManager, "run-jump",
    [=] {
    jumpTimer->start(1);
    animator->setAction("run-jump");
    body->setVelocity(ala::Vec2(130, 350));
  }, [=](float delta)
  {
    if (ala::Input::get()->getKeyUp(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKeyUp(ALA_KEY_RIGHT_ARROW))
    {
      body->setVelocity(ala::Vec2(0, body->getVelocity().getY()));
    }

    if(body->getVelocity().getX() == 0)
    {
      if((ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW)))
      {
        body->setVelocity(ala::Vec2(130, body->getVelocity().getY()));
      }
    }
  }, NULL);

  new ala::State(stateManager, "slash-jump",
    [=] {
    animator->setAction("slash-jump");
    swordCollider->setOffset(ala::Vec2(20, 0));
    swordCollider->setSize(ala::Size(40, 55));
    swordCollider->setActive(false);
    swordTimer->start(0.3f);
  }, [=](float delta)
  {
    if (swordTimer->isDone()) {
      if (!swordCollider->isActive()) {
        swordCollider->setActive(true);
        swordTimer->start(0.2f);
      }
      else {
        swordCollider->setActive(false);
      }
    }
  }, [=] {
    swordCollider->setActive(false);
  });
  new ala::State(stateManager, "throw-jump",
    [=] {
    appleTimer->start(0.3f);
    animator->setAction("throw-jump");
  }, [=](float dt)
  {
    if (appleTimer->isDone())
    {
      aladdinController->throwApple();
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
      appleTimer->start(1000);
    }
  }, NULL);
  new ala::State(stateManager, "push",
    [=] {
    animator->setAction("push0");
  }, [=](float dt) {
    if(animator->getActionName() == "push0" && !animator->isPlaying())
    {
      animator->setAction("push1");
    }
    if(animator->getCurrentFrameIndex() == 7)
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Aladdin Push.wav"));
    }
  },NULL);

  //climb
  new ala::State(stateManager, "climb",
    [=] {
    if (animator->getAction()->getActionName() != "climb")
    {
      animator->setAction("climb");
    }

    animator->pause();
    body->setVelocity(ala::Vec2(0, 0));
    body->setGravityScale(0);
  }, NULL, [=] {
    body->setGravityScale(1);
  });

  //land
  new ala::State(stateManager, "land",
    [=] {
    animator->setAction("land");
    body->setVelocity(ala::Vec2(0, 0));
  }, [=](float dt)
  {
    if (!animator->isPlaying())
    {
      stateManager->changeState("stand");
    }
  }, NULL);

  //climb-move
  new ala::State(stateManager, "climb-move",
    [=] {
    aladdinController->activateVerticalDirectionScalarChecking();
    animator->play();
    body->setVelocity(ala::Vec2(0, 100 * aladdinController->getVerticalDirectionScalar()));
    body->setGravityScale(0);
  }, [=](float delta) {
    if(collider->getBoundingRect().getMaxY() > aladdinController->getCollidingRope()->getBoundingRect().getMaxY())
    {
      transform->setPosition(transform->getPositionX(), transform->getPositionY() - (collider->getBoundingRect().getMaxY() > aladdinController->getCollidingRope()->getBoundingRect().getMaxY()));
    }
  }, [=] {
    body->setGravityScale(1);
    aladdinController->deactivateVerticalDirectionScalarChecking();
  });

  new ala::State(stateManager, "climb-jump",
    [=] {
    animator->setAction("climb-jump");
    body->setVelocity(ala::Vec2(0, 400));
  }, [=](float delta) {
    if (collider->getBoundingRect().getMaxY() > aladdinController->getCollidingRope()->getBoundingRect().getMaxY())
    {
      transform->setPosition(transform->getPositionX(), transform->getPositionY() - (collider->getBoundingRect().getMaxY() > aladdinController->getCollidingRope()->getBoundingRect().getMaxY()));
    }
  }, [=]{
  });
  //hang
  new ala::State(stateManager, "hang",
    [=] {
    animator->setAction("hang");
    body->setVelocity(ala::Vec2());
    body->setGravityScale(0);
  }, NULL, [=] {
    body->setGravityScale(1);
    jumpTimer->start(0.1);
  });

  //hang-move
  new ala::State(stateManager, "hang-move",
    [=] {
    animator->setAction("hang-move");
    body->setVelocity(ala::Vec2(100 * aladdinController->getHorizontalDirectionScalar(), 0));
    body->setGravityScale(0);
  }, NULL, [=] {
    body->setGravityScale(1);
  });

  new ala::State(stateManager, "hang-throw",
    [=] {
    appleTimer->start(0.3f);
    animator->setAction("hang-throw");
    body->setVelocity(ala::Vec2(0, 0));
    body->setGravityScale(0);
  }, [=](float delta)
  {
    if (appleTimer->isDone())
    {
      aladdinController->throwApple();
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ObjectThrow.wav"));
      appleTimer->start(1000);
    }
  }, [=] {
    body->setGravityScale(1);
  });
  //hang-slash
  new ala::State(stateManager, "hang-slash",
    [=] {
    animator->setAction("hang-slash");
    body->setVelocity(ala::Vec2(0, 0));
    body->setGravityScale(0);

    swordCollider->setOffset(ala::Vec2(25, 10));
    swordCollider->setSize(ala::Size(25, 40));
    swordCollider->setActive(false);
    swordTimer->start(0.2f);
  }, [=](float dt) {
    if (swordTimer->isDone())
    {
      if (!swordCollider->isActive()) {
        swordCollider->setActive(true);
        swordTimer->start(0.1f);
      }
      else
      {
        swordCollider->setActive(false);
      }
    }
  }, [=] {
    swordCollider->setActive(false);
  });



  // state transitions
  new ala::StateTransition(stateManager, "stand", "hit", [=] {
    return aladdinController->isHit();
  });
  new ala::StateTransition(stateManager, "hit", "stand", [=] {
    return !animator->isPlaying();
  });
  new ala::StateTransition(stateManager, "hit", "run", [=] {
    return ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW);
  });
  new ala::StateTransition(stateManager, "stand", "run", [] {
    return ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW) || ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW);
  });
  new ala::StateTransition(stateManager, "run", "dash", [=] {
    return dashTimer->isDone() && ((!ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW) && !ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW)));
  });
  new ala::StateTransition(stateManager, "dash", "run", [=] {
    return ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW) || ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW);
  });
  new ala::StateTransition(stateManager, "run", "stand", [=] {
    return (aladdinController->isCollidingGround() && !ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW)) && (!ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW));
  });
  new ala::StateTransition(stateManager, "run", "climb", [=] {
    return (aladdinController->isCollidingRope() && !aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "slash-run", "climb", [=] {
    return (aladdinController->isCollidingRope() && !aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "throw-run", "climb", [=] {
    return (aladdinController->isCollidingRope() && !aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "stand", "sitdown", [] {
    return (ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW));
  });
  new ala::StateTransition(stateManager, "sitdown", "stand", [] {
    return (!ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW));
  });
  new ala::StateTransition(stateManager, "sitdown", "throw-sit", [] {
    return (ala::Input::get()->getKeyDown("a"));
  });
  new ala::StateTransition(stateManager, "throw-sit", "sitdown", [=] {
    return ((!animator->isPlaying() && animator->getAction()->getActionName() == "throw-sit") || ala::Input::get()->getKeyDown("s") || ala::Input::get()->getKeyDown("d") || ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW));
  });
  new ala::StateTransition(stateManager, "dash", "stand", [=] {
    return animator->getActionName() == "dash" && !animator->isPlaying();
  });
  new ala::StateTransition(stateManager, "stand", "throw-stand", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "look-up", "throw-stand", [=] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "throw-stand", "stand", [=] {
    return ((!animator->isPlaying() && animator->getAction()->getActionName() == "throw-stand") || ala::Input::get()->getKeyDown("s") || ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW));
  });
  new ala::StateTransition(stateManager, "stand", "slash-stand", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });
  new ala::StateTransition(stateManager, "slash-stand", "stand", [=] {
    return ((!animator->isPlaying() && animator->getAction()->getActionName() == "slash-stand") || ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW));
  });
  new ala::StateTransition(stateManager, "sitdown", "slash-sit", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });
  new ala::StateTransition(stateManager, "run", "slash-run", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });

  new ala::StateTransition(stateManager, "slash-run", "run", [=] {
    return (!animator->isPlaying() && animator->getAction()->getActionName() == "slash-run");
  });
  new ala::StateTransition(stateManager, "run", "throw-run", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });

  new ala::StateTransition(stateManager, "throw-run", "run", [=] {
    return (!animator->isPlaying() && animator->getAction()->getActionName() == "throw-run");
  });

  new ala::StateTransition(stateManager, "slash-sit", "sitdown", [=] {
    return ((!animator->isPlaying() && animator->getAction()->getActionName() == "slash-sit") || ala::Input::get()->getKeyDown("d") || ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW));
  });

  new ala::StateTransition(stateManager, "stand", "jump", [] {
    return (ala::Input::get()->getKeyDown("d"));
  });
  new ala::StateTransition(stateManager, "jump", "land", [=] {
    return aladdinController->isCollidingGround() && jumpTimer->isDone();
  });
  new ala::StateTransition(stateManager, "jump", "stand", [=] {
    return (aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "spin", "stand", [=] {
    return (aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "spin-jafar", "stand", [=] {
    return (body->getVelocity().getY() < -10);
  });

  new ala::StateTransition(stateManager, "fall", "land", [=] {
    return (aladdinController->isCollidingGround()) && jumpTimer->isDone();
  });

  new ala::StateTransition(stateManager, "fall", "stand", [=] {
    return (aladdinController->isCollidingGround());
  });

  new ala::StateTransition(stateManager, "run", "run-jump", [] {
    return (ala::Input::get()->getKeyDown("d"));
  });

  new ala::StateTransition(stateManager, "run-jump", "land", [=] {
    return aladdinController->isCollidingGround() && jumpTimer->isDone();
  });

  new ala::StateTransition(stateManager, "run-jump", "run", [=] {
    return aladdinController->isCollidingGround();
  });

  new ala::StateTransition(stateManager, "run-jump", "slash-jump", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });

  //new ala::StateTransition(stateManager, "run-jump", "run-jump-fall", [] {
  //  return (ala::Input::get()->getKeyDown("s"));
  //});
  new ala::StateTransition(stateManager, "slash-jump", "stand", [=] {
    return (aladdinController->isCollidingGround());
  });
  new ala::StateTransition(stateManager, "slash-jump", "fall", [=] {
    return (animator->getActionName() == "slash-jump" && !animator->isPlaying());
  });
  new ala::StateTransition(stateManager, "jump", "slash-jump", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });
  new ala::StateTransition(stateManager, "spin", "slash-jump", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });

  new ala::StateTransition(stateManager, "run-jump", "throw-jump", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });

  new ala::StateTransition(stateManager, "throw-jump", "jump", [=] {
    return (!aladdinController->isCollidingGround() && !animator->isPlaying() && animator->getAction()->getActionName() == "throw-jump");
  });
  new ala::StateTransition(stateManager, "jump", "throw-jump", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "spin", "throw-jump", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });

  new ala::StateTransition(stateManager, "throw-jump", "slash-jump", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });

  new ala::StateTransition(stateManager, "slash-stand", "throw-stand", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "slash-sit", "throw-sit", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "throw-stand", "slash-stand", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });
  new ala::StateTransition(stateManager, "throw-sit", "slash-sit", [] {
    return (ala::Input::get()->getKeyDown("s"));
  });
  new ala::StateTransition(stateManager, "slash-jump", "throw-jump", [] {
    return (ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0);
  });
  new ala::StateTransition(stateManager, "throw-jump", "stand", [=] {
    return aladdinController->isCollidingGround();
  });
  new ala::StateTransition(stateManager, "run", "push", [=] {
    return (aladdinController->isCollidingWallLeft() && ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW)) || 
      (aladdinController->isCollidingWallRight() && ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW));
  });
  new ala::StateTransition(stateManager, "push", "stand", [=] {
    return (!aladdinController->isCollidingWallLeft() && !aladdinController->isCollidingWallRight()) || (aladdinController->isCollidingWallLeft() && !(ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW))) ||
      (aladdinController->isCollidingWallRight() && !(ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW)));
  });
  new ala::StateTransition(stateManager, "push", "run", [=] {
    return aladdinController->isCollidingWallLeft() && ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW);
  });
  new ala::StateTransition(stateManager, "jump", "climb", [=] {
    return (aladdinController->isCollidingRope() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "spin", "climb", [=] {
    return (aladdinController->isCollidingRope() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "climb-jump", "hang", [=] {
    return aladdinController->isCollidingHanger() && body->getVelocity().getY() < 0;
  });
  new ala::StateTransition(stateManager, "jump", "hang", [=] {
    return (aladdinController->isCollidingHanger() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "run-jump", "hang", [=] {
    return (aladdinController->isCollidingHanger() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "run", "hang", [=] {
    return (aladdinController->isCollidingHanger() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "spin", "hang", [=] {
    return (aladdinController->isCollidingHanger() && body->getVelocity().getY() < 0);
  });
  new ala::StateTransition(stateManager, "hang", "jump", [=] {
    return input->getKeyDown("d") || !aladdinController->isCollidingHanger();
  });
  new ala::StateTransition(stateManager, "hang-move", "jump", [=] {
    return input->getKeyDown("d") || !aladdinController->isCollidingHanger();
  });
  new ala::StateTransition(stateManager, "hang", "hang-move", [=] {
    return input->getKey(ALA_KEY_LEFT_ARROW) || input->getKey(ALA_KEY_RIGHT_ARROW);
  });
  new ala::StateTransition(stateManager, "hang-move", "hang", [=] {
    return !input->getKey(ALA_KEY_LEFT_ARROW) && !input->getKey(ALA_KEY_RIGHT_ARROW);
  });
  new ala::StateTransition(stateManager, "run-jump", "climb", [=] {
    return (aladdinController->isCollidingRope());
  });
  new ala::StateTransition(stateManager, "climb", "climb-move", [=] {
    if(input->getKey(ALA_KEY_DOWN_ARROW))
    {
      return true;
    }
    if (aladdinController->isCollidingRope() && aladdinController->getCollidingRope()->getBoundingRect().getMaxY() < collider->getBoundingRect().getMaxY())
    {
      return false;
    }
    return (ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });
  new ala::StateTransition(stateManager, "climb-move", "fall", [=] {
    return (input->getKey(ALA_KEY_DOWN_ARROW) && aladdinController->getCollidingRope()->getBoundingRect().getMinY() > collider->getBoundingRect().getMinY() + 10);
  });
  new ala::StateTransition(stateManager, "climb-move", "climb", [=] {
    if (!input->getKey(ALA_KEY_DOWN_ARROW) && aladdinController->isCollidingRope() && aladdinController->getCollidingRope()->getBoundingRect().getMaxY() < collider->getBoundingRect().getMaxY())
    {
      return true;
    }
    return ((!ala::Input::get()->getKey(ALA_KEY_UP_ARROW)) && (!ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW)));
  });
  new ala::StateTransition(stateManager, "climb", "climb-jump", [] {
    return (ala::Input::get()->getKeyDown("d"));
  });
  new ala::StateTransition(stateManager, "climb-move", "climb-jump", [] {
    return (ala::Input::get()->getKeyDown("d"));
  });
  new ala::StateTransition(stateManager, "climb-jump", "climb", [=] {
    return (aladdinController->isCollidingRope() && animator->getAction()->getActionName() == "climb-jump" && !animator->isPlaying());
  });
  new ala::StateTransition(stateManager, "climb-jump", "jump", [=] {
    return ((ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW)) || (ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW)));
  });
  new ala::StateTransition(stateManager, "climb", "hang-throw", [] {
    return ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0;
  });

  new ala::StateTransition(stateManager, "hang-throw", "climb", [=] {
    return aladdinController->isCollidingRope() && ((!animator->isPlaying() && animator->getActionName() == "hang-throw") || ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW) || ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });
  new ala::StateTransition(stateManager, "climb", "hang-slash", [] {
    return ala::Input::get()->getKeyDown("s");
  });

  new ala::StateTransition(stateManager, "hang-slash", "climb", [=] {
    return (aladdinController->isCollidingRope() && !animator->isPlaying() && animator->getActionName() == "hang-slash") || ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW) || ala::Input::get()->getKey(ALA_KEY_UP_ARROW);
  });
  //
  new ala::StateTransition(stateManager, "hang", "hang-throw", [] {
    return ala::Input::get()->getKeyDown("a") && GameData::get()->getInt(APPLE_DATA_KEY)>0;
  });

  new ala::StateTransition(stateManager, "hang-throw", "hang", [=] {
    return aladdinController->isCollidingHanger() && ((!animator->isPlaying() && animator->getActionName() == "hang-throw") || ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW) || ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });
  new ala::StateTransition(stateManager, "hang", "hang-slash", [] {
    return ala::Input::get()->getKeyDown("s");
  });

  new ala::StateTransition(stateManager, "hang-slash", "hang", [=] {
    return aladdinController->isCollidingHanger() && ((!animator->isPlaying() && animator->getActionName() == "hang-slash") || ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW) || ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });

  new ala::StateTransition(stateManager, "stand", "look-up", [] {
    return (ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });

  new ala::StateTransition(stateManager, "look-up", "stand", [] {
    return (!ala::Input::get()->getKey(ALA_KEY_UP_ARROW));
  });

  new ala::StateTransition(stateManager, "look-up", "jump", [=] {
    return input->getKeyDown(ALA_KEY_D);
  });

  new ala::StateTransition(stateManager, "look-up-attack", "jump", [=] {
    return input->getKeyDown(ALA_KEY_D);
  });

  new ala::StateTransition(stateManager, "look-up-throw", "jump", [=] {
    return input->getKeyDown(ALA_KEY_D);
  });

  new ala::StateTransition(stateManager, "stand", "look-up", [=] {
    return input->getKey(ALA_KEY_UP_ARROW);
  });

  new ala::StateTransition(stateManager, "slash-stand", "look-up", [=] {
    return input->getKey(ALA_KEY_UP_ARROW);
  });

  new ala::StateTransition(stateManager, "look-up", "stand", [=] {
    return !input->getKey(ALA_KEY_UP_ARROW) && !animator->isPlaying();
  });

  new ala::StateTransition(stateManager, "look-up", "look-up-attack", [=] {
    return input->getKeyDown(ALA_KEY_S) && !animator->isPlaying();
  });

  new ala::StateTransition(stateManager, "look-up-attack", "look-up", [=] {
    return !animator->isPlaying();
  });

  new ala::StateTransition(stateManager, "look-up", "look-up-throw", [=] {
    return input->getKeyDown(ALA_KEY_A) && !animator->isPlaying() && GameData::get()->getInt(APPLE_DATA_KEY) > 0;
  });

  new ala::StateTransition(stateManager, "look-up-throw", "look-up", [=] {
    return input->getKey(ALA_KEY_UP_ARROW) && !animator->isPlaying();
  });

}

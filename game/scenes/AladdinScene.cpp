/*
* Created by phuctm97 on Sep 30th 2017
*/

#include "AladdinScene.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../scripts/GameDataListener.h"
#include "../scripts/CameraController.h"
#include "../scripts/StairController.h"
#include "core/MapResource.h"
#include "../scripts/CollectableItemController.h"
#include "../scripts/EnemyController.h"
#include "../scripts/CharcoalBurnerController.h"
#include "../scripts/ActiveTrackerController.h"
#include "../scripts/OneWayPlatformController.h"
#include "../scripts/SpawnPointController.h"
#include "../scripts/SpawnGroupController.h"
#include "../scripts/BossSceneController.h"
#include "../Macros.h"
#include "../scripts/ParalaxController.h"

USING_NAMESPACE_ALA;

AladdinScene::AladdinScene(const std::string &mapResourceName)
{
  _mapResourceName = mapResourceName;
}

const std::string& AladdinScene::getMapResourceName() const
{
  return _mapResourceName;
}

void AladdinScene::onPreInitialize() {
  const auto gameManager = GameManager::get();

  auto map = static_cast<MapResource*>(gameManager->getResource(_mapResourceName));
  
  enablePhysics(Vec2(map->getFloatProperty("gravity_x"), map->getFloatProperty("gravity_y")));
  //enableQuadTree(map->getFloatProperty("min_x"), map->getFloatProperty("min_y"), map->getFloatProperty("width"), map->getFloatProperty("height"), 3);

  gameManager->getPrefab("Fade In Effect")->instantiate();

  if(map->keyExist("background"))
  {
    const auto background = new GameObject(this, "Background");
    background->setTag(BACKGROUND_TAG);
    new SpriteRenderer(background, map->getStringProperty("background"));
    background->setLayer("Background");
    background->getTransform()->setPosition(0, 0);

  }

  if(map->keyExist("foreground"))
  {
    const auto foreground = new GameObject(this, "Foreground");
    foreground->setTag(FOREGROUND_TAG);
    new SpriteRenderer(foreground, map->getStringProperty("foreground"));
    foreground->setLayer("Foreground");
    foreground->getTransform()->setPosition(0, 0);
  }

  if (map->keyExist("background_music"))
  {
    _backgroundMusicResourceName = map->getStringProperty("background_music");
  }


  //Ground
  const auto ground = new GameObject(this);
  ground->getTransform()->setPosition(0, 0);
  ground->setTag(GROUND_TAG);
  new Rigidbody(ground, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);

  const auto platform = new GameObject(this);
  platform->getTransform()->setPosition(0, 0);
  platform->setTag(GROUND_TAG);
  new Rigidbody(platform, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
  auto platformController = new OneWayPlatformController(platform);

  const auto wall = new GameObject(this);
  wall->getTransform()->setPosition(0, 0);
  wall->setTag(WALL_TAG);
  new Rigidbody(wall, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);

  const auto rope = new GameObject(this);
  rope->getTransform()->setPosition(0, 0);
  rope->setTag(ROPE_TAG);
  new Rigidbody(rope, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);

  const auto hanger = new GameObject(this);
  hanger->getTransform()->setPosition(0, 0);
  hanger->setTag(HANGER_TAG);
  new Rigidbody(hanger, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);

  const auto stair = new GameObject(this);
  stair->getTransform()->setPosition(0, 0);
  stair->setTag(GROUND_TAG);
  new Rigidbody(stair, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
  new StairController(stair);

  const auto charcoalBurner = new GameObject(this);
  charcoalBurner->getTransform()->setPosition(0, 0);
  charcoalBurner->setTag(CHARCOAL_BURNER_TAG);
  new Timer(charcoalBurner);
  new Rigidbody(charcoalBurner, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
  new CharcoalBurnerController(charcoalBurner);

  const auto mapBlocker = new GameObject(this);
  mapBlocker->getTransform()->setPosition(0, 0);
  mapBlocker->setTag(MAP_BLOCKER_TAG);
  new Rigidbody(mapBlocker, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);

  for(auto activeTracker: map->getMapObjects("ActiveTracker"))
  {
    auto activeTrackerObject = new GameObject(this, activeTracker.getName());
    activeTrackerObject->getTransform()->setPosition(Vec2(activeTracker.getRect().getMidX(), activeTracker.getRect().getMidY()));
    new Rigidbody(activeTrackerObject, PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
    auto collider = new Collider(activeTrackerObject, true, Vec2(), Size(activeTracker.getRect().getSize().getWidth(), activeTracker.getRect().getSize().getHeight()));
    new ActiveTrackerController(activeTrackerObject);

    collider->ignoreTag(WALL_TAG);
    collider->ignoreTag(ROPE_CHECKER_TAG);
    collider->ignoreTag(HANGER_CHECKER_TAG);
    collider->ignoreTag(ROPE_TAG);
    collider->ignoreTag(GROUND_TAG);
    collider->ignoreTag(HANGER_TAG);
    collider->ignoreTag(CHARCOAL_BURNER_TAG);
    collider->ignoreTag(ENEMY_TAG);
    collider->ignoreTag(ENEMY_WEAPON_TAG);
    collider->ignoreTag(ALADDIN_WEAPON_TAG);
    collider->ignoreTag(COLLECTABLE_ITEM_TAG);

    if (activeTracker.keyExist("active_tracker_name"))
    {
      gameManager->getObjectByName(activeTracker.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(collider);
    }

    new ColliderRenderer(collider);
  }

  for (auto unmovableObject : map->getMapObjects("UnmovableObjects"))
  {
    const auto type = unmovableObject.getType();
    if(type == "GROUND")
    {
      auto groundCollider = new Collider(ground, false, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      groundCollider->setTag(GROUND_TAG);
      groundCollider->ignoreTag(GROUND_TAG);
      groundCollider->ignoreTag(WALL_TAG);
      groundCollider->ignoreTag(ROPE_CHECKER_TAG);
      groundCollider->ignoreTag(ROPE_TAG);
      groundCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      groundCollider->ignoreTag(HANGER_TAG);

      if(unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(groundCollider);
      }

      new ColliderRenderer(groundCollider);
    }
    else if(type == "PLATFORM")
    {
      auto platformCollider = new Collider(platform, false, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      platformCollider->setTag(GROUND_TAG);
      platformCollider->ignoreTag(WALL_TAG);
      platformCollider->ignoreTag(ROPE_CHECKER_TAG);
      platformCollider->ignoreTag(ROPE_TAG);
      platformCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      platformCollider->ignoreTag(HANGER_TAG); 

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(platformCollider);
      }

      platformController->addPlatform(platformCollider);

      new ColliderRenderer(platformCollider);

    }
    else if(type == "SPRING")
    {
      gameManager->getPrefab("Spring")->instantiate(Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()));
    }
    else if(type == "CHARCOALBURNER")
    {
      auto charcoalBurnerCollider = new Collider(charcoalBurner, true, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      charcoalBurnerCollider->setTag(CHARCOAL_BURNER_TAG);
      charcoalBurnerCollider->ignoreTag(WALL_TAG);
      charcoalBurnerCollider->ignoreTag(ROPE_CHECKER_TAG);
      charcoalBurnerCollider->ignoreTag(ROPE_TAG);
      charcoalBurnerCollider->ignoreTag(GROUND_TAG);
      charcoalBurnerCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      charcoalBurnerCollider->ignoreTag(HANGER_TAG);
      charcoalBurnerCollider->ignoreTag(CHARCOAL_BURNER_TAG);
      charcoalBurnerCollider->ignoreTag(COLLECTABLE_ITEM_TAG);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(charcoalBurnerCollider);
      }
      new ColliderRenderer(charcoalBurnerCollider);
    }
    else if(type == "WALL")
    {
      auto wallCollider = new Collider(wall, false, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      wallCollider->setTag(WALL_TAG);
      wallCollider->setTag(NPC_TAG);
      wallCollider->ignoreTag(SPRING_TAG);
      wallCollider->ignoreTag(HANGER_CHECKER_TAG);
      wallCollider->ignoreTag(ENEMY_TAG);
      wallCollider->ignoreTag(WALL_TAG);
      wallCollider->ignoreTag(WALL_TAG);
      wallCollider->ignoreTag(ROPE_CHECKER_TAG);
      wallCollider->ignoreTag(ROPE_TAG);
      wallCollider->ignoreTag(GROUND_TAG);
      wallCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      wallCollider->ignoreTag(HANGER_TAG);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(wallCollider);
      }

      new ColliderRenderer(wallCollider);
    }
    else if(type == "ROPE")
    {
      auto ropeCollider = new Collider(rope, true, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      ropeCollider->setTag(ROPE_TAG);
      ropeCollider->ignoreTag(ROPE_TAG);
      ropeCollider->ignoreTag(WALL_TAG);
      ropeCollider->ignoreTag(ALADDIN_WEAPON_TAG);
      ropeCollider->ignoreTag(ROPE_TAG);
      ropeCollider->ignoreTag(GROUND_TAG);
      ropeCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      ropeCollider->ignoreTag(HANGER_TAG);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(ropeCollider);
      }

      new ColliderRenderer(ropeCollider);
    }
    else if (type == "STAIR")
    {
      auto stairCollider = new Collider(stair, false, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      stairCollider->setTag(GROUND_TAG);
      stairCollider->ignoreTag(GROUND_TAG);
      stairCollider->ignoreTag(WALL_TAG);
      stairCollider->ignoreTag(ROPE_CHECKER_TAG);
      stairCollider->ignoreTag(ROPE_TAG);
      stairCollider->ignoreTag(GROUND_TAG);
      stairCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      stairCollider->ignoreTag(HANGER_TAG);
      new ColliderRenderer(stairCollider);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(stairCollider);
      }
    }
    else if(type == "FALLING PLATFORM")
    {
      gameManager->getPrefab("FallingPlatform")->instantiate(Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()));
    }
    else if(type == "MAPBLOCKER")
    {
      auto mapBlockerCollider = new Collider(mapBlocker, false, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      mapBlockerCollider->setTag(MAP_BLOCKER_TAG);
      mapBlockerCollider->ignoreTag(MAP_BLOCKER_TAG);
      mapBlockerCollider->ignoreTag(ENEMY_TAG);

      mapBlockerCollider->ignoreTag(WALL_TAG);
      mapBlockerCollider->ignoreTag(ROPE_CHECKER_TAG);
      mapBlockerCollider->ignoreTag(ROPE_TAG);
      mapBlockerCollider->ignoreTag(GROUND_TAG);
      mapBlockerCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      mapBlockerCollider->ignoreTag(HANGER_TAG);
      new ColliderRenderer(mapBlockerCollider);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(mapBlockerCollider);
      }
    }
    else if(type == "HANGER")
    {
      auto hangerCollider = new Collider(hanger, true, Vec2(unmovableObject.getRect().getMidX(), unmovableObject.getRect().getMidY()), Size(unmovableObject.getRect().getSize().getWidth(), unmovableObject.getRect().getSize().getHeight()), 1, 0);
      hangerCollider->setTag(HANGER_TAG);
      hangerCollider->ignoreTag(ALADDIN_WEAPON_TAG);
      hangerCollider->ignoreTag(WALL_TAG);
      hangerCollider->ignoreTag(ROPE_TAG);
      hangerCollider->ignoreTag(GROUND_TAG);
      hangerCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
      hangerCollider->ignoreTag(HANGER_TAG);
      new ColliderRenderer(hangerCollider);

      if (unmovableObject.keyExist("active_tracker_name"))
      {
        gameManager->getObjectByName(unmovableObject.getString("active_tracker_name"))->getComponentT<ActiveTrackerController>()->addCollider(hangerCollider);
      }
    }
  }

  GameObject* aladdin = NULL;

  for (auto character : map->getMapObjects("MainCharacter"))
  {
    const auto type = character.getType();
    if(type == "Aladdin")
    {
      aladdin = gameManager->getPrefab("Aladdin")->instantiate(character.getName());
      if(GameData::get()->getString(HAS_CHECKPOINT_KEY) == "TRUE")
      {
        aladdin->getTransform()->setPosition(GameData::get()->getFloat(CHECKPOINT_DATA_X_KEY), GameData::get()->getFloat(CHECKPOINT_DATA_Y_KEY));
      }
      else
      {
        aladdin->getTransform()->setPosition(character.getRect().getMidX(), character.getRect().getMidY());
      }
    }
  }


  for(auto item: map->getMapObjects("CollectableItems"))
  {
    const auto type = item.getType();
    {
      auto itemGameObject = gameManager->getPrefab(type)->instantiate(item.getName(), item.getString("quad_index"));
      itemGameObject->getTransform()->setPosition(item.getRect().getMidX(), item.getRect().getMidY());
      itemGameObject->getComponentT<CollectableItemController>()->setValue(item.getString("value"));

      if(type == "Level Complete")
      {
        const auto collider = new ala::Collider(itemGameObject, true, ala::Vec2(0, 0), item.getRect().getSize(), 1, 0);
        collider->setTag(COLLECTABLE_ITEM_TAG);
        collider->ignoreTag(COLLECTABLE_ITEM_TAG);
        collider->ignoreTag(ENEMY_TAG);
        collider->ignoreTag(GROUND_TAG);
        collider->ignoreTag(ROPE_TAG);
        collider->ignoreTag(WALL_TAG);
        collider->ignoreTag(ROPE_CHECKER_TAG);
        collider->ignoreTag(MAP_BLOCKER_TAG);

        new ColliderRenderer(collider);
      }
    }
  }

  const auto spawnGroup = new GameObject(this);
  auto spawnGroupController = new SpawnGroupController(spawnGroup);

  for (auto point : map->getMapObjects("SpawnPoints"))
  {
    const auto type = point.getType();
    {
      const auto groupId = point.getInt("group");
      auto spawnPointObject = new GameObject(spawnGroup, point.getString("quad_index"));
      spawnPointObject->getTransform()->setPosition(point.getRect().getMidX(), point.getRect().getMidY());
      auto spawnPointController = new SpawnPointController(spawnPointObject);
      spawnPointController->setObject(type);
      spawnPointController->setId(groupId);
      spawnPointController->setValue(point.getString("value"));
      spawnGroupController->addSpawnPoint(spawnPointController);
    }
  }

  for (auto npc : map->getMapObjects("NPCs"))
  {
    const auto type = npc.getType();
    auto npcGameObject = gameManager->getPrefab(type)->instantiate(npc.getName(), npc.keyExist("quad_index")? npc.getString("quad_index"):"");
    npcGameObject->getTransform()->setPosition(npc.getRect().getMidX(), npc.getRect().getMidY());

    if(type == "Staff Guard" || type == "Sword Guard" || type == "Knife Guard" || type == "Apple Thief")
    {
      auto enemyController = npcGameObject->getComponentT<EnemyController>();
      enemyController->setStartX(npc.getFloat("start_x"));
      enemyController->setMinX(npc.getFloat("min_x"));
      enemyController->setMaxX(npc.getFloat("max_x"));
    }
    else if(type == "Knife Juggler" || type == "Pot Dropper")
    {
      auto enemyController = npcGameObject->getComponentT<EnemyController>();
      enemyController->setStartX(npcGameObject->getTransform()->getPositionX());
    }
  }

  if (_mapResourceName == "JafarBoss.tmx")
  {
    gameManager->getPrefab("Jafar Foreground")->instantiate();
    const auto bossSceneControllerObject = new GameObject(this);
    new BossSceneController(bossSceneControllerObject);
  }
  else
  {
    gameManager->getPrefab("Sand")->instantiate();
    gameManager->getPrefab("Sky")->instantiate();
  }

  if(aladdin!= NULL)
  {
    gameManager->getPrefab("Aladdin UI")->instantiate(gameManager->getRunningScene()->getMainCamera());

    new CameraController(gameManager->getRunningScene()->getMainCamera());
  }

  const auto gameListeners = new GameObject(this, "Game Listeners");
  new GameDataListener(gameListeners);
  
  GameManager::get()->getPrefab("Audio Event Listener")->instantiate();
}

void AladdinScene::onPostInitialize()
{
  if(_backgroundMusicResourceName != "")
  {
    GameManager::get()->getGlobalMessenger()->broadcast(PLAY_BACKGROUND_MESSAGE, new StringMessageArgs(_backgroundMusicResourceName));
  }
}

void AladdinScene::onPreRelease() {}

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "GameManager.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_2(ala::GameObject, ala::Initializable, ala::Releasable)

  GameObject::GameObject(Scene* parentScene, const std::string& name, const std::string& quadIndex)
  : _id(GameManager::get()->newId()),
  _name(name),
  _tag(-1),
  _flags(0),
  _parentScene(parentScene),
  _active(false),
  _selfInitialize(true),
  _toReleaseInNextFrame(false),
  _componentsInLock(false),
  _messenger(new Messenger()) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // default components
  _transform = new Transform(this);

  // attach to GameManager
  GameManager::get()->attach(this);

  // make sure parent scene is not null
  ALA_ASSERT(_parentScene != NULL);

  // attach to Scene
  _parentScene->addGameObject(this, quadIndex);

  // for debug memory allocation
  TOTAL_OBJECTS_CREATED++;
}

GameObject::GameObject(GameObject* parentObject, const std::string& name)
  : _id(GameManager::get()->newId()),
  _name(name),
  _tag(-1),
  _flags(0),
  _parentScene(NULL),
  _active(false),
  _selfInitialize(true),
  _toReleaseInNextFrame(false),
  _componentsInLock(false),
  _messenger(new Messenger()) {

  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // make sure parent object is not null
  ALA_ASSERT(parentObject != NULL);

  // default components
  _transform = new Transform(this, parentObject->getTransform());

  // attach to GameManager
  GameManager::get()->attach(this);

  // for debug memory allocation
  TOTAL_OBJECTS_CREATED++;
}

GameObject::~GameObject() {
  if (isInitialized()) {
    // make sure object released after destruction
    //    ALA_ASSERT(isReleased());
  }

  // for debug memory allocation
  TOTAL_OBJECTS_DELETED++;
}

long GameObject::getId() const {
  return _id;
}

const std::string& GameObject::getName() const {
  return _name;
}

Scene* GameObject::getParentScene() const {
  return _parentScene;
}

bool GameObject::isActive() const {
  return _active;
}

GameObject* GameObject::setActive(const bool val) {
  _active = val;
  return this;
}

bool GameObject::isSelfInitialize() const {
  return _selfInitialize;
}

GameObject* GameObject::setSelfInitialize(const bool val) {
  _selfInitialize = val;
  return this;
}

const std::string& GameObject::getLayer() const {
  return _layer;
}

GameObject* GameObject::setLayer(const std::string& layer) {
  _layer = layer;
  return this;
}

GameObject* GameObject::setTag(const int tag) {
  ALA_ASSERT(tag >= 0);
  _tag = tag;
  return this;
}

int GameObject::getTag() const {
  return _tag;
}

void GameObject::setFlags(const long v) {
  _flags = v;
}

void GameObject::addFlag(const long v) {
  _flags |= v;
}

int GameObject::getFlags() const {
  return _flags;
}

bool GameObject::hasFlag(const long v) const {
  return (_flags & v) != 0;
}

// ===========================================================
// Events
// ===========================================================

void GameObject::initialize() {
  // make sure object is not initialized;
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // init components
  for (auto component : _components) {
    if (!component->isInitialized()) {
      component->initialize();
    }
  }

  setToInitialized();

  // activate
  setActive(true);
}

void GameObject::updatePhysics(const float delta) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  // update components
  for (auto component : _components) {
    component->updatePhysics(delta);
  }

  unlockComponents();
}

void GameObject::update(const float delta) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  // update components
  for (auto component : _components) {
    component->update(delta);
  }

  unlockComponents();
}

void GameObject::onCollisionEnter(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  for (auto component : _components) {
    component->onCollisionEnter(collisionInfo);
  }

  unlockComponents();
}

void GameObject::onCollisionStay(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  for (auto component : _components) {
    component->onCollisionStay(collisionInfo);
  }

  unlockComponents();
}

void GameObject::onCollisionExit(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  for (auto component : _components) {
    component->onCollisionExit(collisionInfo);
  }

  unlockComponents();
}

void GameObject::onTriggerEnter(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  for (auto component : _components) {
    component->onTriggerEnter(collisionInfo);
  }

  unlockComponents();
}

void GameObject::onTriggerStay(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();

  for (auto component : _components) {
    component->onTriggerStay(collisionInfo);
  }
  unlockComponents();
}

void GameObject::onTriggerExit(const CollisionInfo& collisionInfo) {
  if (isReleasing() || isReleased() || !isInitialized() || !isActive()) return;

  lockComponents();
  for (auto component : _components) {
    component->onTriggerExit(collisionInfo);
  }
  unlockComponents();
}

void GameObject::render() {
  if (isReleasing() || isReleased() || !isInitialized()) return;

  lockComponents();

  // render components
  for (auto component : _components) {
    component->render();
  }

  unlockComponents();
}

void GameObject::release() {
  // check lock
  if (_componentsInLock) {
    releaseInNextFrame();
    return;
  }

  // make sure object is initialized and not released
  //  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // release components
  for (auto component : _components) {
    component->release();
  }

  // release messenger
  _messenger->release();

  // remove from parent scene
  if (_parentScene != NULL) {
    _parentScene->removeGameObject(this);
  }

  // detach from GameManager
  GameManager::get()->detach(this);

  setToReleased();

  // destroy
  delete this;
}

void GameObject::releaseInNextFrame() {
  // make sure object is initialized and not released
  //  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}

void GameObject::resolveLockedTasks() {
  if (isReleasing() || isReleased()) return;

  // lazy init
  if (!isInitialized()) {
    if (isSelfInitialize()) {
      initialize();
    }
    else return;
  }

  // update to release in next frame
  if (_toReleaseInNextFrame) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  // update actions
  updateAddAndRemoveComponentInNextFrame();

  // client
  onResolveLockedTasks();

  // update components
  lockComponents();

  for (const auto component : _components) {
    component->resolveLockedTasks();
  }

  unlockComponents();
}

void GameObject::onResolveLockedTasks() { }

// ============================================================
// Components
// ============================================================

void GameObject::addComponent(GameObjectComponent* component) {
  if (component == NULL) return;
  if (isReleasing() || isReleased()) return;

  // check lock
  if (_componentsInLock) {
    addComponentInNextFrame(component);
    return;
  }

  doAddComponent(component);
}

void GameObject::addComponentInNextFrame(GameObjectComponent* component) {
  if (component == NULL) return;
  if (isReleasing() || isReleased()) return;

  _componentsToAddInNextFrame.push_back(component);
}

void GameObject::removeComponent(GameObjectComponent* component) {
  if (component == NULL) return;
  if (isReleasing() || isReleased()) return;

  // check lock 
  if (_componentsInLock) {
    removeComponentInNextFrame(component);
    return;
  }

  doRemoveComponent(component);
}

void GameObject::removeComponentInNextFrame(GameObjectComponent* component) {
  if (component == NULL) return;
  if (isReleasing() || isReleased()) return;

  _componentsToRemoveInNextFrame.push_back(component);
}

void GameObject::refreshComponent() {
  if (_componentsNotRefreshed.empty()) return;

  std::vector<GameObjectComponent*> componentsNotRefreshed;
  componentsNotRefreshed.insert(componentsNotRefreshed.begin(),
    _componentsNotRefreshed.cbegin(), _componentsNotRefreshed.cend());

  for (const auto component : componentsNotRefreshed) {
    if (component != _transform && ALA_IS_INSTANCE_OF(component, Transform)) {
      // TODO: move children from old transform to new transform

      if (!_transform->isInitialized()) {
        _transform->initialize();
      }
      _transform->release();
      _transform = static_cast<Transform*>(component);

      StdHelper::vectorErase<GameObjectComponent*>(_components, _transform);
      _components.insert(_components.begin(), _transform);
    }
  }

  _componentsNotRefreshed.clear();
}

GameObjectComponent* GameObject::getComponent(const std::string& name) {
  refreshComponent();

  for (auto component : _components) {
    if (component != NULL && component->getName() == name) {
      return component;
    }
  }
  return NULL;
}

GameObjectComponent* GameObject::getComponent(const int tag) {
  refreshComponent();

  for (auto component : _components) {
    if (component != NULL && component->getTag() == tag) {
      return component;
    }
  }
  return NULL;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents(const std::string& name) {
  refreshComponent();

  std::vector<GameObjectComponent*> ret;

  for (auto component : _components) {
    if (component != NULL && component->getName() == name) {
      ret.emplace_back(component);
    }
  }

  return ret;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents(const int tag) {
  refreshComponent();

  std::vector<GameObjectComponent*> ret;

  for (auto component : _components) {
    if (component != NULL && component->getTag() == tag) {
      ret.emplace_back(component);
    }
  }

  return ret;
}

std::vector<GameObjectComponent*> GameObject::getAllComponents() {
  refreshComponent();

  return _components;
}

void GameObject::lockComponents() {
  _componentsInLock = true;
}

void GameObject::unlockComponents() {
  _componentsInLock = false;
}

void GameObject::updateAddAndRemoveComponentInNextFrame() {
  for (auto component : _componentsToAddInNextFrame) {
    doAddComponent(component);
  }
  _componentsToAddInNextFrame.clear();

  for (auto component : _componentsToRemoveInNextFrame) {
    doRemoveComponent(component);
  }
  _componentsToRemoveInNextFrame.clear();
}

void GameObject::doAddComponent(GameObjectComponent* component) {
  if (StdHelper::vectorContain<GameObjectComponent*>(_components, component)) return;

  _componentsNotRefreshed.emplace_back(component);

  _components.emplace_back(component);
}

void GameObject::doRemoveComponent(GameObjectComponent* component) {
  StdHelper::vectorErase<GameObjectComponent*>(_componentsNotRefreshed, component);

  StdHelper::vectorErase<GameObjectComponent*>(_components, component);
}

// ========================================================
// Default components
// ========================================================

bool GameObject::isDefaultComponents(GameObjectComponent* component) {
  if (component == _transform) return true;
  return false;
}

Transform* GameObject::getTransform() {
  refreshComponent();

  return _transform;
}

// ===========================================================
// Messenger
// ===========================================================

Messenger* GameObject::getMessenger() const {
  return _messenger;
}

// ============================================
// Debug memory allocation
// ============================================

long GameObject::TOTAL_OBJECTS_CREATED(0);

long GameObject::TOTAL_OBJECTS_DELETED(0);
}
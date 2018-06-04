#include "Animator.h"
#include "RectMessageArgs.h"
#include "SpriteRenderer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animator, ala::GameObjectComponent)

Animator::~Animator() {}

void Animator::onInitialize() {}

void Animator::onUpdate( const float delta ) {
  if ( !_isPlaying ) {
    return;
  }

  _elapsedTime += delta;

  if ( _elapsedTime >= _currentAction->getInterval() ) {
    _elapsedTime = 0;

    if ( !_isReverse ) {
      ++_frameIndex;
    }
    else {
      --_frameIndex;
    }

    if ( _frameIndex >= _currentAction->getFrames().size() || _frameIndex < 0 ) {
      if ( !_currentAction->isLoop() ) {
        _isPlaying = false;
      }
      else {
        playFromStart();
      }
    }
    else {
      const auto& v = _currentAction->getFrames()[_frameIndex];
      _spriteRenderer->setSourceRect( v.first );
      _spriteRenderer->setOffset( v.second );
    }
  }
}

Animator::Animator( GameObject* gameObject, const std::string& entryAction, Animation* animation,
                    const std::string& name )
  : GameObjectComponent( gameObject, name ) {
  _isPlaying = true;
  _isReverse = false;

  _animation = animation;
  _currentAction = _animation->getAction( entryAction );

  _frameIndex = 0;

  _spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  _spriteRenderer->setSprite(
    static_cast<Sprite*>(GameManager::get()->getResource( _currentAction->getTextureName() )) );

  const auto& v = _currentAction->getFrames()[_frameIndex];
  _spriteRenderer->setSourceRect( v.first );
  _spriteRenderer->setOffset( v.second );
}

Animator::Animator( GameObject* gameObject, const std::string& entryAction, const std::string& animationResourceName,
                    const std::string& name )
  : GameObjectComponent( gameObject, name ) {
  _isPlaying = true;
  _isReverse = false;

  _animation = static_cast<Animation*>(GameManager::get()->getResource( animationResourceName ));
  _currentAction = _animation->getAction( entryAction );

  _frameIndex = 0;

  _spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  _spriteRenderer->setSprite(
    static_cast<Sprite*>(GameManager::get()->getResource( _currentAction->getTextureName() )) );

  const auto& v = _currentAction->getFrames()[_frameIndex];
  _spriteRenderer->setSourceRect( v.first );
  _spriteRenderer->setOffset( v.second );
}

Animation* Animator::getAnimation() const {
  return _animation;
}

void Animator::setAction( const std::string& actionName ) {
  _currentAction = _animation->getAction( actionName );

  if ( !_isReverse ) {
    _frameIndex = 0;
  }
  else {
    _frameIndex = _currentAction->getFrames().size() - 1;
  }

  _isPlaying = true;
  _spriteRenderer->setSprite(
    static_cast<Sprite*>(GameManager::get()->getResource( _currentAction->getTextureName() )) );

  const auto& v = _currentAction->getFrames()[_frameIndex];
  _spriteRenderer->setSourceRect( v.first );
  _spriteRenderer->setOffset( v.second );
}

const std::string& Animator::getActionName() const {
  return _currentAction->getActionName();
}

const Rect& Animator::getCurrentFrameRect() const {
  const auto& v = _currentAction->getFrames()[_frameIndex];
  return v.first;
}

const Vec2& Animator::getCurrentFrameOffset() const {
  const auto& v = _currentAction->getFrames()[_frameIndex];
  return v.second;
}

AnimationAction* Animator::getAction() const {
  return _currentAction;
}

int Animator::getCurrentFrameIndex() const {
  return _frameIndex;
}

void Animator::pause() {
  _isPlaying = false;
}

void Animator::playNext() {
  if (!_isReverse) {
    ++_frameIndex;
  }
  else {
    --_frameIndex;
  }

  if (_frameIndex >= _currentAction->getFrames().size() ||_frameIndex < 0) {
    playFromStart();
  }
  else {
    const auto& v = _currentAction->getFrames()[_frameIndex];
    _spriteRenderer->setSourceRect(v.first);
    _spriteRenderer->setOffset(v.second);
  }
}

void Animator::play() {
  _isPlaying = true;
}

void Animator::playFromStart() {
  _isPlaying = true;

  if ( !_isReverse ) {
    _frameIndex = 0;
  }
  else {
    _frameIndex = _currentAction->getFrames().size() - 1;
  }

  const auto& v = _currentAction->getFrames()[_frameIndex];
  _spriteRenderer->setSourceRect(v.first);
  _spriteRenderer->setOffset(v.second);
}

bool Animator::isPlaying() const {
  return _isPlaying;
}

bool Animator::isReverse() const {
  return _isReverse;
}

void Animator::setReverse( const bool val ) {
  if ( val == _isReverse ) return;

  _isReverse = val;
  if ( _isReverse ) { }
}
}

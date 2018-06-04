#ifndef __ALADDIN_2D_ANIMATOR_H__
#define __ALADDIN_2D_ANIMATOR_H__

#include "2dInclude.h"
#include "Rect.h"
#include "Animation.h"

NAMESPACE_ALA
{
class SpriteRenderer;

ALA_CLASS_HEADER_1(Animator, ala::GameObjectComponent)
private:
  Animation* _animation;

  AnimationAction* _currentAction;
  
  int _frameIndex;

  float _elapsedTime;

  bool _isPlaying;
  bool _isReverse;

  SpriteRenderer* _spriteRenderer;
protected:
  virtual ~Animator();


  void onInitialize() override;
  void onUpdate( const float delta ) override;
public:
  Animator( GameObject* gameObject, const std::string& entryAction, Animation* animationName = NULL,
            const std::string& name = "" );
  Animator( GameObject* gameObject, const std::string& entryAction, const std::string& animationResourceName = "",
            const std::string& name = "" );

  Animation* getAnimation() const;

  void setAction( const std::string& actionName );
  const std::string& getActionName() const;
  AnimationAction* getAction() const;

  const Rect& getCurrentFrameRect() const;
  const Vec2& getCurrentFrameOffset() const;
  int getCurrentFrameIndex() const;

  void pause();
  void playNext();
  void play();
  void playFromStart();

  bool isPlaying() const;
  
  bool isReverse() const;
  void setReverse(const bool val);
};
}
#endif //!__ALADDIN_2D_ANIMATOR_H__

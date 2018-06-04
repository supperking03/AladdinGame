#include "Blink.h"
#include "../2d/BitmapText.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Blink, ala::Action )

Blink::Blink( const float interval, const int count ): _count( count ), _interval( interval ),
                                                       _eslapsedTime( 0 ),
                                                       _eslapsedCount( 0 ), _previousVisible( false ) { }

void Blink::onStart() {
  const auto spriteRenderer = getActionManager()->getGameObject()->getComponentT<SpriteRenderer>();
  if ( spriteRenderer == NULL )
  {
    const auto text = getActionManager()->getGameObject()->getComponentT<BitmapText>();
    if (text == NULL)
    {
      return;
    }
    _eslapsedTime = 0;
    _eslapsedCount = 0;
    _previousVisible = false;
    text->setVisible(false);
    return;
  }

  _eslapsedTime = 0;
  _eslapsedCount = 0;
  _previousVisible = false;
  spriteRenderer->setVisible( false );
}

void Blink::onUpdate( const float delta ) {
  const auto spriteRenderer = getActionManager()->getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer == NULL)
  {
    const auto text = getActionManager()->getGameObject()->getComponentT<BitmapText>();
    if (text == NULL) return;
    _eslapsedTime += delta;
    if (_eslapsedTime >= _interval) {
      _eslapsedTime = 0;

      text->setVisible(!_previousVisible);

      if (text->isVisible()) _eslapsedCount++;

      _previousVisible = text->isVisible();
    }

    if (_eslapsedCount == _count) {
      done();
    }
    return;
  }

  _eslapsedTime += delta;
  if ( _eslapsedTime >= _interval ) {
    _eslapsedTime = 0;

    spriteRenderer->setVisible( !_previousVisible );

    if ( spriteRenderer->isVisible() ) _eslapsedCount++;

    _previousVisible = spriteRenderer->isVisible();
  }

  if ( _eslapsedCount == _count ) {
    done();
  }
}
}

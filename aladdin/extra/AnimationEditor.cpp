#include "AnimationEditor.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::AnimationEditor, ala::GameObjectComponent)

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& actionName, const std::string& name )
  : GameObjectComponent( gameObject, name ), _logger( "ala::AnimationEditor" ), _actionName( actionName ) {}

bool AnimationEditor::onPreInitialize() {
  const auto animator = getGameObject()->getComponentT<Animator>();
  if ( animator == NULL ) return false;
  animator->setAction( _actionName );

  const auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if ( spriteRenderer == NULL ) return false;

  const auto spriteRendererDuplicate = new SpriteRenderer( getGameObject(), spriteRenderer->getSprite(),
                                                           "AnimationEditor-SpriteRenderer" );
  spriteRendererDuplicate->setSourceRect( spriteRenderer->getSourceRect() );
  spriteRendererDuplicate->setOffset( spriteRenderer->getOffset() );
  spriteRendererDuplicate->setBackColor( spriteRenderer->getBackColor() );
  spriteRendererDuplicate->setZOrder( spriteRenderer->getZOrder() );
  spriteRenderer->setZOrder( spriteRenderer->getZOrder() + 1 );
  spriteRendererDuplicate->initialize();

  _logger.info(
    "AnimationEditor used:\n\t- Use J, K, L, I for movement.\n\t- F1 to go to next frame.\n\t- F2 to log edited animation code.\n");

  return true;
}

void AnimationEditor::onUpdate( const float delta ) {
  const auto animator = getGameObject()->getComponentT<Animator>();
  const auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  const auto spriteRendererDuplicate = static_cast<SpriteRenderer*>(getGameObject()
    ->getComponent( "AnimationEditor-SpriteRenderer" ));
  if ( animator == NULL || spriteRenderer == NULL || spriteRendererDuplicate == NULL ) return;

  const auto input = Input::get();
  if ( input->getKeyDown( ALA_KEY_F1 ) ) {
    spriteRendererDuplicate->setSourceRect( spriteRenderer->getSourceRect() );
    spriteRendererDuplicate->setOffset( spriteRenderer->getOffset() );
    spriteRendererDuplicate->setBackColor( spriteRenderer->getBackColor() );
    spriteRendererDuplicate->setZOrder( spriteRenderer->getZOrder() );
    spriteRenderer->setZOrder( spriteRenderer->getZOrder() + 1 );
    animator->playNext();

    if ( animator->getCurrentFrameIndex() == 0 ) {
      _logger.info( "Animation started again" );
    }
  }

  else if ( input->getKeyDown( ALA_KEY_F2 ) ) {
    std::stringstream ss;
    ss << "\n<Animation";
    ss << " name=\"" << animator->getActionName() << "\"";
    ss << " imagePath=\"" << animator->getAction()->getTextureName() << "\"";
    ss << " interval=\"" << animator->getAction()->getInterval() << "\"";
    ss << " isLoop=\"" << (animator->getAction()->isLoop() ? "true" : "false") << "\"";
    ss << ">";

    for ( const auto& frame : animator->getAction()->getFrames() ) {
      ss << "\n\t<sprite";
      ss << " x=\"" << frame.first.getMinX() << "\"";
      ss << " y=\"" << frame.first.getMinY() << "\"";
      ss << " w=\"" << frame.first.getSize().getWidth() << "\"";
      ss << " h=\"" << frame.first.getSize().getHeight() << "\"";
      ss << " offsetX=\"" << frame.second.getX() << "\"";
      ss << " offsetY=\"" << frame.second.getY() << "\"";
      ss << " />";
    }

    ss << "\n</Animation>\n";
    _logger.info( ss.str().c_str() );
  }

  auto offset = animator->getCurrentFrameOffset();

  if ( input->getKeyDown( ALA_KEY_J ) ) {
    offset.setX( offset.getX() - 0.5f );
  }
  else if ( input->getKeyDown( ALA_KEY_L ) ) {
    offset.setX( offset.getX() + 0.5f );
  }
  else if ( input->getKeyDown( ALA_KEY_I ) ) {
    offset.setY( offset.getY() + 0.5f );
  }
  else if ( input->getKeyDown( ALA_KEY_K ) ) {
    offset.setY( offset.getY() - 0.5f );
  }

  spriteRenderer->setOffset( offset );
  animator->getAction()->getFrames()[animator->getCurrentFrameIndex()].second = offset;

  animator->pause();
}
}

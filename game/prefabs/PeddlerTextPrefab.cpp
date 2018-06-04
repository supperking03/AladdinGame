#include "PeddlerTextPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"
#include "../Macros.h"

void PeddlerTextPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();

  object->setLayer("UI");

  const auto stateManager = new ala::StateManager(object, "blink");

  auto actionManager = new ala::ActionManager(object);

  const auto timer = new ala::Timer(object);

  const auto LabelText = new ala::BitmapText(object, "font_one.png", "one.fnt");
  LabelText->setTextAlignment(ala::BitmapText::LEFT);
  LabelText->setCharacterSpacing(6);
  LabelText->setText("FIND MORE GEMS");

  object->getTransform()->setScale(1.5);
  object->getTransform()->setPosition(-115,50);


  new ala::State(stateManager, "blink", [=] {
    auto blink = new ala::Blink(0.5, -1);
    actionManager->addAction(blink);  
  }, NULL, NULL);

  new ala::State(stateManager, "gone", [=]
  {
    timer->start(5);
    actionManager->stopAll();
    LabelText->setVisible(true);
    auto moveBy = new ala::MoveBy(-2000, 5);
    actionManager->addAction(moveBy);
  }, [=](float dt)
  {
    if(timer->isDone())
    {
      object->release();
    }
  }, NULL);

  new ala::StateTransition(stateManager, "blink", "gone", [=] {
    return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW);
  });
}

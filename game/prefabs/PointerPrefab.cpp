#include "PointerPrefab.h"
#include "physics/Collider.h"
#include "physics/Rigidbody.h"
#include "../scripts/MenuController.h"

/*
* Created by kiennm97 on Nov 15th 2017
*/


void PointerPrefab::doInstantiate(ala::GameObject * object) const
{
  new ala::SpriteRenderer(object, "items.png");
  new ala::Animator(object, "menu_select", "items.anm");
  new MenuController(object);

  auto actionManager = new ala::ActionManager(object);
  auto moveBy = new ala::MoveBy(ala::Vec2(15, 0), 0.3);
  auto revert = new ala::MoveBy(ala::Vec2(-15, 0), 0.3);

  vector<ala::Action*> actions;
  actions.push_back(moveBy);
  actions.push_back(revert);
  auto sequence = new ala::Sequence(actions);
  auto repeat = new ala::Repeat(sequence, -1);
  actionManager->addAction(repeat);

}

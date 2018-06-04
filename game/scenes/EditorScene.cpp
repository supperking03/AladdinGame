/*
* 
*/

#include "EditorScene.h"
#include "../scripts/EditorController.h"

USING_NAMESPACE_ALA;

EditorScene::EditorScene() : _logger("EditorScene") {}

void EditorScene::onPreInitialize() {
  auto gameManager = GameManager::get();
  auto editor = gameManager->getPrefab("Editor")->instantiate();

  //throw-pot

  /*  auto throwPot = gameManager->getPrefab("ThrowPot")->instantiate("ThrowPot1");
    throwPot->getTransform()->setPosition(Vec2(-582.00, -132.00));*/
    //throwPot->getComponentT<ColliderRenderer>()->setZOrder(1000);

//  //ground
//  auto ground = gameManager->getPrefab("Ground")->instantiate("ground");
//  ground->getTransform()->setPosition(Vec2(-1686.00, -384.00));
//  ground->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
  //background
  auto background = new GameObject(this, "Background");
  new SpriteRenderer(background, "background.png");
  background->setLayer("Background");
//
//  auto background1 = new GameObject(this, "Background1");
//  new SpriteRenderer(background, "scene_1_1.png");
//
//  //aladdin
//  auto aladdin = new GameObject(this, "Aladdin");
//  new SpriteRenderer(aladdin, "aladdin.png");
//  new Animator(aladdin, "idle1", "aladdin.animation");
//  aladdin->getTransform()->setPosition(-2283.00, -261.00);
//
//  //camel
//  auto camel = new GameObject(this, "Camel");
//  new SpriteRenderer(camel, "camel.png");
//  new Animator(camel, "camel", "aladdin.animation");
//  camel->getTransform()->setPosition(-822.00, -285.00);
//  
//#pragma region Stair1
//  auto stair1 = new GameObject(this,"stair1");
//  auto step11 = new ala::Collider(stair1, false, ala::Vec2(0, 0), ala::Size(40, 20), 0, "Ground");
//  auto step12 = new ala::Collider(stair1, false, ala::Vec2(40, 5), ala::Size(40, 20), 0, "Ground");
//  auto step13 = new ala::Collider(stair1, false, ala::Vec2(80, 10), ala::Size(40, 20), 0, "Ground");
//  auto step14 = new ala::Collider(stair1, false, ala::Vec2(120, 15), ala::Size(40, 20), 0, "Ground");
//  auto step15 = new ala::Collider(stair1, false, ala::Vec2(160, 25), ala::Size(40, 20), 0, "Ground");
//  auto step16 = new ala::Collider(stair1, false, ala::Vec2(200, 35), ala::Size(40, 20), 0, "Ground");
//  auto step17 = new ala::Collider(stair1, false, ala::Vec2(275, 10), ala::Size(40 * 2.5 + 10, 80), 0, "Ground");
//
//  new ala::Rigidbody(stair1, ala::PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
//
//
//  auto cr11 = new ala::ColliderRenderer(step11);
//  auto cr12 = new ala::ColliderRenderer(step12);
//  auto cr13 = new ala::ColliderRenderer(step13);
//  auto cr14 = new ala::ColliderRenderer(step14);
//  auto cr15 = new ala::ColliderRenderer(step15);
//  auto cr16 = new ala::ColliderRenderer(step16);
//  auto cr17 = new ala::ColliderRenderer(step17);
//
//  cr11->setZOrder(1000);
//  cr12->setZOrder(1000);
//  cr13->setZOrder(1000);
//  cr14->setZOrder(1000);
//  cr15->setZOrder(1000);
//  cr16->setZOrder(1000);
//  cr17->setZOrder(1000);
//
//  stair1->getTransform()->setPosition(-1215.00, -276.00);
//#pragma endregion  Stair1
//
//#pragma region Stair2
//  auto stair2 = new GameObject(this, "stair2");
//  auto step21 = new ala::Collider(stair2, false, ala::Vec2(0, 0), ala::Size(40, 10), 0, "Ground");
//  auto step22 = new ala::Collider(stair2, false, ala::Vec2(35, 5), ala::Size(30, 10), 0, "Ground");
//  auto step23 = new ala::Collider(stair2, false, ala::Vec2(65, 10), ala::Size(35, 15), 0, "Ground");
//  auto step24 = new ala::Collider(stair2, false, ala::Vec2(100, 15), ala::Size(35, 25), 0, "Ground");
//  auto step25 = new ala::Collider(stair2, false, ala::Vec2(130, 25), ala::Size(35, 20), 0, "Ground");
//  auto step26 = new ala::Collider(stair2, false, ala::Vec2(175, 35), ala::Size(60, 20), 0, "Ground");
//  auto step27 = new ala::Collider(stair2, false, ala::Vec2(230, 40), ala::Size(50, 20), 0, "Ground");
//  auto step28 = new ala::Collider(stair2, false, ala::Vec2(345, 50), ala::Size(180, 20), 0, "Ground");
//
//  new ala::Rigidbody(stair2, ala::PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
//
//
//  auto cr21 = new ala::ColliderRenderer(step21);
//  auto cr22 = new ala::ColliderRenderer(step22);
//  auto cr23 = new ala::ColliderRenderer(step23);
//  auto cr24 = new ala::ColliderRenderer(step24);
//  auto cr25 = new ala::ColliderRenderer(step25);
//  auto cr26 = new ala::ColliderRenderer(step26);
//  auto cr27 = new ala::ColliderRenderer(step27);
//  auto cr28 = new ala::ColliderRenderer(step28);
//
//  cr21->setZOrder(1000);
//  cr22->setZOrder(1000);
//  cr23->setZOrder(1000);
//  cr24->setZOrder(1000);
//  cr25->setZOrder(1000);
//  cr26->setZOrder(1000);
//  cr27->setZOrder(1000);
//  cr28->setZOrder(1000);
//
//  stair2->getTransform()->setPosition(-75.00, -234.00);
//#pragma endregion  Stair2
//
//#pragma region Stair3
//  auto stair3 = new GameObject(this, "stair3");
//  auto step30 = new ala::Collider(stair3, false, ala::Vec2(300, -20), ala::Size(40, 15), 0, "Ground");
//  auto step31 = new ala::Collider(stair3, false, ala::Vec2(276, -10), ala::Size(40, 10), 0, "Ground");
//  auto step32 = new ala::Collider(stair3, false, ala::Vec2(246, 0), ala::Size(40, 10), 0, "Ground");
//  auto step33 = new ala::Collider(stair3, false, ala::Vec2(217, 8), ala::Size(35, 10), 0, "Ground");
//  auto step34 = new ala::Collider(stair3, false, ala::Vec2(185, 15), ala::Size(35, 15), 0, "Ground");
//  auto step35 = new ala::Collider(stair3, false, ala::Vec2(155, 20), ala::Size(35, 15), 0, "Ground");
//  auto step36 = new ala::Collider(stair3, false, ala::Vec2(115, 25), ala::Size(50, 20), 0, "Ground");
//  auto step37 = new ala::Collider(stair3, false, ala::Vec2(65, 35), ala::Size(55, 20), 0, "Ground");
//  auto step38 = new ala::Collider(stair3, false, ala::Vec2(35, 40), ala::Size(50, 20), 0, "Ground");
//  auto step39 = new ala::Collider(stair3, false, ala::Vec2(0, 50), ala::Size(50, 20), 0, "Ground");
//
//  new ala::Rigidbody(stair3, ala::PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
//
//  auto cr30 = new ala::ColliderRenderer(step30);
//  auto cr31 = new ala::ColliderRenderer(step31);
//  auto cr32 = new ala::ColliderRenderer(step32);
//  auto cr33 = new ala::ColliderRenderer(step33);
//  auto cr34 = new ala::ColliderRenderer(step34);
//  auto cr35 = new ala::ColliderRenderer(step35);
//  auto cr36 = new ala::ColliderRenderer(step36);
//  auto cr37 = new ala::ColliderRenderer(step37);
//  auto cr38 = new ala::ColliderRenderer(step38);
//  auto cr39 = new ala::ColliderRenderer(step39);
//
//  cr30->setZOrder(1000);
//  cr31->setZOrder(1000);
//  cr32->setZOrder(1000);
//  cr33->setZOrder(1000);
//  cr34->setZOrder(1000);
//  cr35->setZOrder(1000);
//  cr36->setZOrder(1000);
//  cr37->setZOrder(1000);
//  cr38->setZOrder(1000);
//  cr39->setZOrder(1000);
//
//  stair3->getTransform()->setPosition(-88.00, -302.00);
//#pragma endregion  Stair3
//
//#pragma region Stair4
//  auto stair4 = new GameObject(this, "stair4");
//  auto step41 = new ala::Collider(stair4, false, ala::Vec2(0, 0), ala::Size(40, 10), 0, "Ground");
//  auto step42 = new ala::Collider(stair4, false, ala::Vec2(38, 7), ala::Size(40, 15), 0, "Ground");
//  auto step43 = new ala::Collider(stair4, false, ala::Vec2(85, 15), ala::Size(50, 15), 0, "Ground");
//  auto step44 = new ala::Collider(stair4, false, ala::Vec2(125, 25), ala::Size(50, 15), 0, "Ground");
//
//  new ala::Rigidbody(stair4, ala::PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
//
//
//  auto cr41 = new ala::ColliderRenderer(step41);
//  auto cr42 = new ala::ColliderRenderer(step42);
//  auto cr43 = new ala::ColliderRenderer(step43);
//  auto cr44 = new ala::ColliderRenderer(step44);
//
//  cr41->setZOrder(1000);
//  cr42->setZOrder(1000);
//  cr43->setZOrder(1000);
//  cr44->setZOrder(1000);
//
//  stair4->getTransform()->setPosition(1989.00, -309.00);
//#pragma endregion  Stair4
//
//#pragma region Stair5
//  auto stair5 = new GameObject(this, "stair5");
//  auto step51 = new ala::Collider(stair5, false, ala::Vec2(0, 0), ala::Size(40, 10), 0, "Ground");
//  auto step52 = new ala::Collider(stair5, false, ala::Vec2(38, 7), ala::Size(40, 15), 0, "Ground");
//  auto step53 = new ala::Collider(stair5, false, ala::Vec2(80, 15), ala::Size(50, 15), 0, "Ground");
//  auto step54 = new ala::Collider(stair5, false, ala::Vec2(125, 25), ala::Size(50, 15), 0, "Ground");
//  auto step55 = new ala::Collider(stair5, false, ala::Vec2(190, 35), ala::Size(90, 15), 0, "Ground");
//
//  new ala::Rigidbody(stair5, ala::PhysicsMaterial(10, 0.5), ALA_BODY_TYPE_STATIC, 0);
//
//
//  auto cr51 = new ala::ColliderRenderer(step51);
//  auto cr52 = new ala::ColliderRenderer(step52);
//  auto cr53 = new ala::ColliderRenderer(step53);
//  auto cr54 = new ala::ColliderRenderer(step54);
//  auto cr55 = new ala::ColliderRenderer(step55);
//
//  cr51->setZOrder(1000);
//  cr52->setZOrder(1000);
//  cr53->setZOrder(1000);
//  cr54->setZOrder(1000);
//  cr55->setZOrder(1000);
//
//
//  stair5->getTransform()->setPosition(1455.00, -141.00);
//#pragma endregion  Stair5
//
//
//  //Rope
//  auto rope1 = gameManager->getPrefab("Rope")->instantiate("Rope");
//  rope1->getTransform()->setPosition(Vec2(-294.00, -123.00));
//  rope1->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto rope2 = gameManager->getPrefab("Rope")->instantiate("Rope2");
//  rope2->getComponentT<Collider>()->setSize(Size(1, 245));
//  rope2->getTransform()->setPosition(Vec2(-837.00, 81.00));
//  rope2->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto rope3 = gameManager->getPrefab("Rope")->instantiate("Rope3");
//  rope3->getComponentT<Collider>()->setSize(Size(1, 265));
//  rope3->getTransform()->setPosition(Vec2(314.00, 135.00));
//  rope3->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto rope4 = gameManager->getPrefab("Rope")->instantiate("Rope4");
//  rope4->getComponentT<Collider>()->setSize(Size(1, 225));
//  rope4->getTransform()->setPosition(Vec2(2328.00,-120.00));
//  rope4->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  //wall
//  auto wall1 = gameManager->getPrefab("Wall")->instantiate("Wall1");
//  wall1->getComponentT<Collider>()->setSize(Size(40, 470));
//  wall1->getTransform()->setPosition(Vec2(-930.00,126.00));
//  wall1->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall2 = gameManager->getPrefab("Wall")->instantiate("Wall2");
//  wall2->getComponentT<Collider>()->setSize(Size(40, 400));
//  wall2->getTransform()->setPosition(Vec2(-162.00,-141.00));
//  wall2->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall3 = gameManager->getPrefab("Wall")->instantiate("Wall3");
//  wall3->getComponentT<Collider>()->setSize(Size(25, 215));
//  wall3->getTransform()->setPosition(Vec2(126.00,237.00));
//  wall3->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall4 = gameManager->getPrefab("Wall")->instantiate("Wall4");
//  wall4->getComponentT<Collider>()->setSize(Size(40, 240));
//  wall4->getTransform()->setPosition(Vec2(240.00,51.00));
//  wall4->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall5 = gameManager->getPrefab("Wall")->instantiate("Wall5");
//  wall5->getComponentT<Collider>()->setSize(Size(25, 85));
//  wall5->getTransform()->setPosition(Vec2(660.00,-129.00));
//  wall5->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall6 = gameManager->getPrefab("Wall")->instantiate("Wall6");
//  wall6->getComponentT<Collider>()->setSize(Size(40, 100));
//  wall6->getTransform()->setPosition(Vec2(1200.00,168.00));
//  wall6->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall7 = gameManager->getPrefab("Wall")->instantiate("Wall7");
//  wall7->getComponentT<Collider>()->setSize(Size(40, 228));
//  wall7->getTransform()->setPosition(Vec2(2334.00, 234.00));
//  wall7->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall8 = gameManager->getPrefab("Wall")->instantiate("Wall8");
//  wall8->getComponentT<Collider>()->setSize(Size(25, 26));
//  wall8->getTransform()->setPosition(Vec2(789.00, 30.00));
//  wall8->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto wall9 = gameManager->getPrefab("Wall")->instantiate("Wall9");
//  wall9->getComponentT<Collider>()->setSize(Size(30, 95));
//  wall9->getTransform()->setPosition(Vec2(-924.00, -279.00));
//  wall9->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  //Platform
//  auto platform1 = gameManager->getPrefab("Platform")->instantiate("platform1");
//  platform1->getComponentT<Collider>()->setSize(Size(102, 5));
//  platform1->getTransform()->setPosition(Vec2(-861.00,-99.00));
//  platform1->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform2 = gameManager->getPrefab("Platform")->instantiate("platform2");
//  platform2->getComponentT<Collider>()->setSize(Size(45, 5));
//  platform2->getTransform()->setPosition(Vec2(-891.00,-51.00));
//  platform2->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform3 = gameManager->getPrefab("Platform")->instantiate("platform3");
//  platform3->getComponentT<Collider>()->setSize(Size(290, 5));
//  platform3->getTransform()->setPosition(Vec2(-489.00, -99.00));
//  platform3->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform4 = gameManager->getPrefab("Platform")->instantiate("platform4");
//  platform4->getComponentT<Collider>()->setSize(Size(682, 5));
//  platform4->getTransform()->setPosition(Vec2(-450.00, 60.00));
//  platform4->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform5 = gameManager->getPrefab("Platform")->instantiate("platform5");
//  platform5->getComponentT<Collider>()->setSize(Size(129, 5));
//  platform5->getTransform()->setPosition(Vec2(201.00,171.00));
//  platform5->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform6 = gameManager->getPrefab("Platform")->instantiate("platform6");
//  platform6->getComponentT<Collider>()->setSize(Size(79, 5));
//  platform6->getTransform()->setPosition(Vec2(402.00, 171.00));
//  platform6->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform7 = gameManager->getPrefab("Platform")->instantiate("platform7");
//  platform7->getComponentT<Collider>()->setSize(Size(220, 5));
//  platform7->getTransform()->setPosition(Vec2(696.00, 171.00));
//  platform7->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform8 = gameManager->getPrefab("Platform")->instantiate("platform8");
//  platform8->getComponentT<Collider>()->setSize(Size(376, 5));
//  platform8->getTransform()->setPosition(Vec2(621.00, 45.00));
//  platform8->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform9 = gameManager->getPrefab("Platform")->instantiate("platform9");
//  platform9->getComponentT<Collider>()->setSize(Size(107, 5));
//  platform9->getTransform()->setPosition(Vec2(1173.00, 219.00));
//  platform9->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform10 = gameManager->getPrefab("Platform")->instantiate("platform10");
//  platform10->getComponentT<Collider>()->setSize(Size(1122, 5));
//  platform10->getTransform()->setPosition(Vec2(1779.00, 123.00));
//  platform10->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform11 = gameManager->getPrefab("Platform")->instantiate("platform11");
//  platform11->getComponentT<Collider>()->setSize(Size(178, 5));
//  platform11->getTransform()->setPosition(Vec2(342.00, -69.00));
//  platform11->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform12 = gameManager->getPrefab("Platform")->instantiate("platform12");
//  platform12->getComponentT<Collider>()->setSize(Size(269, 5));
//  platform12->getTransform()->setPosition(Vec2(564.00, -84.00));
//  platform12->getComponentT<ColliderRenderer>()->setZOrder(1000);
//  
//  auto platform13 = gameManager->getPrefab("Platform")->instantiate("platform13");
//  platform13->getComponentT<Collider>()->setSize(Size(441, 5));
//  platform13->getTransform()->setPosition(Vec2(1017.00, 18.00));
//  platform13->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform14 = gameManager->getPrefab("Platform")->instantiate("platform14");
//  platform14->getComponentT<Collider>()->setSize(Size(90, 5));
//  platform14->getTransform()->setPosition(Vec2(1965.00, -129.00));
//  platform14->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform15 = gameManager->getPrefab("Platform")->instantiate("platform15");
//  platform15->getComponentT<Collider>()->setSize(Size(75, 5));
//  platform15->getTransform()->setPosition(Vec2(2262.00, -162.00));
//  platform15->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform16 = gameManager->getPrefab("Platform")->instantiate("platform16");
//  platform16->getComponentT<Collider>()->setSize(Size(75, 5));
//  platform16->getTransform()->setPosition(Vec2(2262.00, -162.00));
//  platform16->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform17 = gameManager->getPrefab("Platform")->instantiate("platform17");
//  platform17->getComponentT<Collider>()->setSize(Size(300, 5));
//  platform17->getTransform()->setPosition(Vec2(2238.00, -279.00));
//  platform17->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform18 = gameManager->getPrefab("Platform")->instantiate("platform18");
//  platform18->getComponentT<Collider>()->setSize(Size(767, 5));
//  platform18->getTransform()->setPosition(Vec2(1053.00, -147.00));
//  platform18->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform19 = gameManager->getPrefab("Platform")->instantiate("platform19");
//  platform19->getComponentT<Collider>()->setSize(Size(107, 5));
//  platform19->getTransform()->setPosition(Vec2(402.00, -228.00));
//  platform19->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform20 = gameManager->getPrefab("Platform")->instantiate("platform20");
//  platform20->getComponentT<Collider>()->setSize(Size(50, 2000));
//  platform20->getTransform()->setPosition(Vec2(2409.00, -45.00));
//  platform20->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform21 = gameManager->getPrefab("Platform")->instantiate("platform21");
//  platform21->getComponentT<Collider>()->setSize(Size(50, 2000));
//  platform21->getTransform()->setPosition(Vec2(-2409.00, 117.00));
//  platform21->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform22 = gameManager->getPrefab("Platform")->instantiate("platform22");
//  platform22->getComponentT<Collider>()->setSize(Size(50, 10));
//  platform22->getTransform()->setPosition(Vec2(-117.00, -240.00));
//  platform22->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto platform23 = gameManager->getPrefab("Platform")->instantiate("platform23");
//  platform23->getComponentT<Collider>()->setSize(Size(73, 10));
//  platform23->getTransform()->setPosition(Vec2(-924.00, -228.00));
//  platform23->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//
//  //hanger
//  auto hanger1 = gameManager->getPrefab("Hanger")->instantiate("hanger1");
//  hanger1->getComponentT<Collider>()->setSize(Size(415, 2));
//  hanger1->getTransform()->setPosition(Vec2(2178.00, 33.00));
//  hanger1->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto hanger2 = gameManager->getPrefab("Hanger")->instantiate("hanger2");
//  hanger2->getComponentT<Collider>()->setSize(Size(200, 2));
//  hanger2->getTransform()->setPosition(Vec2(2070.00, 258.00));
//  hanger2->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  //spin
//  auto spin1 = gameManager->getPrefab("Spin")->instantiate("spin1");
//  spin1->getComponentT<Collider>()->setSize(Size(15, 5));
//  spin1->getTransform()->setPosition(Vec2(1866.00, 195.00));
//  spin1->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto spin2 = gameManager->getPrefab("Spin")->instantiate("spin2");
//  spin2->getComponentT<Collider>()->setSize(Size(15, 5));
//  spin2->getTransform()->setPosition(Vec2(1083.00, 90.00));
//  spin2->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
//  auto spin3 = gameManager->getPrefab("Spin")->instantiate("spin3");
//  spin3->getComponentT<Collider>()->setSize(Size(15, 5));
//  spin3->getTransform()->setPosition(Vec2(1110.00,159.00));
//  spin3->getComponentT<ColliderRenderer>()->setZOrder(1000);
//
  //enemy_guard
  auto enemy_guard1 = new GameObject(this, "enemy_guard1");
  auto srEnemy_guard1 = new ala::SpriteRenderer(enemy_guard1, "guards.png");
  new Animator(enemy_guard1, "fat_guard_run", "guards.anm"); 
  enemy_guard1->getTransform()->setPosition(-1671.00, -261.00);
  enemy_guard1->getComponentT<SpriteRenderer>()->setZOrder(1000);
  enemy_guard1->getTransform()->setScaleX(-1);
//
//  auto enemy_guard2 = new GameObject(this, "enemy_guard2");
//  auto srEnemy_guard2 = new ala::SpriteRenderer(enemy_guard2, "guards.png");
//  new Animator(enemy_guard2, "enemy_guard_attack", "guards.anm");
//  enemy_guard2->getTransform()->setPosition(342.00, -42.00);
//  enemy_guard2->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
//  //fat_guard
//  auto fat_guard1 = new GameObject(this, "fat_guard1");
//  auto srFat_guard1 = new ala::SpriteRenderer(fat_guard1, "guards.png");
//  new Animator(fat_guard1, "fat_guard_run", "guards.anm");
//  fat_guard1->getTransform()->setPosition(-1416.00, -261.00);
//  fat_guard1->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
//  auto fat_guard2 = new GameObject(this, "fat_guard2");
//  auto srFat_guard2 = new ala::SpriteRenderer(fat_guard2, "guards.png");
//  new Animator(fat_guard2, "fat_guard_run", "guards.anm");
//  fat_guard2->getTransform()->setPosition(-654.00, 90.00);
//  fat_guard2->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
//  //adorable_guard
//  auto adorable_guard1 = new GameObject(this, "adorable_guard1");
//  auto srAdorable_guard1 = new ala::SpriteRenderer(adorable_guard1, "guards.png");
//  new Animator(adorable_guard1, "adorable_guard_run", "guards.anm");
//  adorable_guard1->getTransform()->setPosition(-660.00, -282.00);
//  adorable_guard1->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
//  auto adorable_guard2 = new GameObject(this, "adorable_guard2");
//  auto srAdorable_guard2 = new ala::SpriteRenderer(adorable_guard2, "guards.png");
//  new Animator(adorable_guard2, "adorable_guard_run", "guards.anm");
//  adorable_guard2->getTransform()->setPosition(-483.00, -69.00);
//  adorable_guard2->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
//  auto adorable_guard3 = new GameObject(this, "adorable_guard3");
//  auto srAdorable_guard3 = new ala::SpriteRenderer(adorable_guard3, "guards.png");
//  new Animator(adorable_guard3, "adorable_guard_run", "guards.anm");
//  adorable_guard3->getTransform()->setPosition(-327.00, 90.00);
//  adorable_guard3->getComponentT<SpriteRenderer>()->setZOrder(1000);
//
  auto explosion =gameManager->getPrefab("Explosion")->instantiate("Explosion1");
  explosion->getTransform()->setPosition(Vec2(2409.00, -45.00));


  std::vector<GameObject*> objects;
  objects.push_back(explosion);
  objects.push_back(enemy_guard1);
 /* objects.push_back(enemy_guard2);
  objects.push_back(fat_guard2);
  objects.push_back(adorable_guard3);
  objects.push_back(adorable_guard2);
  objects.push_back(adorable_guard1);
  objects.push_back(fat_guard1);
  objects.push_back(enemy_guard1);
  objects.push_back(stair5);
  objects.push_back(stair4);
  objects.push_back(wall9);
  objects.push_back(platform23);
  objects.push_back(stair3);
  objects.push_back(stair2);
  objects.push_back(platform22);
  objects.push_back(stair1);
  objects.push_back(spin3);
  objects.push_back(spin2);
  objects.push_back(spin1);
  objects.push_back(hanger2);
  objects.push_back(hanger1);
  objects.push_back(platform21);
  objects.push_back(platform20);
  objects.push_back(platform19);
  objects.push_back(wall8);
  objects.push_back(wall7);
  objects.push_back(platform18);
  objects.push_back(platform17);
  objects.push_back(platform16);
  objects.push_back(platform15);
  objects.push_back(platform14);
  objects.push_back(platform13);
  objects.push_back(platform12);
  objects.push_back(platform11);
  objects.push_back(platform10);
  objects.push_back(platform9);
  objects.push_back(platform8);
  objects.push_back(platform7);
  objects.push_back(platform6);
  objects.push_back(platform5);
  objects.push_back(platform4);
  objects.push_back(platform3);
  objects.push_back(platform2);
  objects.push_back(platform1);
  objects.push_back(wall6);
  objects.push_back(wall5);
  objects.push_back(aladdin);*/
  //objects.push_back(background);
  //objects.push_back(camel);
  //objects.push_back(ground);
  //objects.push_back(rope1);
  //objects.push_back(rope2);
  //objects.push_back(rope3);
  //objects.push_back(rope4);
  //objects.push_back(wall1);
  //objects.push_back(wall2);
  //objects.push_back(wall3);
  //objects.push_back(wall4);


  auto editorController = editor->getComponentT<EditorController>();
  editorController->setGameObjects(objects);
}

void EditorScene::onPreRelease() {}

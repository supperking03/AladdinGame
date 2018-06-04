/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BasicExamplePrefab.h"
#include "../prefabs/AnimationAndStateExamplePrefab.h"
#include "../prefabs/AladdinPrefab.h"

#include "../../aladdin/2d/Sprite.h"
#include "../prefabs/ThrowingApplePrefab.h"

#include "../prefabs/EditorPrefab.h"
#include "../prefabs/PointerPrefab.h"
#include "../prefabs/JafarPrefab.h"
#include "../prefabs/JafarFirePrefab.h"
#include "../prefabs/JafarSpellPrefab.h"
#include "../prefabs/PotDropperPrefab.h"
#include "../prefabs/PotPrefab.h"
#include "../prefabs/StaffGuardPrefab.h"
#include "../prefabs/SwordGuardPrefab.h"
#include "../prefabs/ExplosionPrefab.h"
#include "../prefabs/KnifeJugglerPrefab.h"
#include "../prefabs/ThrowingKnifePrefab.h"
#include "../prefabs/KnifeGuardPrefab.h"
#include "core/MapResource.h"
#include "../prefabs/CollectableApplePrefab.h"
#include "../prefabs/AppleThiefPrefab.h"
#include "../prefabs/TwinklePrefab.h"
#include "../prefabs/CheckpointPrefab.h"
#include "../prefabs/ExtraHealthPrefab.h"
#include "../prefabs/SpendThesePrefab.h"
#include "../prefabs/GenieBonusPrefab.h"
#include "../prefabs/FallingPlatformPrefab.h"
#include "../prefabs/UIPrefab.h"
#include "../prefabs/CamelPrefab.h"
#include "../prefabs/SalivaPrefab.h"
#include "../prefabs/AladdinHeadPrefab.h"
#include "../prefabs/LampPrefab.h"
#include "../prefabs/AbuHeadPrefab.h"
#include "../prefabs/FlamePrefab.h"
#include "../prefabs/SpringPrefab.h"
#include "../prefabs/AudioEventListenerPrefab.h"
#include "../prefabs/LevelCompletePrefab.h"
#include "../prefabs/BigTwinklePrefab.h"
#include "../prefabs/NormalTwinklePrefab.h"
#include "../prefabs/BigExplosionPrefab.h"
#include "../prefabs/PlayMenuPrefab.h"
#include "../prefabs/OptionMenuPrefab.h"
#include "../GameData.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../prefabs/PeddlerPrefab.h"
#include "../prefabs/PeddlerTextPrefab.h"
#include "../prefabs/SkyPrefab.h"
#include "../prefabs/SandPrefab.h"
#include "../prefabs/JafarForegroundPrefab.h"
#include "../prefabs/FadeInEffectPrefab.h"
#include "../prefabs/AladdinSceneFadeOutTransitionPrefab.h"
#include "../prefabs/CompleteSceneFadeOutTransitionPrefab.h"
#include "../prefabs/DieSceneFadeOutTransitionPrefab.h"
#include "../prefabs/MenuSceneFadeOutTransitionPrefab.h"
#include "../prefabs/RetrySceneFadeOutTransitionPrefab.h"


USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameData = GameData::get();
  gameData->setInt(APPLE_DATA_KEY, 0);
  gameData->setInt(LIVES_DATA_KEY, 0);
  gameData->setInt(RUBY_DATA_KEY, 0);
  gameData->setInt(SCORE_DATA_KEY, 0);
  gameData->setInt(HEALTH_DATA_KEY, 0);
  gameData->setString(HAS_CHECKPOINT_KEY, "FALSE");
  gameData->setFloat(CHECKPOINT_DATA_X_KEY, std::numeric_limits<float>::max());
  gameData->setFloat(CHECKPOINT_DATA_Y_KEY, std::numeric_limits<float>::max());
  gameData->setString(BGM_KEY, "ON");
  gameData->setString(SFX_KEY, "ON");
  gameData->setString(DIFFICULTY_KEY, "EASY");

  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer("Parallax");
  gameManager->addLayer("Background");
  gameManager->addLayer("NPCs");
  gameManager->addLayer("Character");
  gameManager->addLayer("Items");
  gameManager->addLayer("Effects");
  gameManager->addLayer("Foreground");
  gameManager->addLayer("UI");
  gameManager->addLayer("Overlay");

  // Textures
  new Sprite("AgrabahMarketBackground.png", "textures/backgrounds/scene_1_0.png");
  new Sprite("AgrabahMarketForeground.png", "textures/backgrounds/scene_1_1.png");
  new Sprite("aladdin.png", "textures/playable_characters/aladdin.png");
  new Sprite("camel.png", "textures/nonplayable_characters/camel.png");
  new Sprite("cutscenes.png", "textures/miscellaneous/cutscenes.png");
  new Sprite("items.png", "textures/miscellaneous/items.png");
  new Sprite("numbers.png", "textures/miscellaneous/numbers.png");
  new Sprite("guards.png", "textures/enemies/guards.png");
  new Sprite("civilian-enemies.png", "textures/enemies/civilian-enemies.png");
  new Sprite("jafar.png", "textures/bosses/jafar.png");
  new Sprite("aladdinPoster.png", "textures/miscellaneous/aladdinPoster.png");
  new ala::Sprite("abu_end.png", "textures/nonplayable_characters/abu_end.png");
  new ala::Sprite("abu_victory.png", "textures/nonplayable_characters/abu_victory.png");

  new Sprite("enemy_explosion.png", "textures/enemies/enemy_explosion.png");
  new Sprite("twinkle.png", "textures/miscellaneous/enemy_explosions.png");
  new Sprite("fallingplatform.png", "textures/backgrounds/fallingplatform.png");
  new Sprite("backgroundJarfarfront.png", "textures/backgrounds/backgroundJarfarfront.png");
  new Sprite("jafar_palace_parallax.png", "textures/backgrounds/jafar_palace_parallax.png");
  new Sprite("ruby.png", "textures/miscellaneous/ruby.png");
  new Sprite("font_one.png", "textures/miscellaneous/font_one.png");
  new Sprite("font_two.png", "textures/miscellaneous/font_two.png");
  new Sprite("victory.png", "textures/miscellaneous/victory.png");
  new Sprite("lamp.png", "textures/miscellaneous/lamp.png");
  new Sprite("ItemsExplored.png", "textures/miscellaneous/ItemsExplored.png");
  new Sprite("enemy_explosions.png", "textures/miscellaneous/enemy_explosions.png");
  new Sprite("retry.png", "textures/miscellaneous/retry.png");
  new Sprite("abu.png", "textures/nonplayable_characters/abu.png");
  new Sprite("peddler.png", "textures/nonplayable_characters/peddler.png");
  new Sprite("agrabah_market_parallax.png", "textures/backgrounds/parallax.png");
  // Fonts
  new Font("crackman.ttf", "crackman.ttf", "fonts");
  new Font("aladdin.ttf", "aladdin.ttf", "fonts");
  new Font("arcade.ttf", "arcade.ttf", "fonts");
  new BitmapFont("one.fnt", "fonts/one.fnt");
  new BitmapFont("two.fnt", "fonts/two.fnt");



  // Animations
  new Animation("aladdin.anm", "animations/playable_characters/aladdin.anm");
  new Animation("camel.anm", "animations/nonplayable_characters/camel.anm");
  new Animation("cutscenes.anm", "animations/miscellaneous/cutscenes.anm");
  new Animation("items.anm", "animations/miscellaneous/items.anm");
  new Animation("numbers.anm", "animations/miscellaneous/numbers.anm");
  new Animation("guards.anm", "animations/enemies/guards.anm");
  new Animation("jafar.anm", "animations/bosses/jafar.anm");
  new Animation("civilian-enemies.anm", "animations/enemies/civilian-enemies.anm");
  new Animation("apple.anm", "animations/miscellaneous/apple.anm");
  new Animation("abu.anm", "animations/nonplayable_characters/abu.anm");
  new Animation("peddler.anm", "animations/nonplayable_characters/peddler.anm");
  new Animation("agrabah_market_parallax.anm", "animations/backgrounds/parallax.anm");

  // Audio clips
  new AudioClip("AgrabahMarket.wav", "audio/background/AgrabahMarket.wav");

  new AudioClip("AladdinHurt.wav", "audio/sfx/AladdinHurt.wav");
  new AudioClip("AladdinOof.wav", "audio/sfx/AladdinOof.wav");
  new AudioClip("AppleCollect.wav", "audio/sfx/AppleCollect.wav");
  new AudioClip("AppleSplat.wav", "audio/sfx/AppleSplat.wav");
  new AudioClip("CamelSpit.wav", "audio/sfx/CamelSpit.wav");
  new AudioClip("ClayPot.wav", "audio/sfx/ClayPot.wav");
  new AudioClip("CloudPoof.wav", "audio/sfx/CloudPoof.wav");
  new AudioClip("ExtraHealth.wav", "audio/sfx/ExtraHealth.wav");
  new AudioClip("FireFromCoal.wav", "audio/sfx/FireFromCoal.wav");
  new AudioClip("Flagpole.wav", "audio/sfx/Flagpole.wav");
  new AudioClip("GenieFumes.wav", "audio/sfx/GenieFumes.wav");
  new AudioClip("Guard'sPants.wav", "audio/sfx/Guard'sPants.wav");
  new AudioClip("GuardBeckon.wav", "audio/sfx/GuardBeckon.wav");
  new AudioClip("GuardHit1.wav", "audio/sfx/GuardHit1.wav");
  new AudioClip("GuardHit2.wav", "audio/sfx/GuardHit2.wav");
  new AudioClip("HighSword.wav", "audio/sfx/HighSword.wav");
  new AudioClip("JafarLaugh.wav", "audio/sfx/JafarLaugh.wav");
  new AudioClip("JafarSnake.wav", "audio/sfx/JafarSnake.wav");
  new AudioClip("LowSword.wav", "audio/sfx/LowSword.wav");
  new AudioClip("MenuChange.wav", "audio/sfx/MenuChange.wav");
  new AudioClip("MenuSelect.wav", "audio/sfx/MenuSelect.wav");
  new AudioClip("ObjectThrow.wav", "audio/sfx/ObjectThrow.wav");
  new AudioClip("SwordChing.wav", "audio/sfx/SwordChing.wav");
  new AudioClip("SwordSpinning.wav", "audio/sfx/SwordSpinning.wav");
  new AudioClip("Continue Point.wav", "audio/sfx/Continue Point.wav");
  new AudioClip("Gem Collect.wav", "audio/sfx/Gem Collect.wav");
  new AudioClip("Aladdin Push.wav", "audio/sfx/Aladdin Push.wav");
  new AudioClip("Wow.wav", "audio/sfx/Wow.wav");
  new AudioClip("Aaah.wav", "audio/sfx/Aaah.wav");
  new AudioClip("LevelComplete.wav", "audio/background/LevelComplete.wav");
  new AudioClip("AWholeNewWorld.wav", "audio/background/AWholeNewWorld.wav");
  new AudioClip("BossTune.wav", "audio/background/BossTune.wav");

  // Maps
  new MapResource("AgrabahMarket.tmx", "maps/AgrabahMarket.tmx");
  new MapResource("JafarBoss.tmx", "maps/JafarBoss.tmx");

  // Prefabs
  new AnimationAndStateExamplePrefab();
  new BasicExamplePrefab();
  new AladdinPrefab();
  new ThrowingApplePrefab();

  new EditorPrefab();
  new OptionMenuPrefab();
  new PointerPrefab();
  new PotDropperPrefab();
  new StaffGuardPrefab();
  new PotPrefab();
  new KnifeJugglerPrefab();
  new ThrowingKnifePrefab();
  new SwordGuardPrefab();
  new ExplosionPrefab();
  new KnifeGuardPrefab();
  new CollectableApplePrefab();
  new JafarPrefab();
  new JafarSpellPrefab();
  new AppleThiefPrefab();
  new TwinklePrefab();
  new UIPrefab();
  new CheckpointPrefab();
  new ExtraHealthPrefab();
  new SpendThesePrefab();
  new GenieBonusPrefab();
  new CamelPrefab();
  new SalivaPrefab();
  new FallingPlatformPrefab();
  new FlamePrefab();
  new AladdinHeadPrefab();
  new LampPrefab();
  new AbuHeadPrefab();
  new SpringPrefab();
  new AudioEventListenerPrefab();
  new JafarFirePrefab();
  new LevelCompletePrefab();
  new BigTwinklePrefab();
  new NormalTwinklePrefab();
  new BigExplosionPrefab();
  new PlayMenuPrefab();
  new PeddlerPrefab();
  new PeddlerTextPrefab();
  new SkyPrefab();
  new SandPrefab();
  new JafarForegroundPrefab();
  new AladdinSceneFadeOutTransitionPrefab();
  new CompleteSceneFadeOutTransitionPrefab();
  new DieSceneFadeOutTransitionPrefab();
  new MenuSceneFadeOutTransitionPrefab();
  new RetrySceneFadeOutTransitionPrefab();
  new FadeInEffectPrefab();
}

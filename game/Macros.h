﻿#ifndef __GAME_MACROS_H__
#define __GAME_MACROS_H__

enum
{
  ALADDIN_TAG,
  ENEMY_TAG,
  GROUND_TAG,
  WALL_TAG,
  ROPE_TAG,
  HANGER_TAG,
  BACKGROUND_TAG,
  FOREGROUND_TAG,
  ALADDIN_WEAPON_TAG,
  ENEMY_WEAPON_TAG,
  CHARCOAL_BURNER_TAG,
  ROPE_CHECKER_TAG,
  HANGER_CHECKER_TAG,
  COLLECTABLE_ITEM_TAG,
  MAP_BLOCKER_TAG,
  NPC_TAG,
  SPRING_TAG,
  STAIR_CHECKER_TAG,
  JAFAR_TAG,
  SHOP_5_TAG,
  SHOP_10_TAG
};

enum
{
  AI_STATE_IDLE,
  AI_STATE_FOLLOW,
  AI_STATE_ATTACK,
  AI_STATE_THROW_NORMAL,
  AI_STATE_THROW_ROTATE
};

#ifndef OPEN_OPTION_SCENE_MESSAGE
#define OPEN_OPTION_SCENE_MESSAGE "OPEN_OPTION_SCENE_MESSAGE"
#endif //!OPEN_OPTION_SCENE_MESSAGE

#ifndef OPEN_PLAY_SCENE_MESSAGE
#define OPEN_PLAY_SCENE_MESSAGE "OPEN_PLAY_SCENE_MESSAGE"
#endif //!OPEN_PLAY_SCENE_MESSAGE

#ifndef WEAPON_TYPE_ALADDIN_SWORD
#define WEAPON_TYPE_ALADDIN_SWORD "WEAPON_TYPE_ALADDIN_SWORD"
#endif //!WEAPON_TYPE_ALADDIN_SWORD

#ifndef WEAPON_TYPE_ALADDIN_APPLE
#define WEAPON_TYPE_ALADDIN_APPLE "WEAPON_TYPE_ALADDIN_APPLE"
#endif //!WEAPON_TYPE_ALADDIN_APPLE

#ifndef WEAPON_TYPE_ALADDIN_SALIVA
#define WEAPON_TYPE_ALADDIN_SALIVA "WEAPON_TYPE_ALADDIN_SALIVA"
#endif //!WEAPON_TYPE_ALADDIN_SALIVA

#ifndef WEAPON_TYPE_ALADDIN_LAMP
#define WEAPON_TYPE_ALADDIN_LAMP "WEAPON_TYPE_ALADDIN_LAMP"
#endif //!WEAPON_TYPE_ALADDIN_LAMP

#ifndef WEAPON_TYPE_ALADDIN_KNIFE
#define WEAPON_TYPE_ALADDIN_KNIFE "WEAPON_TYPE_ALADDIN_KNIFE"
#endif //!WEAPON_TYPE_ALADDIN_KNIFE

#ifndef WEAPON_TYPE_ENEMY_KNIFE
#define WEAPON_TYPE_ENEMY_KNIFE "WEAPON_TYPE_ENEMY_KNIFE"
#endif //!WEAPON_TYPE_ENEMY_KNIFE

#ifndef WEAPON_TYPE_ENEMY_SWORD
#define WEAPON_TYPE_ENEMY_SWORD "WEAPON_TYPE_ENEMY_SWORD"
#endif //!WEAPON_TYPE_ENEMY_SWORD

#ifndef WEAPON_TYPE_ENEMY_STAFF
#define WEAPON_TYPE_ENEMY_STAFF "WEAPON_TYPE_ENEMY_STAFF"
#endif //!WEAPON_TYPE_ENEMY_STAFF

#ifndef WEAPON_TYPE_ENEMY_STEAL
#define WEAPON_TYPE_ENEMY_STEAL "WEAPON_TYPE_ENEMY_STEAL"
#endif //!WEAPON_TYPE_ENEMY_STEAL

#ifndef WEAPON_TYPE_ENEMY_POT
#define WEAPON_TYPE_ENEMY_POT "WEAPON_TYPE_ENEMY_POT"
#endif //!WEAPON_TYPE_ENEMY_POT

#ifndef WEAPON_TYPE_ENEMY_FLAME
#define WEAPON_TYPE_ENEMY_FLAME "WEAPON_TYPE_ENEMY_FLAME"
#endif //!WEAPON_TYPE_ENEMY_FLAME

#ifndef WEAPON_TYPE_ENEMY_SPELL
#define WEAPON_TYPE_ENEMY_SPELL "WEAPON_TYPE_ENEMY_SPELL"
#endif //!WEAPON_TYPE_ENEMY_SPELL

#ifndef WEAPON_TYPE_ENEMY_FIRE
#define WEAPON_TYPE_ENEMY_FIRE "WEAPON_TYPE_ENEMY_FIRE"
#endif //!WEAPON_TYPE_ENEMY_FIRE

#ifndef WEAPON_TYPE_JAFAR
#define WEAPON_TYPE_JAFAR "WEAPON_TYPE_JAFAR"
#endif //!WEAPON_TYPE_JAFAR

#ifndef TURN_ON_CHARCOALBURNER_MESSAGE
#define TURN_ON_CHARCOALBURNER_MESSAGE "TURN_ON_CHARCOALBURNER_MESSAGE"
#endif //!TURN_ON_CHARCOALBURNER_MESSAGE

#ifndef SPAWN_APPLE_MESSAGE
#define SPAWN_APPLE_MESSAGE "SPAWN_APPLE_MESSAGE"
#endif //!SPAWN_APPLE_MESSAGE

#ifndef UI_CHANGED_MESSAGE
#define UI_CHANGED_MESSAGE "UI_CHANGED_MESSAGE"
#endif //!UI_CHANGED_MESSAGE

#ifndef APPLE_THROWED_MESSAGE
#define APPLE_THROWED_MESSAGE "APPLE_THROWED_MESSAGE"
#endif //!APPLE_THROWED_MESSAGE

#ifndef APPLE_ACQUIRED_MESSAGE
#define APPLE_ACQUIRED_MESSAGE "APPLE_ACQUIRED_MESSAGE"
#endif //!APPLE_ACQUIRED_MESSAGE

#ifndef LIVES_ACQUIRED_MESSAGE
#define LIVES_ACQUIRED_MESSAGE "LIVES_ACQUIRED_MESSAGE"
#endif //!LIVES_ACQUIRED_MESSAGE

#ifndef HEALTH_ACQUIRED_MESSAGE
#define HEALTH_ACQUIRED_MESSAGE "HEALTH_ACQUIRED_MESSAGE"
#endif //!HEALTH_ACQUIRED_MESSAGE

#ifndef HEALTH_LOST_MESSAGE
#define HEALTH_LOST_MESSAGE "HEALTH_LOST_MESSAGE"
#endif //!HEALTH_LOST_MESSAGE

#ifndef APPLE_STOLEN_MESSAGE
#define APPLE_STOLEN_MESSAGE "APPLE_STOLEN_MESSAGE"
#endif //!APPLE_STOLEN_MESSAGE

#ifndef SCORE_ACQUIRED_MESSAGE
#define SCORE_ACQUIRED_MESSAGE "SCORE_ACQUIRED_MESSAGE"
#endif //!SCORE_ACQUIRED_MESSAGE

#ifndef RUBY_ACQUIRED_MESSAGE
#define RUBY_ACQUIRED_MESSAGE "RUBY_ACQUIRED_MESSAGE"
#endif //!RUBY_ACQUIRED_MESSAGE

#ifndef RUBY_LOST_MESSAGE
#define RUBY_LOST_MESSAGE "RUBY_LOST_MESSAGE"
#endif //!RUBY_LOST_MESSAGE

#ifndef CHECKPOINT_CHECKED_MESSAGE
#define CHECKPOINT_CHECKED_MESSAGE "CHECKPOINT_CHECKED_MESSAGE"
#endif //!CHECKPOINT_CHECKED_MESSAGE

#ifndef ALADDIN_OUT_OF_HEALTH_MESSAGE
#define ALADDIN_OUT_OF_HEALTH_MESSAGE "ALADDIN_OUT_OF_HEALTH_MESSAGE"
#endif //!ALADDIN_OUT_OF_HEALTH_MESSAGE

#ifndef PLAY_SFX_MESSAGE
#define PLAY_SFX_MESSAGE "PLAY_SFX_MESSAGE"
#endif //!PLAY_SFX_MESSAGE

#ifndef PLAY_BACKGROUND_MESSAGE
#define PLAY_BACKGROUND_MESSAGE "PLAY_BACKGROUND_MESSAGE"
#endif //!PLAY_BACKGROUND_MESSAGE

#ifndef STOP_BACKGROUND_MESSAGE
#define STOP_BACKGROUND_MESSAGE "STOP_BACKGROUND_MESSAGE"
#endif //!STOP_BACKGROUND_MESSAGE

#ifndef RESUME_BACKGROUND_MESSAGE
#define RESUME_BACKGROUND_MESSAGE "RESUME_BACKGROUND_MESSAGE"
#endif //!RESUME_BACKGROUND_MESSAGE

#ifndef BGM_CHANGED
#define BGM_CHANGED "BGM_CHANGED"
#endif //!BGM_CHANGED

#ifndef SFX_CHANGED
#define SFX_CHANGED "SFX_CHANGED"
#endif //!SFX_CHANGED

#ifndef DIFFICULTY_CHANGED
#define DIFFICULTY_CHANGED "DIFFICULTY_CHANGED"
#endif //!DIFFICULTY_CHANGED

#ifndef APPLE_DATA_KEY
#define APPLE_DATA_KEY "APPLE_DATA_KEY"
#endif //!APPLE_DATA_KEY

#ifndef LIVES_DATA_KEY
#define LIVES_DATA_KEY "LIVES_DATA_KEY"
#endif //!LIVES_DATA_KEY

#ifndef RUBY_DATA_KEY
#define RUBY_DATA_KEY "RUBY_DATA_KEY"
#endif //!RUBY_DATA_KEY

#ifndef SCORE_DATA_KEY
#define SCORE_DATA_KEY "SCORE_DATA_KEY"
#endif //!SCORE_DATA_KEY

#ifndef HEALTH_DATA_KEY
#define HEALTH_DATA_KEY "HEALTH_DATA_KEY"
#endif //!HEALTH_DATA_KEY

#ifndef HAS_CHECKPOINT_KEY
#define HAS_CHECKPOINT_KEY "HAS_CHECKPOINT_KEY"
#endif //!HAS_CHECKPOINT_KEY

#ifndef CHECKPOINT_DATA_X_KEY
#define CHECKPOINT_DATA_X_KEY "CHECKPOINT_DATA_X_KEY"
#endif //!CHECKPOINT_DATA_X_KEY

#ifndef CHECKPOINT_DATA_Y_KEY
#define CHECKPOINT_DATA_Y_KEY "CHECKPOINT_DATA_Y_KEY"
#endif //!CHECKPOINT_DATA_Y_KEY

#ifndef BGM_KEY
#define BGM_KEY "BGM_KEY"
#endif //!BGM_KEY

#ifndef SFX_KEY
#define SFX_KEY "SFX_KEY"
#endif //!SFX_KEY

#ifndef DIFFICULTY_KEY
#define DIFFICULTY_KEY "DIFFICULTY_KEY"
#endif //!DIFFICULTY_KEY

#endif //!__GAME_MACROS_H__
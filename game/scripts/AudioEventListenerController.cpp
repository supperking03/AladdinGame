#include "AudioEventListenerController.h"
#include "../Macros.h"
#include "../GameData.h"

ALA_CLASS_SOURCE_2(AudioEventListenerController, ala::GameObjectComponent, ala::MessageListener)

AudioEventListenerController::AudioEventListenerController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _sfxAudioSource(NULL),
  _backgroundAudioSource(NULL)
{
}

void AudioEventListenerController::onInitialize()
{
  _sfxAudioSource = static_cast<ala::AudioSource*>(getGameObject()->getComponent("SFX Audio Source"));
  _backgroundAudioSource = static_cast<ala::AudioSource*>(getGameObject()->getComponent("Background Audio Source"));

  subscribeGlobalMessage(PLAY_SFX_MESSAGE, [=](ala::MessageArgs* message)
  {
    if(GameData::get()->getString(SFX_KEY) == "ON")
    {
      auto resourceName = static_cast<ala::StringMessageArgs*>(message)->getPayload();
      _sfxAudioSource->setAudioClip(static_cast<ala::AudioClip*>(ala::GameManager::get()->getResource(resourceName)));
      _sfxAudioSource->playOneShot();
    }
  });

  subscribeGlobalMessage(PLAY_BACKGROUND_MESSAGE, [=](ala::MessageArgs* message)
  {
    if (GameData::get()->getString(BGM_KEY) == "ON")
    {
      auto resourceName = static_cast<ala::StringMessageArgs*>(message)->getPayload();
      _backgroundAudioSource->setAudioClip(static_cast<ala::AudioClip*>(ala::GameManager::get()->getResource(resourceName)));
      _backgroundAudioSource->setLoop(true);
      _backgroundAudioSource->play();
    }
  });

  subscribeGlobalMessage(STOP_BACKGROUND_MESSAGE, [=](ala::MessageArgs* message)
  {
    _backgroundAudioSource->stop();
  });
  subscribeGlobalMessage(RESUME_BACKGROUND_MESSAGE, [=](ala::MessageArgs* message)
  {
    _backgroundAudioSource->play();
  });
}

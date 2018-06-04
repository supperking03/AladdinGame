#ifndef __AUDIO_EVENT_LISTENER_CONTROLLER_H__
#define __AUDIO_EVENT_LISTENER_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_2(AudioEventListenerController, ala::GameObjectComponent, ala::MessageListener)
private:
  ala::AudioSource* _sfxAudioSource;
  ala::AudioSource* _backgroundAudioSource;
public:
  AudioEventListenerController(ala::GameObject* gameObject, const std::string &name = "");

  void onInitialize() override;
};

#endif //!__AUDIO_EVENT_LISTENER_CONTROLLER_H__

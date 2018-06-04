#ifndef __AUDIO_EVENT_LISTENER_H__
#define __AUDIO_EVENT_LISTENER_H__

#include <aladdin.h>

class AudioEventListenerPrefab: public ala::Prefab
{
public:
  AudioEventListenerPrefab():Prefab("Audio Event Listener") {}
  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__AUDIO_EVENT_LISTENER_H__

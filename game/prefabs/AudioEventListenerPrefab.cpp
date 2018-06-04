#include "AudioEventListenerPrefab.h"
#include "../scripts/AudioEventListenerController.h"

void AudioEventListenerPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::AudioSource(object, "AppleCollect.wav", "Background Audio Source");
  new ala::AudioSource(object, "AppleCollect.wav", "SFX Audio Source");

  new AudioEventListenerController(object);
}

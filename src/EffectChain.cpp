#include "EffectChain.hpp"
#include "AudioEffects/AudioEffect.hpp"
#include "AudioEffects/CustomDistortionEquation.hpp"
#include "AudioEffects/TripleSmoothingDistortion.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/*
This class maintains an effect chain for our plugin, all audio is processed
though the processSample method which will iterate over all our effects in our
effects vector

using a vector allows us to easily swap our audioeffects and change order
*/



template <typename T>
std::unique_ptr<AudioEffect> createAudioEffectFromParameter() {
  return std::make_unique<T>();
}

EffectChain::EffectChain() {
  valueMap = {
      {juce::String("tripleSmoothingDistortion"),
       createAudioEffectFromParameter<TripleSmoothingDistortion>},
       {juce::String("customDistortionEquation"),
       createAudioEffectFromParameter<CustomDistortionEquation>}
  };
}

void EffectChain::processSample(float &sample) {
  for (u_long i = 0; i < effects.size(); i++) {
    effects[i]->processAudio(sample);
  }
}

void EffectChain::addEffect(const juce::String &parameterId, float &value) {

  juce::String str = parameterId;
  std::cout << parameterId << std::endl;
  if (valueMap.count(parameterId)) {
    effects.push_back(valueMap[parameterId]());
    std::cout << "hello";
  }
}

void EffectChain::removeEffect(const juce::String &parameterId) {

  for (u_long i = 0; i < effects.size(); i++) {
    if (effects[i]->getName() == parameterId) {
      effects.erase(effects.begin() + (int)i);
    }
  }
}

#include "EffectChain.hpp"
#include "AudioEffects/AudioEffect.hpp"
#include "AudioEffects/CustomDistortionEquation.hpp"
#include "AudioEffects/SawToothClipping.hpp"
#include "AudioEffects/SquareClipping.hpp"
#include "AudioEffects/TripleSmoothingDistortion.hpp"
#include <functional>
#include <memory>
#include <ostream>
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
std::unique_ptr<AudioEffect>
createAudioEffectFromParameter(juce::AudioProcessorValueTreeState &vts) {
  return std::make_unique<T>(vts);
}

EffectChain::EffectChain() {
  valueMap = {
      {juce::String("tripleSmoothingDistortion"),
       createAudioEffectFromParameter<TripleSmoothingDistortion>},
      {juce::String("customDistortion"),
       createAudioEffectFromParameter<CustomDistortionEquation>},
      {juce::String("squareClipping"),
       createAudioEffectFromParameter<SquareClipping>},
      {juce::String("sawToothClipping"),
       createAudioEffectFromParameter<SawToothClipping>},
  };
}

void EffectChain::processSample(float &sample) {

  for (u_long i = 0; i < effects.size(); i++) {
    effects[i]->processAudio(sample);
  }
}

void EffectChain::addEffect(const juce::String &parameterId,
                            juce::AudioProcessorValueTreeState &vts) {

  if (valueMap.count(parameterId)) {
    effects.push_back(valueMap[parameterId](vts));
  }
}

void EffectChain::removeEffect(const juce::String &parameterId) {

  int index = getEffectIndex(parameterId);

  if (index != -1) {
    effects.erase(effects.begin() + index);
  }
}

int EffectChain::getEffectIndex(const juce::String &parameterId) {

  for (u_long i = 0; i < effects.size(); i++) {
    if (effects[i]->getName() == parameterId) {
      return i;
    }
  }
  return -1;
}

void EffectChain::addEffectParameter(
    AudioEffectParameter audioEffectParameter) {

  int index = getEffectIndex(audioEffectParameter.getAudioEffectName());

  if (index != -1) {
    effects[index]->changeParameter(audioEffectParameter);
  }
}
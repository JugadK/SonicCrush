#pragma once

#include "muParserCallback.h"
#include "Enums/AudioEffectNames.hpp"
#include <atomic>
#include <juce_core/juce_core.h>
#include <memory>
#include <variant>

class AudioEffectParameter {
public:
  AudioEffectParameter(juce::String parameterString, float value);
  AudioEffectParameter(juce::String parameterString, std::string &value);
  ~AudioEffectParameter(){};
  AudioEffects getAudioEffectName();
  juce::String getParameterName();
  std::string getStringData();
  float getFloatData();
  std::variant<float, std::string> floatValue, stringValue;

private:
  AudioEffectParameter(juce::String parameterString);
  AudioEffects audioEffectName;
  juce::String parameterName;
};
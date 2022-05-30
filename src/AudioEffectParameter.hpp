#pragma once

#include "muParserCallback.h"
#include <atomic>
#include <juce_core/juce_core.h>
#include <memory>
#include <variant>

class AudioEffectParameter {
public:
  AudioEffectParameter(juce::String parameterString, float value);
  AudioEffectParameter(juce::String parameterString, std::string &value);
  ~AudioEffectParameter(){};
  juce::String getAudioEffectName();
  juce::String getParameterName();
  std::string getStringData();
  void setStringData(std::string &newData);
  float getFloatData();
  void setFloatData(float newData);

private:
  AudioEffectParameter(juce::String parameterString);
  juce::String audioEffectName;
  juce::String parameterName;
  std::variant<float, std::string> floatValue, stringValue;
};
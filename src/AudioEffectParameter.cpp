#include "AudioEffectParameter.hpp"
#include "Enums/AudioEffectNames.hpp"

// Audio Effect Parameter is used so we can communicate the string parameters
// stored in the valueTree to the actual AudioEffect classes that manipulate the
// examples. We do this by storing the strings in a way that can be decoded into
// an AudioEffectParameter, which can then be used by the EffectChain
//  The correct audioeffect and change the parameter
//  More info in the docs at /docs/AudioEffectParameter
//

AudioEffectParameter::AudioEffectParameter(juce::String parameterString) {

  if (parameterString[0] == 'p') {
    for (int i = 2; i < parameterString.length(); i++) {
      if (parameterString[i] == '_') {
        this->audioEffectName = stringToAudioEffect(parameterString.substring(2, i));
        this->parameterName =
            parameterString.substring(i + 1, parameterString.length());
      }
    }
  } else {
    throw std::invalid_argument("received invalid string parameter");
  }
}

AudioEffectParameter::AudioEffectParameter(juce::String parameterString,
                                           float value)
    : AudioEffectParameter(parameterString) {

  this->floatValue = value;
}

AudioEffectParameter::AudioEffectParameter(juce::String parameterString,
                                           std::string &value)
    : AudioEffectParameter(parameterString) {

  this->stringValue = value;
}

AudioEffects AudioEffectParameter::getAudioEffectName() {
  return audioEffectName;
}

juce::String AudioEffectParameter::getParameterName() { return parameterName; }

std::string AudioEffectParameter::getStringData() {
  return std::get<std::string>(stringValue);
}

float AudioEffectParameter::getFloatData() {
  return std::get<float>(floatValue);
}

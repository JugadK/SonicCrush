#include "AudioEffectNames.hpp"
#include <string>

std::unordered_map<juce::String, AudioEffects> audioEffectMap = {
#define X(a) {#a, AudioEffects::a},
#include "AudioEffectNames.def"
#undef X
};

const char *audioEffectToString(AudioEffects audioEffect) {
  return effects_str[audioEffect];
}

AudioEffects stringToAudioEffect(juce::String audioEffectString) { return audioEffectMap[audioEffectString]; }

bool isValidAudioEffectString(juce::String audioEffectString) {
  return audioEffectMap.count(audioEffectString);
}
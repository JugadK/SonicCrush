#include "AudioEffects/TripleSmoothingDistortion.hpp"
#include "Enums/AudioEffectNames.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

/*
This class maintains an effect chain for our audio, all audio is processed
though the processSample method which will iterate over all our effects in our
effects vector
*/

class EffectChain {
public:
  EffectChain();
  void processSample(float &sample);
  void addEffect(AudioEffects audioEffect,
                 juce::AudioProcessorValueTreeState &vts);
  void removeEffect(AudioEffects audioEffect);
  int getEffectIndex(AudioEffects audioEffect);
  void addEffectParameter(AudioEffectParameter audioEffectParameter);
  std::unordered_map<AudioEffects,
                     std::function<std::unique_ptr<AudioEffect>(
                         juce::AudioProcessorValueTreeState &vts)>>
      valueMap;

private:
  std::vector<std::unique_ptr<AudioEffect>> effects;
};
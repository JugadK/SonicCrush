#include "AudioEffect.hpp"

class SawToothClipping : public AudioEffect {
public:
  SawToothClipping(juce::AudioProcessorValueTreeState& vts);
  ~SawToothClipping();
  void processAudio(float &sample);
  void setClipValue(float value);
  AudioEffects getName();
  void changeParameter(AudioEffectParameter effectParameter);
private:
  AudioEffectParameter clipValue;
  float currentSawToothStep;
  AudioEffectParameter currentSawToothIncrement;
};
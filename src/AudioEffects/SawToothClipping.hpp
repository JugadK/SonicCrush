#include "AudioEffect.hpp"

class SawToothClipping : public AudioEffect {
public:
  SawToothClipping(juce::AudioProcessorValueTreeState& vts);
  ~SawToothClipping();
  void processAudio(float &sample);
  void setClipValue(float value);
  juce::String getName();
  void changeParameter(AudioEffectParameter effectParameter);
private:
  AudioEffectParameter clipValue;
  float currentSawToothStep;
  AudioEffectParameter currentSawToothIncrement;
};
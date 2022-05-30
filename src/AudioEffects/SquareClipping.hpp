#include "AudioEffect.hpp"

class SquareClipping : public AudioEffect {
public:
  SquareClipping(juce::AudioProcessorValueTreeState& vts);
  ~SquareClipping();
  void processAudio(float &sample);
  void getParametersFromValueTree(juce::AudioProcessorValueTreeState& vts);
  void setClipValue(float value);
  juce::String getName();
  void changeParameter(AudioEffectParameter effectParameter);
private:
  AudioEffectParameter clipValue;
};
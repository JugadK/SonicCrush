#include "SquareClipping.hpp"
#include <atomic>
#include <ostream>

SquareClipping::SquareClipping(juce::AudioProcessorValueTreeState &vts)
    : clipValue("p_squareClipping_clipValue",
                *(vts.getRawParameterValue("p_squareClipping_clipValue"))){};

SquareClipping::~SquareClipping(){};

void SquareClipping::setClipValue(float value) {
  clipValue.floatValue = value;
}

void SquareClipping::processAudio(float &sample) {

  if (std::abs(sample) > clipValue.getFloatData()) {
    if (sample > 0.0f) {
      sample = clipValue.getFloatData();
    } else if (sample < 0.0f) {
      sample = clipValue.getFloatData() * -1;
    }
  }
}

AudioEffects SquareClipping::getName() {
  return AudioEffects::squareClipping;
}

void SquareClipping::changeParameter(AudioEffectParameter effectParameter) {
  if (effectParameter.getParameterName() == "clipValue") {
    setClipValue(effectParameter.getFloatData());
  }
}

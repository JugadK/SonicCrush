#include "SawToothClipping.hpp"
#include <ostream>

SawToothClipping::SawToothClipping(juce::AudioProcessorValueTreeState &vts)
    : clipValue("p_sawToothClipping_clipValue",
                std::abs(*(vts.getRawParameterValue("p_sawToothClipping_clipValue")))),
      currentSawToothStep(0.0f),
      // TODO make this grab a variable from valuetreestate
      currentSawToothIncrement("p_sawToothClipping_currentSawToothIncrement",
                               0.001f){};

SawToothClipping::~SawToothClipping(){};

void SawToothClipping::processAudio(float &sample) {

  if (std::abs(sample) > clipValue.getFloatData()  && clipValue.getFloatData() != 0.0f) {

    currentSawToothStep =
        currentSawToothStep + currentSawToothIncrement.getFloatData();

    if (sample < 0.0f) {

      sample = -(clipValue.getFloatData()) - currentSawToothStep;

    } else if (sample >= 0.0f) {

      sample = clipValue.getFloatData() + currentSawToothStep;
    }
  } else {
    currentSawToothStep = 0.0f;
  }
}

void SawToothClipping::setClipValue(float value) {
  clipValue.floatValue = value;
}

AudioEffects SawToothClipping::getName() {
  return AudioEffects::sawToothClipping;
}

void SawToothClipping::changeParameter(AudioEffectParameter effectParameter) {
  if (effectParameter.getParameterName() == "clipValue") {
    setClipValue(std::abs(effectParameter.getFloatData()));
  }
}
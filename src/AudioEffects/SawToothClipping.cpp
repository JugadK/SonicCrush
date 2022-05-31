#include "SawToothClipping.hpp"
#include <ostream>

SawToothClipping::SawToothClipping(juce::AudioProcessorValueTreeState &vts)
    : clipValue("p_sawToothClipping_clipValue",
                *(vts.getRawParameterValue("p_sawToothClipping_clipValue"))),
      // TODO make this grab a variable from valuetreestate
      currentSawToothIncrement("p_sawToothClipping_currentSawToothIncrement",
                               0.001f),
      currentSawToothStep(0.0f){};

SawToothClipping::~SawToothClipping(){};

void SawToothClipping::processAudio(float &sample) {

  if (std::abs(sample) > clipValue.getFloatData()) {

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
  clipValue.setFloatData(value);
}

juce::String SawToothClipping::getName() {
  return juce::String("sawToothClipping");
}

void SawToothClipping::changeParameter(AudioEffectParameter effectParameter) {
  if (effectParameter.getParameterName() == "clipValue") {
    setClipValue(effectParameter.getFloatData());
  }
}
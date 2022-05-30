#include "TripleSmoothingDistortion.hpp"
#include <memory>
#include <ostream>

TripleSmoothingDistortion::TripleSmoothingDistortion(
    juce::AudioProcessorValueTreeState &vts) {}

TripleSmoothingDistortion::~TripleSmoothingDistortion() {}

void TripleSmoothingDistortion::processAudio(float &sample) {

  sample = std::pow(sample, 3);
}

juce::String TripleSmoothingDistortion::getName() {

  juce::String name = "tripleSmoothingDistortion";
  return name;
}

void TripleSmoothingDistortion::changeParameter(
    AudioEffectParameter effectParameter) {}

#include "TripleSmoothingDistortion.hpp"
#include <memory>
#include <ostream>

TripleSmoothingDistortion::TripleSmoothingDistortion(
    juce::AudioProcessorValueTreeState &vts) {}

TripleSmoothingDistortion::~TripleSmoothingDistortion() {}

void TripleSmoothingDistortion::processAudio(float &sample) {

  sample = std::pow(sample, 3);
}

AudioEffects TripleSmoothingDistortion::getName() {

  return AudioEffects::tripleSmoothingDistortion;
}

void TripleSmoothingDistortion::changeParameter(
    AudioEffectParameter effectParameter) {}

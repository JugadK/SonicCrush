#include "TripleSmoothingDistortion.hpp"
#include <memory>

void TripleSmoothingDistortion::processAudio(float &sample) {

  sample = std::pow(sample, 3);
}

juce::String TripleSmoothingDistortion::getName() {

  juce::String name = "tripleSmoothingDistortion";
  return name;
}

#pragma once
#include "../../modules/muparser/include/muParser.h"
#include "AudioEffect.hpp"

class CustomDistortionEquation : public AudioEffect {
public:
  CustomDistortionEquation(juce::AudioProcessorValueTreeState& vts);
  ~CustomDistortionEquation();
  void processAudio(float &sample);
  void setDistortionEquation(std::string equation);
  juce::String getName();
  std::string getDistortionEquation();
  void changeParameter(AudioEffectParameter effectParameter);
  static std::string current_equation;

private:
  double eulersNumber = 2.71828;
  double pi = 3.14159;
  double varX;
  mu::Parser distortionEquationParser;
};
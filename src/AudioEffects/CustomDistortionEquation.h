#include "../../modules/muparser/include/muParser.h"
#include "AudioEffect.hpp"

class CustomDistortionEquation : public AudioEffect {
public:
  void processAudio(float &sample);
  void setDistortionEquation(std::string equation);
  const juce::String name = "customDistortionEquation";
  std::string getDistortionEquation();

private:
  std::string current_equation;
  double eulersNumber = 2.71828;
  double pi = 3.14159;
  double varX;
  mu::Parser distortionEquationParser;
};
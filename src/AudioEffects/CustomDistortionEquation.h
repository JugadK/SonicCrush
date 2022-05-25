#include "../../modules/muparser/include/muParser.h"
#include "AudioEffect.hpp"

class CustomDistortionEquation : public AudioEffect {
public:
  void processAudio(float &sample);

  void setDistortionEquation(std::string equation);

  std::string getDistortionEquation();

private:
  juce::String name = "customDistortionEquation";
  std::string current_equation;
  double eulersNumber = 2.71828;
  double pi = 3.14159;
  double varX;
  mu::Parser distortionEquationParser;

};
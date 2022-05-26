#include "CustomDistortionEquation.hpp"
#include "../../modules/muparser/include/muParser.h"
#include <string>

void CustomDistortionEquation::processAudio(float &sample) {

  varX = sample;
  distortionEquationParser.DefineVar("x", &varX);

  sample = distortionEquationParser.Eval();
}

void CustomDistortionEquation::setDistortionEquation(std::string equation) {

  this->current_equation = equation;

  distortionEquationParser.SetExpr(equation);
  distortionEquationParser.DefineVar("e", &eulersNumber);
  distortionEquationParser.DefineVar("pi", &pi);
}

juce::String CustomDistortionEquation::getName() {
  juce::String name = "customDistortionEquation";
  return name;
}

std::string CustomDistortionEquation::getDistortionEquation() {
  return current_equation;
}

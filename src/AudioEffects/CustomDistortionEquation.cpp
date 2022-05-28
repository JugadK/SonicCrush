#include "CustomDistortionEquation.hpp"
#include "../../modules/muparser/include/muParser.h"
#include <iterator>
#include <string>

CustomDistortionEquation::CustomDistortionEquation() {
  current_equation = "2*x";
  distortionEquationParser.SetExpr(current_equation);
  distortionEquationParser.DefineVar("x", &varX);
}

CustomDistortionEquation::~CustomDistortionEquation() {}

void CustomDistortionEquation::processAudio(float &sample) {

  try {

    varX = (double)sample;
   
    sample = (float)distortionEquationParser.Eval();

    // std::cout << sample;
  } catch (mu::Parser::exception_type &e) {
    std::cout << "error";
    std::cout << e.GetMsg() << std::endl;
  }
}

void CustomDistortionEquation::setDistortionEquation(std::string equation) {

  this->current_equation = equation;

  distortionEquationParser.SetExpr(equation);
  distortionEquationParser.DefineVar("x", &varX);
  distortionEquationParser.DefineVar("e", &eulersNumber);
  distortionEquationParser.DefineVar("pi", &pi);
}

juce::String CustomDistortionEquation::getName() {
  juce::String name = "customDistortion";
  return name;
}

std::string CustomDistortionEquation::getDistortionEquation() {
  return current_equation;
}

void CustomDistortionEquation::changeParameter(AudioEffectParameter effectParameter) {
  if(effectParameter.getParameterName() == juce::String("equationName")) {
    this->setDistortionEquation(effectParameter.getStringData());
  }
}

#include "CustomDistortionEquation.hpp"
#include "../../modules/muparser/include/muParser.h"
#include <iterator>
#include <string>

// Static equation is a hack, in the future the equation string should be added
// to PluginProcessors value tree
std::string CustomDistortionEquation::current_equation = "2*x";

CustomDistortionEquation::CustomDistortionEquation(
    juce::AudioProcessorValueTreeState &vts) {

  setDistortionEquation(current_equation);
}

CustomDistortionEquation::~CustomDistortionEquation() {}

void CustomDistortionEquation::processAudio(float &sample) {

  try {

    varX = (double)sample;

    sample = (float)distortionEquationParser.Eval();

  } catch (mu::Parser::exception_type &e) {
    std::cout << e.GetMsg() << std::endl;
  }
}

void CustomDistortionEquation::setDistortionEquation(std::string equation) {

  CustomDistortionEquation::current_equation = equation;

  distortionEquationParser.SetExpr(current_equation);
  distortionEquationParser.DefineVar("x", &varX);
  distortionEquationParser.DefineVar("e", &eulersNumber);
  distortionEquationParser.DefineVar("pi", &pi);
}

AudioEffects CustomDistortionEquation::getName() {
  return AudioEffects::customDistortion;
}

std::string CustomDistortionEquation::getDistortionEquation() {
  return current_equation;
}

void CustomDistortionEquation::changeParameter(
    AudioEffectParameter effectParameter) {
  if (effectParameter.getParameterName() == juce::String("equationName")) {
    this->setDistortionEquation(effectParameter.getStringData());
  }
}

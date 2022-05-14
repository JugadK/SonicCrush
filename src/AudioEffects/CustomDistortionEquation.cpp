#include "../../modules/muparser/include/muParser.h"
#include "AudioEffect.hpp"
#include <string>

class CustomDistortionEquation : public AudioEffect {
public:
  void processAudio(float &sample) {

    varX = sample;

    distortionEquationParser.DefineVar("x", &varX);

    sample = distortionEquationParser.Eval();
  }

  void setDistortionEquation(std::string equation) {

    this->current_equation = equation;

    distortionEquationParser.SetExpr(equation);
    distortionEquationParser.DefineVar("e", &eulersNumber);
    distortionEquationParser.DefineVar("pi", &pi);
  }

  std::string getDistortionEquation() { return this->current_equation; }

private:
  std::string current_equation;
  double eulersNumber = 2.71828;
  double pi = 3.14159;
  double varX;
  mu::Parser distortionEquationParser;
};
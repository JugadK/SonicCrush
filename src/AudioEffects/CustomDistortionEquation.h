#include "../../modules/muparser/include/muParser.h"
#include "AudioEffect.hpp"

class CustomDistortionEquation : public AudioEffect {
public:
  void processAudio(float &sample);

  void setDistortionEquation(std::string equation);

  std::string getDistortionEquation();

};
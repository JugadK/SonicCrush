#include "TripleSmoothingDistortion.h"

void TripleSmoothingDistortion::processAudio(float &sample) {

  sample = std::pow(sample, 3);
}

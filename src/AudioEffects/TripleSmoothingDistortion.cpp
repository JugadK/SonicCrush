#include "AudioEffect.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>

class TripleSmoothingDistortion : public AudioEffect {
    public:
        void processAudio(float &sample) {

            sample = std::pow(sample,3);

         
        }
};
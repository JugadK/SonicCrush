#pragma once
#include "AudioEffect.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>

class TripleSmoothingDistortion : public AudioEffect {
    public:
        TripleSmoothingDistortion();
        ~TripleSmoothingDistortion();
        static std::unique_ptr<TripleSmoothingDistortion> create();
        void processAudio(float &sample);
        juce::String getName();
        void changeParameter(AudioEffectParameter effectParameter);
        
};
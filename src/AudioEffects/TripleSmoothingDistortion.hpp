#pragma once
#include "AudioEffect.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>

class TripleSmoothingDistortion : public AudioEffect {
    public:
        TripleSmoothingDistortion(juce::AudioProcessorValueTreeState& vts);
        ~TripleSmoothingDistortion();
        void processAudio(float &sample);
        juce::String getName();
        void changeParameter(AudioEffectParameter effectParameter);
};
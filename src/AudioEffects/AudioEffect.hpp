#pragma once
#include <juce_core/juce_core.h>
#include "../AudioEffectParameter.hpp"

class AudioEffect {
    public:

        // processAudio applies the AudioEffect effect onto the sample
        
        virtual void processAudio(float &sample) = 0;     
        virtual ~AudioEffect() {};  
        virtual juce::String getName() = 0;
        virtual void changeParameter(AudioEffectParameter effectParameter) = 0;
};
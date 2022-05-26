#pragma once
#include <juce_core/juce_core.h>

class AudioEffect {
    public:

        // processAudio applies the AudioEffect effect onto the sample
        virtual void processAudio(float &sample) = 0;        
        virtual juce::String getName() = 0;
};
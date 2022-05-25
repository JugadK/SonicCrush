#pragma once

#include <juce_core/juce_core.h>

class AudioEffect {
    public:
        virtual void processAudio(float &sample) = 0;
        virtual void setString(juce::String name) = 0;
        virtual juce::String getString() = 0;
        
};
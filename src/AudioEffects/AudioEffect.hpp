#pragma once

#include <juce_core/juce_core.h>

class AudioEffect {
    public:
        virtual void processAudio(float &sample) = 0;
        
};
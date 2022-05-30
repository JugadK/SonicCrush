#pragma once
#include <juce_core/juce_core.h>
#include "../AudioEffectParameter.hpp"
#include <juce_audio_processors/juce_audio_processors.h>

class AudioEffect {
    public:
        virtual void processAudio(float &sample) = 0;    
        virtual ~AudioEffect() {};  
        virtual juce::String getName() = 0;
        virtual void changeParameter(AudioEffectParameter effectParameter) = 0;
};
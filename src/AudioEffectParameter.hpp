#pragma once

#include "muParserCallback.h"
#include <juce_core/juce_core.h>
#include <variant>



class AudioEffectParameter {
    public:
        AudioEffectParameter(juce::String parameterString, float &value);
        AudioEffectParameter(juce::String parameterString, std::string &value);
        ~AudioEffectParameter() {};
        juce::String getAudioEffectName();
        juce::String getParameterName();
        std::string  getStringData();
        float getFloatData();

    private:
        AudioEffectParameter(juce::String parameterString);
        juce::String audioEffectName;
        juce::String parameterName;
        std::variant<float, std::string> floatValue, stringValue;
};
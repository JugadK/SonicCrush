#include "AudioEffect.hpp"

class SawToothClipping : public AudioEffect {
    public:
        SawToothClipping(juce::AudioProcessorValueTreeState& vts);
        ~SawToothClipping();
        void processAudio(float &sample);
        juce::String getName();
        void changeParameter(AudioEffectParameter effectParameter);
};
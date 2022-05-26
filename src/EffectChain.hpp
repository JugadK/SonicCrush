#include "AudioEffects/TripleSmoothingDistortion.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

/*
This class maintains an effect chain for our audio, all audio is processed though the
processSample method which will iterate over all our effects in our effects vector
*/

class EffectChain {
    public:
        EffectChain();
        void processSample(float& sample);
        void addEffect(const juce::String & parameterId, float& value);
        void removeEffect(const juce::String & parameterId);

    private:
        std::vector<std::unique_ptr<AudioEffect>> effects;
        std::unordered_map<juce::String, std::function<std::unique_ptr<AudioEffect>()>> valueMap;
        
};
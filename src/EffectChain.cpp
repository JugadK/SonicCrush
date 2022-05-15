#include "AudioEffects/AudioEffect.hpp"
#include <unordered_map>
#include <vector>

/*
This class maintains an effect chain for our audio, all audio is processed though the
processSample method which will iterate over all our effects in our effects vector
*/

class EffectChain {
    public:
        void processSample(float& sample) {

            for(u_long i = 0; i < effects.size(); i++) {
                effects[i].processAudio(sample);
            }
        }

        void addEffect(AudioEffect effect) {
            effects.push_back(effect);
        }

    private:
        std::vector<AudioEffect> effects;
};
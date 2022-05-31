#pragma once
#include <iostream>
#include <unordered_map>
#include <juce_core/juce_core.h>

// X macros are sort of function macro, we can define a function like X(a) and for every X(something) stored in
// AudioEffectNames.def it will run the macro, pasting however you manipulate,
// the "a" after the call, so X(a) a means just copy whatever a is, while #a will paste "a" as a string
// so if we need a new AudioEffect just add a new X(effectName) into AudioEffectNames

enum AudioEffects {
#define X(a) a,
#include "AudioEffectNames.def"
#undef X

};

char const* const effects_str[] = {
#   define X(a) #a,
#   include "AudioEffectNames.def"
#   undef X
};

AudioEffects stringToAudioEffect(juce::String);
const char *audioEffectToString(AudioEffects audioEffect);
bool isValidAudioEffectString(juce::String audioEffectString);
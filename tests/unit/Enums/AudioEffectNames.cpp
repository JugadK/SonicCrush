#include "../../../src/Enums/AudioEffectNames.hpp"
#include <gtest/gtest.h>
#include <juce_core/juce_core.h>

TEST(AudioEffectNames, audioEffectToString) {

  juce::String str = audioEffectToString(AudioEffects::customDistortion);
  EXPECT_EQ(str, juce::String("customDistortion"));

  str = audioEffectToString(AudioEffects::squareClipping);
  EXPECT_EQ(str, juce::String("squareClipping"));
}

TEST(AudioEffectNames, stringToAudioEffect) {

  AudioEffects effect = stringToAudioEffect("customDistortion");
  EXPECT_EQ(effect, AudioEffects::customDistortion);

  effect = stringToAudioEffect("tripleSmoothingDistortion");
  EXPECT_EQ(effect, AudioEffects::tripleSmoothingDistortion);
}
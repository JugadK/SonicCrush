#include "../../src/EffectChain.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(AudioEffectParameter, constructorString) {

  juce::String parameterString = "p_customDistortion_equationName";

  std::string str = "4*x";

  AudioEffectParameter aep = AudioEffectParameter(parameterString, str);

  EXPECT_EQ(aep.getAudioEffectName(), AudioEffects::customDistortion);
  EXPECT_EQ(aep.getParameterName(), "equationName");
  EXPECT_EQ(aep.getStringData(), "4*x");
}

TEST(AudioEffectParameter, constructorFloat) {

  juce::String parameterString = "p_tripleSmoothingDistortion_gain";

  float value = 1.0f;

  AudioEffectParameter aep = AudioEffectParameter(parameterString, value);

  EXPECT_EQ(aep.getAudioEffectName(), AudioEffects::tripleSmoothingDistortion);
  EXPECT_EQ(aep.getParameterName(), "gain");
  EXPECT_EQ(aep.getFloatData(), 1.0f);
}
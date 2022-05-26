#include "../src/EffectChain.hpp"
#include <gtest/gtest.h>

TEST(EffectChain, processSample) {

juce::String tsd = "tripleSmoothingDistortion";
EffectChain effectChain = EffectChain();
float value = 1.0f;
effectChain.addEffect(tsd, value);

std::cout << "hello2" << std::endl;

float sample = 0.25f;

effectChain.processSample(sample);

EXPECT_EQ(floorf(sample * 100) / 100, 0.01f);

}

TEST(EffectChain, addAndRemoveEffect) {

juce::String tsd = "tripleSmoothingDistortion";
EffectChain effectChain = EffectChain();
float value = 1.0f;
float sample = 0.25f;

effectChain.addEffect(tsd, value);

effectChain.removeEffect(tsd);

effectChain.processSample(sample);

EXPECT_EQ(sample, 0.25f);

}
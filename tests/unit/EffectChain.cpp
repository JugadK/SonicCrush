#include "../../src/EffectChain.hpp"
#include "../../mocks/MockAudioEffect.hpp"
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>


TEST(EffectChain, processSample) {

//MockAudioEffect audioEffect;

juce::String tsd = "customDistortion";
EffectChain effectChain = EffectChain();
float value = 1.0f;
effectChain.addEffect(tsd);

float sample = 0.25f;

effectChain.processSample(sample);

EXPECT_EQ(floorf(sample * 100) / 100, 0.5f);

}

TEST(EffectChain, addAndRemoveEffect) {

juce::String tsd = "customDistortion";
EffectChain effectChain = EffectChain();
float value = 1.0f;
float sample = 0.25f;

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);
effectChain.processSample(sample);

EXPECT_EQ(sample, 0.25f);

}

TEST(EffectChain, addAndRemoveEffectMultiple) {


juce::String tsd = "customDistortion";
EffectChain effectChain = EffectChain();
float value = 1.0f;
float sample = 0.25f;

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.addEffect(tsd);
effectChain.removeEffect(tsd);

effectChain.processSample(sample);



EXPECT_EQ(sample, 0.25f);

}

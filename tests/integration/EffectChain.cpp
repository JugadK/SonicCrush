#include "../../../src/AudioEffects/CustomDistortionEquation.hpp"
#include "../../../src/PluginProcessor.h"
#include "../mocks/MockAudioProcessor.hpp"
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

TEST(EffectChain, processSample) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  // TODO remove static current_equation by integrating
  // current equation into value tree state
  // This is why state is bad kids
  CustomDistortionEquation::current_equation = "2*x";

  juce::String parameterId = "customDistortion";
  EffectChain effectChain = EffectChain();

  effectChain.addEffect(parameterId, vts);
  float sample = 0.25f;

  effectChain.processSample(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.5f);
}

TEST(EffectChain, processSampleClippingValue) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("p_squareClipping_clipValue",
                                                   "p_squareClipping_clipValue",
                                                   -40.0f, 80.0f, 0.5f)});

  EffectChain effectChain = EffectChain();

  juce::String parameterId = "squareClipping";
  effectChain.addEffect(parameterId, vts);

  float sample = 1.0f;
  effectChain.processSample(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.5f);
}

TEST(EffectChain, addAndRemoveEffect) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  EffectChain effectChain = EffectChain();

  juce::String parameterId = "customDistortion";

  effectChain.addEffect(parameterId, vts);
  effectChain.removeEffect(parameterId);

  float sample = 0.25f;
  effectChain.processSample(sample);

  EXPECT_EQ(sample, 0.25f);
}

TEST(EffectChain, findEffect) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("p_squareClipping_clipValue",
                                                   "p_squareClipping_clipValue",
                                                   -40.0f, 80.0f, 1.0f)});

  AudioEffectParameter squareClippingClipValue =
      AudioEffectParameter("p_squareClipping_clipValue", 0.5f);

  EffectChain effectChain = EffectChain();

  juce::String parameterId = "squareClipping";
  effectChain.addEffect(parameterId, vts);

  float sample = 1.0f;
  effectChain.processSample(sample);

  EXPECT_EQ(sample, 1.0f);

  effectChain.addEffectParameter(squareClippingClipValue);

  effectChain.processSample(sample);

  EXPECT_EQ(sample, 0.5f);
}

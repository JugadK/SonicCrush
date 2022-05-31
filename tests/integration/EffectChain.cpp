#include "../../../src/AudioEffects/CustomDistortionEquation.hpp"
#include "../../../src/PluginProcessor.h"
#include "../mocks/MockAudioProcessor.hpp"
#include <gmock/gmock-cardinalities.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include <unordered_map>

TEST(EffectChain, processSample) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {
          std::make_unique<juce::AudioParameterFloat>("preGain", "preGain",
                                                      -40.0f, 80.0f, 1.0f),
          std::make_unique<juce::AudioParameterFloat>("postGain", "postGain",
                                                      -40.0f, 80.0f, 1.0f),
          std::make_unique<juce::AudioParameterFloat>(
              "p_squareClipping_clipValue", "p_squareClipping_clipValue", -1.0f,
              1.0f, 0.1f),
          std::make_unique<juce::AudioParameterFloat>(
              "p_sawToothClipping_clipValue", "p_sawToothClipping_clipValue",
              -1.0f, 1.0f, 0.1f),
          std::make_unique<juce::AudioParameterBool>(
              "squareClipping",  // parameterID
              "Square Clipping", // parameter name
              false),
          std::make_unique<juce::AudioParameterBool>(
              "sawToothClipping",  // parameterID
              "Sawtooth Clipping", // parameter name
              false),
          std::make_unique<juce::AudioParameterBool>(
              "tripleSmoothingDistortion",     // parameterID
              "Triple Exponential Distortion", // parameter name
              false),
          std::make_unique<juce::AudioParameterBool>(
              "customDistortion",  // parameterID
              "Custom Distortion", // parameter name
              false),
          std::make_unique<juce::AudioParameterBool>(
              "noDistortion",  // parameterID
              "No Distortion", // parameter name
              true),
          std::make_unique<juce::AudioParameterBool>(
              "noClipping",  // parameterID
              "No Clipping", // parameter name
              true),
      });

  // TODO remove static current_equation by integrating
  // current equation into value tree state
  // Without this if the test that changes it to 4*x is run before
  // The processAudio returns 1.0f;
  // This is why state is bad kids
  // CustomDistortionEquation::current_equation = "2*x";

  EffectChain effectChain = EffectChain();

  std::vector<juce::String> effectNames;

  // Since our valueMap is unordered we have no way of telling what order ]
  // The audioeffects are returned in, so to find the correct sample value
  // We collect all AudioEffects stored in the valueMap and then use a hashnao
  // to match it to the correct sample response

  // Get all audioeffect names registered in the effectChain valueMap
  for (auto i = effectChain.valueMap.begin(); i != effectChain.valueMap.end();
       i++) {
    effectNames.push_back(i->first);
  }

  
  std::unordered_map<juce::String, std::vector<float>> sampleMap = {
      {juce::String("tripleSmoothingDistortion"),
       {0.015f, 0.015f, 0.015f, 0.015f, 0.015f}},
      {juce::String("customDistortion"), {0.5f, 0.5f, 0.5f, 0.5f, 0.5f}},
      {juce::String("squareClipping"), {0.1f, 0.1f, 0.1f, 0.1f, 0.1f}},
      {juce::String("sawToothClipping"),
       {0.101f, 0.102f, 0.103f, 0.104f, 0.105f}},

  };

  for (int i = 0; i < effectNames.size(); i++) {

    juce::String currentEffect = effectNames[i];
    effectChain.addEffect(currentEffect, vts);

    for (int j = 0; j < 5; j++) {

      float sample = 0.25f;
      effectChain.processSample(sample);
      EXPECT_EQ(floorf(sample * 1000) / 1000, sampleMap[currentEffect][j]);
    }

    effectChain.removeEffect(currentEffect);
  }
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

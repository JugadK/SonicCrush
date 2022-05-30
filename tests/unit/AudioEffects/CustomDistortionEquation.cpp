#include "../../../src/AudioEffects/CustomDistortionEquation.hpp"
#include "../../../src/PluginProcessor.h"
#include <gtest/gtest.h>

#include "../../mocks/MockAudioProcessor.hpp"

TEST(CustomDistortionEquation, EquationExponential) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  CustomDistortionEquation cde = CustomDistortionEquation(vts);

  cde.setDistortionEquation("x^2");

  EXPECT_TRUE(cde.getDistortionEquation() == "x^2");

  float sample = 0.0f;
  cde.processAudio(sample);

  EXPECT_TRUE(sample == 0.0f);

  sample = 0.4f;
  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.16f) << sample;
}

TEST(CustomDistortionEquation, EquationEuler) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  CustomDistortionEquation cde = CustomDistortionEquation(vts);
  cde.setDistortionEquation("2*e*x");

  EXPECT_TRUE(cde.getDistortionEquation() == "2*e*x");

  float sample = 0.0f;
  cde.processAudio(sample);

  EXPECT_EQ(sample, 0.0f);

  sample = 0.4f;
  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 2.17f) << sample;
}

TEST(CustomDistortionEquation, GetsEquationPi) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  CustomDistortionEquation cde = CustomDistortionEquation(vts);
  cde.setDistortionEquation("pi*x");

  EXPECT_TRUE(cde.getDistortionEquation() == "pi*x");

  float sample = 0.0f;
  cde.processAudio(sample);

  EXPECT_EQ(sample, 0.0f);

  sample = 0.4f;
  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 1.25f) << sample;
}

TEST(CustomDistortionEquation, ChangeEquationParameter) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr, juce::Identifier("SonicCrush"),
      {std::make_unique<juce::AudioParameterFloat>("preGain", "preGain", -40.0f,
                                                   80.0f, 1.0f)});

  CustomDistortionEquation cde = CustomDistortionEquation(vts);

  std::string str = "4*x";
  AudioEffectParameter equationName = AudioEffectParameter(
      juce::String("p_customDistortion_equationName"), str);

  cde.changeParameter(equationName);

  EXPECT_TRUE(cde.getDistortionEquation() == "4*x");
}
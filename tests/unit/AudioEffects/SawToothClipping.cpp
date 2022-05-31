#include "../../../src/AudioEffects/SawToothClipping.hpp"
#include "../../mocks/MockAudioProcessor.hpp"
#include <gtest/gtest.h>

TEST(SawToothClipping, processAudio) {

  {
    std::vector<float> testSamples = {0.5f, 0.6f, 0.7f, 0.6f, 0.4f};

    std::vector<float> testProcessedSamples = {0.5f,    0.501f, 0.502f,
                                               0.503f, 0.4f};

    MockAudioProcessor mad = MockAudioProcessor();

    juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
        mad, nullptr, juce::Identifier("SC"),
        {std::make_unique<juce::AudioParameterFloat>(
            "p_sawToothClipping_clipValue", "p_sawToothClipping_clipValue",
            -1.0f, 1.0f, 0.5f)});

    SawToothClipping sawToothClipping = SawToothClipping(vts);

    for (int i = 0; i < testSamples.size(); i++) {
      sawToothClipping.processAudio(testSamples[i]);
      EXPECT_EQ(testSamples[i], testProcessedSamples[i]);
    }
  }
}

TEST(SawToothClipping, parameterChanged) {

  MockAudioProcessor mad = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mad, nullptr, juce::Identifier("SC"),
      {std::make_unique<juce::AudioParameterFloat>(
          "p_sawToothClipping_clipValue", "p_sawToothClipping_clipValue", -1.0f,
          1.0f, 0.5f)});

  SawToothClipping squareClipper = SawToothClipping(vts);

  AudioEffectParameter clipValue =
      AudioEffectParameter("p_sawToothClipping_clipValue", 0.3f);
  squareClipper.changeParameter(clipValue);

  float sample = 0.5f;
  squareClipper.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.3f);
}

#include "../../../src/AudioEffects/SquareClipping.hpp"
#include "../../mocks/MockAudioProcessor.hpp"
#include <gtest/gtest.h>

TEST(SquareClipping, processSample) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  {

    MockAudioProcessor mad = MockAudioProcessor();

    juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
        mad, nullptr, juce::Identifier("Sonic"),
        {std::make_unique<juce::AudioParameterFloat>(
            "p_squareClipping_clipValue", "p_squareClipping_clipValue", -1.0f,
            1.0f, 1.0f)});

    SquareClipping squareClipper = SquareClipping(vts);

    float sample = 1.0f;
    squareClipper.processAudio(sample);

    EXPECT_EQ(floorf(sample * 100) / 100, 1.0f);
  }

  {

    MockAudioProcessor mad = MockAudioProcessor();

    juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
        mad, nullptr, juce::Identifier("SC"),
        {std::make_unique<juce::AudioParameterFloat>(
            "p_squareClipping_clipValue", "p_squareClipping_clipValue", -1.0f,
            1.0f, 0.5f)});

    SquareClipping squareClipper = SquareClipping(vts);

    float sample = 1.0f;
    squareClipper.processAudio(sample);

    EXPECT_EQ(floorf(sample * 100) / 100, 0.5f);
  }

  {

    MockAudioProcessor mad = MockAudioProcessor();

    juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
        mad, nullptr, juce::Identifier("SC"),
        {std::make_unique<juce::AudioParameterFloat>(
            "p_squareClipping_clipValue", "p_squareClipping_clipValue", -1.0f,
            1.0f, 0.5f)});

    SquareClipping squareClipper = SquareClipping(vts);

    float sample = -1.0f;
    squareClipper.processAudio(sample);

    EXPECT_EQ(floorf(sample * 100) / 100, -0.5f);
  }
}

TEST(SquareClipping, parameterChanged) {

  MockAudioProcessor mad = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mad, nullptr, juce::Identifier("SC"),
      {std::make_unique<juce::AudioParameterFloat>("p_squareClipping_clipValue",
                                                   "p_squareClipping_clipValue",
                                                   -1.0f, 1.0f, 0.5f)});

  SquareClipping squareClipper = SquareClipping(vts);

  AudioEffectParameter clipValue =
      AudioEffectParameter("p_squareClipping_clipValue", 0.3f);
  squareClipper.changeParameter(clipValue);

  float sample = 0.5f;
  squareClipper.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.3f);
}

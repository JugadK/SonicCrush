#include "../../../src/AudioEffects/TripleSmoothingDistortion.hpp"
#include "../../../src/PluginProcessor.h"
#include <cstdlib>
#include <gtest/gtest.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <memory>
#include <new>
#include "../../mocks/MockAudioProcessor.hpp"

TEST(TripleSmoothingDistortion, ProcessAudio) {

  juce::ScopedJuceInitialiser_GUI initializeJuce;

  MockAudioProcessor mAudioProcessor = MockAudioProcessor();

  juce::AudioProcessorValueTreeState vts = juce::AudioProcessorValueTreeState(
      mAudioProcessor, nullptr);

  TripleSmoothingDistortion tsd = TripleSmoothingDistortion(vts);

  float sample = 0.0f;
  tsd.processAudio(sample);

  EXPECT_EQ(0.0f, sample);

  sample = 0.6f;
  tsd.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.21f);



}

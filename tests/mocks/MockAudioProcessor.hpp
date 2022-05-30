
#include <gmock/gmock-function-mocker.h>
#include <juce_audio_processors/juce_audio_processors.h>

// Before using this in a test make sure  juce::ScopedJuceInitialiser_GUI initializeJuce;
// has been called in scope, otherwise memory leaks will occur during testing

class MockAudioProcessor : public juce::AudioProcessor {

  MOCK_METHOD(const juce::String, getName, (), (const, override));
  MOCK_METHOD(juce::StringArray, getAlternateDisplayNames, (), (const));
  MOCK_METHOD(void, prepareToPlay,
              (double sampleRate, int maximumExpectedSamplesPerBlock),
              (override));
  MOCK_METHOD(void, releaseResources, (), (override));
  MOCK_METHOD(void, memoryWarningReceived, (), (override));
  MOCK_METHOD(void, processBlock,
              (juce::AudioBuffer<float> & buffer,
               juce::MidiBuffer &midiMessages),
              (override));
  MOCK_METHOD(void, processBlock,
              (juce::AudioBuffer<double> & buffer,
               juce::MidiBuffer &midiMessages),
              (override));
  MOCK_METHOD(void, processBlockBypassed,
              (juce::AudioBuffer<double> & buffer,
               juce::MidiBuffer &midiMessages),
              (override));
  MOCK_METHOD(void, processBlockBypassed,
              (juce::AudioBuffer<float> & buffer,
               juce::MidiBuffer &midiMessages),
              (override));
  MOCK_METHOD(bool, canAddBus, (bool isInput), (override, const));
  MOCK_METHOD(bool, canRemoveBus, (bool isInput), (override, const));
  MOCK_METHOD(bool, supportsDoublePrecisionProcessing, (), (override, const));
  MOCK_METHOD(double, getTailLengthSeconds, (), (override, const));
  MOCK_METHOD(bool, acceptsMidi, (), (override, const));
  MOCK_METHOD(bool, producesMidi, (), (override, const));
  MOCK_METHOD(bool, supportsMPE, (), (override, const));
  MOCK_METHOD(bool, isMidiEffect, (), (override, const));
  // MOCK_METHOD(void, setNonRealtime, (bool isNonRealtime), (override));
  MOCK_METHOD(juce::AudioProcessorEditor *, createEditor, (), (override));
  MOCK_METHOD(bool, hasEditor, (), (override, const));
  MOCK_METHOD(int, getNumPrograms, (), (override));
  MOCK_METHOD(int, getCurrentProgram, (), (override));
  MOCK_METHOD(void, setCurrentProgram, (int index), (override));
  MOCK_METHOD(const juce::String, getProgramName, (int index), (override));
  MOCK_METHOD(void, changeProgramName, (int index, const juce::String &newName),
              (override));
  MOCK_METHOD(void, getStateInformation, (juce::MemoryBlock & destData),
              (override));
  MOCK_METHOD(void, setStateInformation, (const void *data, int sizeInBytes),
              (override));
};
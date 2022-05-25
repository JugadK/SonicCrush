#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "../modules/muparser/include/muParser.h"
#include "EffectChain.h"

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener {
public:
  // Default distortion equation
  std::string currentDistortionEquation = "2*x";

  EffectChain effectChain = EffectChain();

  float noteOnVel;
  //==============================================================================
  AudioPluginAudioProcessor();
  ~AudioPluginAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  void parameterChanged(const juce::String & parameterID, float newValue) override;

  juce::Random random;

  std::atomic<float> *preGainParameter = nullptr;
  std::atomic<float> *postGainParameter = nullptr;
  std::atomic<float> *clipParameter = nullptr;

  std::atomic<float> *noClippingParameter = nullptr;
  std::atomic<float> *squareClippingParameter = nullptr;
  std::atomic<float> *sawToothClippingParameter = nullptr;

  std::atomic<float> *noDistortionParameter = nullptr;
  std::atomic<float> *tripleExponentialParameter = nullptr;
  std::atomic<float> *customDistortionParameter = nullptr;

  double preGain;
  double postGain;
  double clipThreshold;
  bool noClipping = true;
  bool enableSquareClipping = false;
  bool enableSawToothClipping = false;
  bool noDistortion = true;
  bool enableTripleExponentialDistortion = false;
  bool enableCustomDistortionEquation = false;

  double eulersNumber = 2.71828;
  double pi = 3.14159;
  double varX;
  mu::Parser distortionEquationParser;


  float currentSawToothStep = 0.0f;

  float currentSawToothStepIncrement = 0.001f;

  void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill);

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  juce::AudioProcessorValueTreeState parameters;
 
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};

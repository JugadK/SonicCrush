#include "PluginProcessor.h"
#include "../modules/muparser/include/muParser.h"
#include "PluginEditor.h"
#include <string>
#include "AudioEffects/TripleSmoothingDistortion.cpp"
#include "AudioEffects/CustomDistortionEquation.h"


//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
              ),              
      parameters(*this, nullptr, juce::Identifier("SonicCrush"),
                 {
                     std::make_unique<juce::AudioParameterFloat>(
                         "preGain", "preGain", -40.0f, 80.0f, 1.0f),
                     std::make_unique<juce::AudioParameterFloat>(
                         "postGain", "postGain", -40.0f, 80.0f, 1.0f),
                     std::make_unique<juce::AudioParameterFloat>(
                         "clipValue", "clipValue", -1.0f, 1.0f, 1.0f),
                     std::make_unique<juce::AudioParameterBool>(
                         "squareClipping",  // parameterID
                         "Square Clipping", // parameter name
                         false),
                     std::make_unique<juce::AudioParameterBool>(
                         "sawToothClipping",  // parameterID
                         "Sawtooth Clipping", // parameter name
                         false),
                     std::make_unique<juce::AudioParameterBool>(
                         "tripleExponentialDistortion",   // parameterID
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
                 }) {
  // phaseParameter = parameters.getRawParameterValue("invertPhase");

  preGainParameter = parameters.getRawParameterValue("preGain");
  postGainParameter = parameters.getRawParameterValue("postGain");
  clipParameter = parameters.getRawParameterValue("clipValue");
  noClippingParameter = parameters.getRawParameterValue("noClipping");
  sawToothClippingParameter =
      parameters.getRawParameterValue("sawToothClipping");
  squareClippingParameter = parameters.getRawParameterValue("squareClipping");
  noDistortionParameter = parameters.getRawParameterValue("noDistortion");
  tripleExponentialParameter =
      parameters.getRawParameterValue("tripleExponentialDistortion");
  customDistortionParameter =
      parameters.getRawParameterValue("customDistortion");
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AudioPluginAudioProcessor::getNumPrograms() {
  return 1; // NB: some hosts don't cope very well if you tell them there are 0
            // programs, so this should be at least 1, even if you're not really
            // implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram() { return 0; }

void AudioPluginAudioProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index,
                                                  const juce::String &newName) {
  juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                              int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages) {

  juce::ignoreUnused(midiMessages);

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.

  distortionEquationParser.SetExpr(currentDistortionEquation);
  distortionEquationParser.DefineVar("x", &varX);
  distortionEquationParser.DefineVar("e", &eulersNumber);
  distortionEquationParser.DefineVar("pi", &pi);

  for (int channel = 0; channel < totalNumInputChannels; ++channel) {

    auto *channelData = buffer.getWritePointer(channel);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

      channelData[sample] = buffer.getSample(channel, sample);

    }
  }

  ;

  /*  try {

      clipThreshold = *clipParameter;
      preGain = *preGainParameter;
      postGain = *postGainParameter;

      // For Some reason we can only get parameters back as floats, so to use
      // them as booleans we determine if they are 1 or 0

      enableSquareClipping = *squareClippingParameter < 1 ? false : true;
      enableSawToothClipping = *sawToothClippingParameter < 1 ? false : true;

      enableTripleExponentialDistortion =
          *tripleExponentialParameter < 1 ? false : true;
      enableCustomDistortionEquation =
          *customDistortionParameter < 1 ? false : true;

      if (enableCustomDistortionEquation) {
      }

      for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

        channelData[sample] =
            buffer.getSample(channel, sample) * pow(10, *preGainParameter / 20);

        if (enableTripleExponentialDistortion) {

          channelData[sample] = pow(channelData[sample], 3);

        } else if (enableCustomDistortionEquation) {

          varX = channelData[sample];

          channelData[sample] = distortionEquationParser.Eval();
        }

        if (std::abs(channelData[sample]) > clipThreshold) {

          if (enableSquareClipping) {

            if (channelData[sample] < 0.0f) {

              channelData[sample] = -(clipThreshold);

            } else if (channelData[sample] >= 0.0f) {

              channelData[sample] = clipThreshold;
            }
          } else if (enableSawToothClipping) {

            currentSawToothStep =
                currentSawToothStep + currentSawToothStepIncrement;

            if (channelData[sample] < 0.0f) {

              channelData[sample] = -(clipThreshold) - (currentSawToothStep);

            } else if (channelData[sample] >= 0.0f) {

              channelData[sample] = (clipThreshold) + (currentSawToothStep);
            }
          }
        } else {
          currentSawToothStep = 0.0f;
        }

        channelData[sample] = channelData[sample] * pow(10, postGain / 20);
      }
    } catch (mu::Parser::exception_type &e) {
      std::cout << e.GetMsg() << std::endl;
    } */
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
  return new AudioPluginAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.

  auto state = parameters.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);

  juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                    int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.

  std::unique_ptr<juce::XmlElement> xmlState(
      getXmlFromBinary(data, sizeInBytes));

  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(parameters.state.getType()))
      parameters.replaceState(juce::ValueTree::fromXml(*xmlState));

  juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new AudioPluginAudioProcessor();
}

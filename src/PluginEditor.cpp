#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <cstddef>
#include "AudioEffectParameter.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p, juce::AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor(&p), valueTreeState(vts), audioProcessor(p) {

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(600, 440);


  enum RadioButton {
    ClipButtons = 100,
    DistortionButton = 101,
  };

  addAndMakeVisible(gainSliderLabel);
  addAndMakeVisible(postGainSliderLabel);
  addAndMakeVisible(clipSliderLabel);
  addAndMakeVisible(sawtoothIncrementSliderLabel);

  gainSliderLabel.setFont(juce::Font(12.0f, juce::Font::bold));
  gainSliderLabel.setText("Pre Gain", juce::dontSendNotification);
  postGainSliderLabel.setFont(juce::Font(12.0f, juce::Font::bold));
  postGainSliderLabel.setText("Post Gain", juce::dontSendNotification);
  clipSliderLabel.setFont(juce::Font(12.0f, juce::Font::bold));
  clipSliderLabel.setText("Clip", juce::dontSendNotification);

  addAndMakeVisible(SquareClippingButton);
  addAndMakeVisible(SawToothClippingButton);
  addAndMakeVisible(noClippingButton);
 
  squareClippingAttachment.reset(
      new ButtonAttachment(valueTreeState, "squareClipping", SquareClippingButton));
  sawToothClippingAttachment.reset(
      new ButtonAttachment(valueTreeState, "sawToothClipping", SawToothClippingButton));
  noClippingAttachment.reset(
      new ButtonAttachment(valueTreeState, "noClipping", noClippingButton)); 

  noClippingButton.setRadioGroupId(100);
  SquareClippingButton.setRadioGroupId(100);
  SawToothClippingButton.setRadioGroupId(100);

  addAndMakeVisible(noDistortionButton);
  addAndMakeVisible(tripleSmoothingDistortionButton);
  addAndMakeVisible(customDistortionEquationButton);

  noDistortionAttachment.reset(
      new ButtonAttachment(valueTreeState, "noDistortion", noDistortionButton));
  tripleSmoothingAttachment.reset(
      new ButtonAttachment(valueTreeState, "tripleSmoothingDistortion", tripleSmoothingDistortionButton));
  customDistortionEquationAttachment.reset(
      new ButtonAttachment(valueTreeState, "customDistortion", customDistortionEquationButton));

  noDistortionButton.setRadioGroupId(101);
  tripleSmoothingDistortionButton.setRadioGroupId(101);
  customDistortionEquationButton.setRadioGroupId(101);

  addAndMakeVisible(equationInput);
  equationInput.onReturnKey = [this] { onReturnPressed(&equationInput); };

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(postGainSlider);
  addAndMakeVisible(clipSlider);

  preGainAttachment.reset(
      new SliderAttachment(valueTreeState, "preGain", gainSlider));
  postGainAttachment.reset(
      new SliderAttachment(valueTreeState, "postGain", postGainSlider));
  clipAttachment.reset(
      new SliderAttachment(valueTreeState, "clipValue", clipSlider));

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  // g.setOpacity(0.0f);
  setOpaque(false);
  // g.fillAll(
  //    juce::Colours::transparentBlack);
  g.setColour(juce::Colours::transparentBlack);
  g.setFont(15.0f);
}

void AudioPluginAudioProcessorEditor::onReturnPressed(
    juce::TextEditor *textEditor) {

  if (textEditor == &equationInput) {

    std::string str = textEditor->getText().toStdString();

    juce::String eqParameter = "p_customDistortion_equationName";

    audioProcessor.effectChain.addEffectParameter(AudioEffectParameter(eqParameter,str));

    std::cout << "hello";
  }
}

void AudioPluginAudioProcessorEditor::resized() {

  equationInput.setBounds(300, 200, 100, 60);

  gainSlider.setBounds(90, 330, getWidth() - 180, 20);
  clipSlider.setBounds(90, 350, getWidth() - 180, 20);
  postGainSlider.setBounds(90, 370, getWidth() - 180, 20);

  gainSliderLabel.setBounds(55, 330, 40, 20);
  clipSliderLabel.setBounds(55, 350, 40, 20);
  postGainSliderLabel.setBounds(55, 370, 40, 20);

  noClippingButton.setBounds(90, 100, 80, 30);
  SquareClippingButton.setBounds(90, 130, 80, 30);
  SawToothClippingButton.setBounds(90, 160, 80, 30);

  noDistortionButton.setBounds(300, 100, 80, 30);
  tripleSmoothingDistortionButton.setBounds(300, 130, 80, 30);
  customDistortionEquationButton.setBounds(300, 160, 80, 30);
}

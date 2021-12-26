#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <cstddef>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(600, 440);

  enum RadioButton {
    ClipButtons = 100,
    DistortionButton = 101,
  };

  addAndMakeVisible(gainSliderLabel);
  addAndMakeVisible(clipSliderLabel);
  addAndMakeVisible(sawtoothIncrementSliderLabel);

  gainSliderLabel.setFont(juce::Font(12.0f, juce::Font::bold));
  gainSliderLabel.setText("Gain", juce::dontSendNotification);
  clipSliderLabel.setFont(juce::Font(12.0f, juce::Font::bold));
  clipSliderLabel.setText("Clip", juce::dontSendNotification);

  addAndMakeVisible(SquareClippingButton);
  addAndMakeVisible(SawToothClippingButton);
  addAndMakeVisible(noClippingButton);

  noClippingButton.setRadioGroupId(100);
  SquareClippingButton.setRadioGroupId(100);
  SawToothClippingButton.setRadioGroupId(100);

  noClippingButton.onClick = [this] {
    updateToggleState(&noClippingButton, "None");
  };
  SquareClippingButton.onClick = [this] {
    updateToggleState(&SquareClippingButton, "Square");
  };
  SawToothClippingButton.onClick = [this] {
    updateToggleState(&SawToothClippingButton, "SawTooth");
  };

  addAndMakeVisible(noDistortionButton);
  addAndMakeVisible(tripleExponentialSmoothingButton);
  addAndMakeVisible(customDistortionEquationButton);

  noDistortionButton.setRadioGroupId(101);
  tripleExponentialSmoothingButton.setRadioGroupId(101);
  customDistortionEquationButton.setRadioGroupId(101);

  noDistortionButton.onClick = [this] {
    updateToggleState(&noDistortionButton, "No Distortion");
  };
  tripleExponentialSmoothingButton.onClick = [this] {
    updateToggleState(&tripleExponentialSmoothingButton, "Triple Smoothing Distortion");
  };
  customDistortionEquationButton.onClick = [this] {
    updateToggleState(&customDistortionEquationButton, "Custom Distortion");
  };

  addAndMakeVisible(equationInput);
  equationInput.onReturnKey = [this] { onReturnPressed(&equationInput); };

  // addAndMakeVisible(sawToothIncrementSlider);
  //  sawToothIncrementSlider.setSliderStyle(
  //      juce::Slider::SliderStyle::LinearBarVertical);
  sawToothIncrementSlider.setRange(0.0, 0.0001);
  sawToothIncrementSlider.setValue(0);
  sawToothIncrementSlider.addListener(this);

  addAndMakeVisible(gainSlider);
  //  gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
  gainSlider.setRange(-40.0, 80);
  gainSlider.setValue(1);
  gainSlider.addListener(this);

  addAndMakeVisible(clipSlider);
  //  clipSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
  clipSlider.setRange(-1, 1);
  clipSlider.setValue(1);
  clipSlider.addListener(this);
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

void AudioPluginAudioProcessorEditor::updateToggleState(juce::Button *button,
                                                        juce::String name) {
  auto state = button->getToggleState();
  juce::String stateString = state ? "ON" : "OFF";

  if (button == &SawToothClippingButton) {
    audioProcessor.enableSawToothClipping = state;
  }

  if (button == &SquareClippingButton) {
    audioProcessor.enableSquareClipping = state;
  }

  if (button == &tripleExponentialSmoothingButton) {
    audioProcessor.enableTripleExponentialDistortion = state;
  }

  if (button == &customDistortionEquationButton) {
    audioProcessor.enableCustomDistortionEquation = state;
  }

  juce::Logger::outputDebugString(name + " Button changed to " + stateString);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
  if (slider == &gainSlider) {
    audioProcessor.rawVolume = pow(10, gainSlider.getValue() / 20);
  }

  if (slider == &clipSlider) {
    audioProcessor.clipThreshold = clipSlider.getValue();
  }

  if (slider == &sawToothIncrementSlider) {
    audioProcessor.currentSawToothStepIncrement = (float)clipSlider.getValue();
  }
}

void AudioPluginAudioProcessorEditor::onReturnPressed(
    juce::TextEditor *textEditor) {

  if (textEditor == &equationInput) {

    juce::String str = textEditor->getText();

    audioProcessor.currentDistortionEquation = str.toStdString();
  }
}

void AudioPluginAudioProcessorEditor::resized() {

  equationInput.setBounds(300, 200, 100, 60);

  gainSlider.setBounds(90, 330, getWidth() - 180, 20);
  clipSlider.setBounds(90, 350, getWidth() - 180, 20);
  sawToothIncrementSlider.setBounds(90, 370, getWidth() - 180, 20);

  gainSliderLabel.setBounds(55, 330, 40, 20);
  clipSliderLabel.setBounds(55, 350, 40, 20);

  noClippingButton.setBounds(90, 100, 80, 30);
  SquareClippingButton.setBounds(90, 130, 80, 30);
  SawToothClippingButton.setBounds(90, 160, 80, 30);

  noDistortionButton.setBounds(300, 100, 80, 30);
  tripleExponentialSmoothingButton.setBounds(300, 130, 80, 30);
  customDistortionEquationButton.setBounds(300, 160, 80, 30);
}

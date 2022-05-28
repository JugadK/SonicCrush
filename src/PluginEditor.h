#pragma once

#include "PluginProcessor.h"
#include "../modules/JUCE/modules/juce_opengl/juce_opengl.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        juce::OpenGLContext {
public:
  explicit AudioPluginAudioProcessorEditor(
      AudioPluginAudioProcessor &, juce::AudioProcessorValueTreeState &vts);
  ~AudioPluginAudioProcessorEditor() override;
  void updateToggleState(juce::Button *button, juce::String name);

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  juce::TextEditor equationInput;

private:
  juce::AudioProcessorValueTreeState &valueTreeState;

  typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
  typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

  juce::Label OptionLabel{{}, "Option"};
  juce::ToggleButton SquareClippingButton{"Normal 'Square' Clipping"},
      SawToothClippingButton{"SawTooth Clipping"},
      noClippingButton{"Disable Clipping"};

  juce::ToggleButton tripleSmoothingDistortionButton{
      "Triple Exponential Class"};

  juce::ToggleButton customDistortionEquationButton{
      "Custom Distortion Equation"},
      noDistortionButton{"Disable Distortion"};

  juce::Label gainSliderLabel{"Gain"};
  juce::Label postGainSliderLabel{"Post Gain"};
  juce::Label clipSliderLabel{"Clip Value"};
  juce::Label sawtoothIncrementSliderLabel;

  juce::Label distortionLabel;
  juce::Label clipLabel;

  void onReturnPressed(juce::TextEditor *textEditor);

  AudioPluginAudioProcessor &audioProcessor;

  juce::Slider gainSlider;
  juce::Slider postGainSlider;
  juce::Slider clipSlider;
  juce::Slider sawToothIncrementSlider;

  std::unique_ptr<SliderAttachment> preGainAttachment;
  std::unique_ptr<SliderAttachment> postGainAttachment;
  std::unique_ptr<SliderAttachment> clipAttachment;

  std::unique_ptr<ButtonAttachment> noDistortionAttachment;
  std::unique_ptr<ButtonAttachment> tripleSmoothingAttachment;
  std::unique_ptr<ButtonAttachment> customDistortionEquationAttachment;

  std::unique_ptr<ButtonAttachment> squareClippingAttachment;
  std::unique_ptr<ButtonAttachment> sawToothClippingAttachment;
  std::unique_ptr<ButtonAttachment> noClippingAttachment;


  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};

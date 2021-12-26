#pragma once

#include "PluginProcessor.h"
#include "modules/JUCE/modules/juce_opengl/juce_opengl.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        private juce::Slider::Listener, juce::OpenGLContext {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;
  void updateToggleState(juce::Button *button, juce::String name);

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

 

  
  juce::TextEditor equationInput;

  

private:
  void sliderValueChanged(juce::Slider *slider) override;

  juce::Label OptionLabel{{}, "Option"};
  juce::ToggleButton SquareClippingButton{"Normal 'Square' Clipping"},
      SawToothClippingButton{"SawTooth Clipping"},noClippingButton{"Disable Clipping"};

  juce::ToggleButton tripleExponentialSmoothingButton{"Triple Exponential Class"};

  juce::ToggleButton customDistortionEquationButton{"Custom Distortion Equation"},noDistortionButton{"Disable Distortion"};

  juce::Label gainSliderLabel{"Gain"};
  juce::Label clipSliderLabel{"Clip Value"};
  juce::Label sawtoothIncrementSliderLabel;

  juce::Label distortionLabel;
  juce::Label clipLabel;

  




  void onReturnPressed(juce::TextEditor *textEditor);

  AudioPluginAudioProcessor &audioProcessor;

  juce::Slider gainSlider; 

  juce::Slider clipSlider;

  juce::Slider sawToothIncrementSlider;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};


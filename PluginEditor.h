/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace juce;
//==============================================================================
/**
*/
class AndrewHp01volumePanAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 public Slider::Listener
{
public:
    AndrewHp01volumePanAudioProcessorEditor (AndrewHp01volumePanAudioProcessor&);
    ~AndrewHp01volumePanAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //calls whenever a slider changes
    void sliderValueChanged(Slider* slider) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AndrewHp01volumePanAudioProcessor& audioProcessor;
    juce::Slider mVolumeSlider;
    juce::Label volLabel;

    juce::Slider panSlider;
    juce::Label panLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AndrewHp01volumePanAudioProcessorEditor)
};

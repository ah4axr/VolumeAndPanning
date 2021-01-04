/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AndrewHp01volumePanAudioProcessorEditor::AndrewHp01volumePanAudioProcessorEditor (AndrewHp01volumePanAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 350);

    //pointer to audio params
    auto& processorParams = processor.getParameters();

    //slider attributes
    //x, y, w, h
    mVolumeSlider.setBounds(50, 20, 80, 280);
    mVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    //readOnly, w, h
    mVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 30);

    //Range of slider to range of param
    //pointer to param
    juce::AudioParameterFloat* volProcParam = (juce::AudioParameterFloat*)processorParams.getUnchecked(0);
    mVolumeSlider.setRange(volProcParam->range.start, volProcParam->range.end);
    mVolumeSlider.setValue(*volProcParam);
    mVolumeSlider.setTextValueSuffix(" dB");

    //make editor a listener
    mVolumeSlider.addListener(this);

    //add slider as child of audio processor editor
    addAndMakeVisible(mVolumeSlider);

    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&mVolumeSlider, false);

    ////////////////////////////////////////////////////////////////////////////////
    //slider attributes
    //x, y, w, h
    panSlider.setBounds(175, 110, 300, 100);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    //readOnly, w, h
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 30);

    //Range of slider to range of param
    //pointer to param
    juce::AudioParameterFloat* panProcParam = (juce::AudioParameterFloat*)processorParams.getUnchecked(1);
    panSlider.setRange(panProcParam->range.start, panProcParam->range.end);
    panSlider.setValue(*panProcParam);
    panSlider.setTextValueSuffix(" C");

    panSlider.addListener(this);

    //add slider as child of audio processor editor
    addAndMakeVisible(panSlider);

    addAndMakeVisible(panLabel);
    panLabel.setText("Panning", juce::dontSendNotification);
    panLabel.attachToComponent(&panSlider, false);
}

AndrewHp01volumePanAudioProcessorEditor::~AndrewHp01volumePanAudioProcessorEditor()
{
}

//==============================================================================
void AndrewHp01volumePanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Decibel Gain and Panning", getLocalBounds(), juce::Justification::centredTop, 1);
}

void AndrewHp01volumePanAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AndrewHp01volumePanAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //pointer to params in audio processor
    auto& processorParams = processor.getParameters();

    //compare pointer and slider using address
    if (slider == &mVolumeSlider)
    {
        //get pointer to first parameter
        AudioParameterFloat* volumeParam = (AudioParameterFloat*)processorParams.getUnchecked(0);

        //use slider val to set param in processor
        float sliderValue = mVolumeSlider.getValue();
        //set the new param
        *volumeParam = sliderValue;

        //debug prints
        //DBG("Volume slider set to: " << sliderValue);
    }

    if (slider == &panSlider)
    {
        //get correct parameter
        AudioParameterFloat* panningParam = (AudioParameterFloat*)processorParams.getUnchecked(1);

        //set param with slider
        float sliderValue = panSlider.getValue();
        
        //set new param
        *panningParam = sliderValue;

        //debug prints
        //DBG("Panning slider set to: " << sliderValue);
        if (*panningParam < 0.0)
        {
            panSlider.setTextValueSuffix(" L");
        }
        else if (*panningParam > 0.0)
        {
            panSlider.setTextValueSuffix(" R");
        }
        else
        {
            panSlider.setTextValueSuffix(" C");
        }
    }
}
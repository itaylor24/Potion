/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================x
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscComp(audioProcessor.apvts, "OSC1"), adsrComp(audioProcessor.apvts), chorusComp(audioProcessor.apvts), reverbComp(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);
    


//     oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
//
    
    
    addAndMakeVisible(oscComp);
    addAndMakeVisible(chorusComp);
    addAndMakeVisible(reverbComp);
    addAndMakeVisible(adsrComp);

}
    

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//
//    g.setColour (juce::Colours::black);
//    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.fillAll (juce::Colours::white);
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    adsrComp.setBounds (getWidth() / 3, 0, (getWidth() / 2) * 1.2, getHeight()/3);
    chorusComp.setBounds(getWidth()/ 3, getHeight()/3, (getWidth() /2 )* 1.2, getHeight()/3);
    reverbComp.setBounds(getWidth()/ 3, getHeight()*2/3, (getWidth() /2 )* 1.2, getHeight()/3);
    
    oscComp.setBounds(10,10,100,30);
    
}



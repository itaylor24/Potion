/*
  ==============================================================================

    OscComponent.cpp
    Created: 8 May 2024 3:17:25am
    Author:  Isaac Taylor

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String selectorId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices {"Sine", "Saw", "Square", "Triangle"};
    waveformSelector.addItemList(choices, 2);
    addAndMakeVisible(waveformSelector);
    
    waveformSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, selectorId, waveformSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("OscComponent", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
    g.fillAll(juce::Colours::white);
}

void OscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    waveformSelector.setBounds(0,0,90,20);
}

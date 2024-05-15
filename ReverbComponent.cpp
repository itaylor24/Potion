/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 12 May 2024 2:30:44pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    dryAttachment = std::make_unique<SliderAttachment>(apvts,  "DRY",  drySlider);
    wetAttachment = std::make_unique<SliderAttachment>(apvts,   "WET",   wetSlider);
    roomAttachment = std::make_unique<SliderAttachment>(apvts, "ROOM", roomSlider);
    dampAttachment = std::make_unique<SliderAttachment>(apvts, "DAMP", dampSlider);
    
    setSliderParams (drySlider, dryLabel);
    setSliderParams (wetSlider, wetLabel);
    setSliderParams (roomSlider, roomLabel);
    setSliderParams (dampSlider, dampLabel);
    
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::white);
    auto bounds = getLocalBounds();
    g.setColour (juce::Colours::black);
    g.drawRoundedRectangle (bounds.toFloat().reduced(10.0f), 5.0f, 2.0f);
    g.setColour (juce::Colours::blue);
    g.setFont (15.0f);
    g.setFont (g.getCurrentFont().boldened());
    g.drawText ("Reverb", 20, 15, 100, 25, juce::Justification::left);
    
}

void ReverbComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() * .7;
    const auto sliderStartX = 15;
    const auto sliderStartY = 55;
    
    const auto labelStartY = 35;
    const auto labelWidth = 70;
    const auto labelHeight = 18;
    const auto labelOffset = 5;

//    drySlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
//    wetSlider.setBounds (drySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    roomSlider.setBounds (wetSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    dampSlider.setBounds (roomSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    
    dryLabel.setBounds (sliderStartX - labelOffset, labelStartY, labelWidth, labelHeight);
    drySlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);

    wetLabel.setBounds (drySlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    wetSlider.setBounds (drySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    roomLabel.setBounds (wetSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    roomSlider.setBounds (wetSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    dampLabel.setBounds (roomSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    dampSlider.setBounds (roomSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    

}

void ReverbComponent::setSliderParams (juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    label.setFont(15.0f);
    label.setColour(juce::Label::textColourId, juce::Colours::blue);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible (slider);
}

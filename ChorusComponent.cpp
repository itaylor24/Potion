/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 9 May 2024 4:55:21pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    rateAttachment = std::make_unique<SliderAttachment>(apvts,  "RATE",  rateSlider);
    depthAttachment = std::make_unique<SliderAttachment>(apvts,   "DEPTH",   depthSlider);
    delayAttachment = std::make_unique<SliderAttachment>(apvts, "CENTERDELAY", delaySlider);
    feedbackAttachment = std::make_unique<SliderAttachment>(apvts, "FEEDBACK", feedbackSlider);
    mixAttachment = std::make_unique<SliderAttachment>(apvts, "MIX", mixSlider);
    
    setSliderParams (rateSlider, rateLabel);
    setSliderParams (depthSlider, depthLabel);
    setSliderParams (delaySlider, delayLabel);
    setSliderParams (feedbackSlider, feedbackLabel);
    setSliderParams (mixSlider, mixLabel);
    
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
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
    g.drawText ("Chorus", 20, 15, 100, 25, juce::Justification::left);
    
}

void ChorusComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 5 - padding;
    const auto sliderHeight = bounds.getHeight() * .7;
    const auto sliderStartX = 15;
    const auto sliderStartY = 55;
    
    const auto labelStartY = 35;
    const auto labelWidth = 70;
    const auto labelHeight = 18;
    const auto labelOffset = 5;

//    rateSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
//    depthSlider.setBounds (rateSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    delaySlider.setBounds (depthSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    feedbackSlider.setBounds (delaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    mixSlider.setBounds (feedbackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    
    rateLabel.setBounds (sliderStartX - labelOffset, labelStartY, labelWidth, labelHeight);
    rateSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);

    depthLabel.setBounds (rateSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    depthSlider.setBounds (rateSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    delayLabel.setBounds (depthSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    delaySlider.setBounds (depthSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    feedbackLabel.setBounds (delaySlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    feedbackSlider.setBounds (delaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    
    mixLabel.setBounds (feedbackSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    mixSlider.setBounds (feedbackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void ChorusComponent::setSliderParams (juce::Slider& slider, juce::Label& label)
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

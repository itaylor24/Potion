/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 8 May 2024 2:18:53pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

     attackAttachment = std::make_unique<SliderAttachment>(apvts,  "ATTACK",  attackSlider);
     decayAttachment = std::make_unique<SliderAttachment>(apvts,   "DECAY",   decaySlider);
     sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
     releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParams (attackSlider, attackLabel);
    setSliderParams (decaySlider, decayLabel);
    setSliderParams (sustainSlider, sustainLabel);
    setSliderParams (releaseSlider, releaseLabel);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
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
    g.drawText ("ADSR", 20, 15, 100, 25, juce::Justification::left);
}

void AdsrComponent::resized()
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

//    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
//    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
//    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    
    attackLabel.setBounds (sliderStartX - labelOffset, labelStartY, labelWidth, labelHeight);
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);

    decayLabel.setBounds (attackSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    sustainLabel.setBounds (decaySlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    releaseLabel.setBounds (sustainSlider.getRight() + padding - labelOffset, labelStartY, labelWidth, labelHeight);
    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    
//    const auto startX = 15;
//    const auto startY = 55;
//    const auto width = sliderWidth;
//    const auto height = sliderHeight + 20;
        
//    attack.setBounds (startX, startY, width, height);
//    decay.setBounds (attack.getRight(), startY, sliderWidth, sliderHeight);
//    sustain.setBounds (decay.getRight(), startY, sliderWidth, sliderHeight);
//    release.setBounds (sustain.getRight(), startY, sliderWidth, sliderHeight);
}

void AdsrComponent::setSliderParams (juce::Slider& slider, juce::Label& label)
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

/*
  ==============================================================================

    ChorusComponent.h
    Created: 9 May 2024 4:55:21pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void setSliderParams (juce::Slider& slider, juce::Label& label);
    
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider delaySlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> delayAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;
    
    juce::Label rateLabel { "RATE", "RATE" };
    juce::Label depthLabel { "DEPTH", "DEPTH" };
    juce::Label delayLabel { "DELAY", "DELAY" };
    juce::Label feedbackLabel { "FEEDBACK", "FEEDBACK" };
    juce::Label mixLabel { "MIX", "MIX" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};

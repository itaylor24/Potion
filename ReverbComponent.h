/*
  ==============================================================================

    ReverbComponent.h
    Created: 12 May 2024 2:30:44pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void setSliderParams (juce::Slider& slider, juce::Label& label);
    
    juce::Slider drySlider;
    juce::Slider wetSlider;
    juce::Slider roomSlider;
    juce::Slider dampSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> dryAttachment;
    std::unique_ptr<SliderAttachment> wetAttachment;
    std::unique_ptr<SliderAttachment> roomAttachment;
    std::unique_ptr<SliderAttachment> dampAttachment;
    
    juce::Label dryLabel { "DRY", "DRY" };
    juce::Label wetLabel { "WET", "WET" };
    juce::Label roomLabel { "ROOM", "ROOM" };
    juce::Label dampLabel { "DAMP", "DAMP" };

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

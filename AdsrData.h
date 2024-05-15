/*
  ==============================================================================

    AdsrData.h
    Created: 8 May 2024 2:19:28pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR {
public:
    void update (const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams; 
}; 


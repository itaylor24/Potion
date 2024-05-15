/*
  ==============================================================================

    OscData.h
    Created: 8 May 2024 2:16:52am
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public:
    void setWaveform(const int type);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setOscFrequency(const int midiNoteNumber);

private:
    
};

/*
  ==============================================================================

    SynthSound.h
    Created: 1 May 2024 6:32:09pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};

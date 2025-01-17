/*
  ==============================================================================

    SynthVoice.h
    Created: 1 May 2024 6:31:43pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "OscData.h"
#include "AdsrData.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    OscData& getOsc(){return osc;}
   
   
private:
    
//    juce::ADSR adsr;
//    juce::ADSR::Parameters adsrParams;
    AdsrData adsr;
    OscData osc;
    
    juce::dsp::Gain<float> gain;
    bool isPrepared = false;
    juce::AudioBuffer<float> synthBuffer;

};


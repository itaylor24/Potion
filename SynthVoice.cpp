/*
  ==============================================================================

    SynthVoice.cpp
    Created: 1 May 2024 6:31:43pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setOscFrequency(midiNoteNumber); 
    adsr.noteOn();
    
    
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (! allowTailOff || ! adsr.isActive()){
            clearCurrentNote();
    }
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
   

}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
}
void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepareToPlay(spec);
    gain.prepare(spec);
    
    gain.setGainLinear(0.3f);

    isPrepared = true;
}


void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if (! isVoiceActive()){
            return;
    }
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());

    if (startSample != 0){
        jassertfalse;
    }

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);

        if (! adsr.isActive()){
            clearCurrentNote();
        }
    }
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsr.update(attack, decay, sustain, release);
}

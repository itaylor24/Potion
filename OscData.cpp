/*
  ==============================================================================

    OscData.cpp
    Created: 8 May 2024 2:16:52am
    Author:  Isaac Taylor

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveform(const int type){
   // return std::sin(x);
    //return x / MathConstants<float>::pi;
    //return x < 0.0f ? -1.0f : 1.0f;
    switch(type){
        case 0:
            //sin
            initialise([](float x){return std::sin(x);});
            break;
        case 1:
            //saw
            initialise([](float x){return x / juce::MathConstants<float>::pi;});
            break;
        case 2:
            //square
            initialise([](float x){return x < 0.0f ? -1.0f : 1.0f;});
            break;
        case 3:
            //triangle
            initialise([](float x){
                return (std::acos(std::sin(x))/ juce::MathConstants<float>::pi/2) - 1.0f;
            });
        default:
            jassertfalse;
            break;
    }
    
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec){
    prepare(spec); 
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block){
    
    process(juce::dsp::ProcessContextReplacing<float>(block));

}

void OscData::setOscFrequency(const int midiNoteNumber){
    
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());

    
    
    apvts.addParameterListener ("RATE", this);
    apvts.addParameterListener ("DEPTH", this);
    apvts.addParameterListener ("CENTREDELAY", this);
    apvts.addParameterListener ("FEEDBACK", this);
    apvts.addParameterListener ("DRY", this);
    apvts.addParameterListener ("WET", this);
    apvts.addParameterListener ("ROOM", this);
    apvts.addParameterListener ("DAMP", this);

    
    
    
    chorus.setRate (50);
    chorus.setDepth (.08);
    chorus.setCentreDelay (7);
    chorus.setFeedback (.2);
    chorus.setMix (.5);
    
    
    
    reverbParameters.dryLevel = 0.2f;
    reverbParameters.wetLevel = .8f;
    reverbParameters.roomSize = .65f;
    reverbParameters.damping = 0.8f;
    
    reverb.setParameters(reverbParameters);
    
}

SynthAudioProcessor::~SynthAudioProcessor()
{
    apvts.removeParameterListener ("RATE", this);
    apvts.removeParameterListener ("DEPTH", this);
    apvts.removeParameterListener ("CENTREDELAY", this);
    apvts.removeParameterListener ("FEEDBACK", this);
    apvts.removeParameterListener ("MIX", this);
    apvts.addParameterListener ("DRY", this);
    apvts.addParameterListener ("WET", this);
    apvts.addParameterListener ("ROOM", this);
    apvts.addParameterListener ("DAMP", this);
}

//==============================================================================
const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
    reverb.setSampleRate(sampleRate);
    reverb.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    
    chorus.prepare(spec);
    chorus.reset();
    
    for(int i = 0; i < synth.getNumVoices(); i++){
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    
    
    
    for(int i = 0; i < synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            
            //OSC Controls
            //ADSR
            //LFO?
            
            auto& attack = *apvts.getRawParameterValue ("ATTACK");
            auto& decay = *apvts.getRawParameterValue ("DECAY");
            auto& sustain = *apvts.getRawParameterValue ("SUSTAIN");
            auto& release = *apvts.getRawParameterValue ("RELEASE");
            
            auto& waveformType1 = *apvts.getRawParameterValue("OSC1");
            
            
            voice->getOsc().setWaveform(waveformType1);
            voice->updateADSR (attack.load(), decay.load(), sustain.load(), release.load());
            
            
        }
        
    }
    
    for (const juce::MidiMessageMetadata metadata : midiMessages){
        if (metadata.numBytes == 3){
            juce::Logger::writeToLog ("TimeStamp: " + juce::String (metadata.getMessage().getTimeStamp()));
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> block(buffer);
    chorus.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    reverb.processStereo (buffer.getWritePointer (0), buffer.getWritePointer (1), buffer.getNumSamples());
    
//    auto& rate = *apvts.getRawParameterValue("RATE");
//    auto& depth = *apvts.getRawParameterValue("DEPTH");
//    auto& centerdelay = *apvts.getRawParameterValue("CENTERDELAY");
//    auto& feedback = *apvts.getRawParameterValue("FEEDBACK");
//    auto& mix = *apvts.getRawParameterValue("MIX");
//
//    chorus.setRate(rate);
//    chorus.setDepth(depth);
//    chorus.setCentreDelay(centerdelay);
//    chorus.setFeedback(feedback);
//    chorus.setMix(mix);
    
    
    
//    reverb.processMono (buffer.getWritePointer (0), buffer.getNumSamples());
    //const auto numChannels = fmin (totalNumInputChannels, totalNumOutputChannels);
    
    //REVERB
//    if (numChannels == 1){
//        reverb.processMono (buffer.getWritePointer (0), buffer.getNumSamples());
//    }
//    else if (numChannels == 2){
//        reverb.processStereo (buffer.getWritePointer (0), buffer.getWritePointer (1), buffer.getNumSamples());
//    }
    

}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

void SynthAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    if (parameterID == "RATE")
        chorus.setRate (newValue);
    
    if (parameterID == "DEPTH")
        chorus.setDepth (newValue);
    
    if (parameterID == "CENTERDELAY")
        chorus.setCentreDelay (newValue);
    
    if (parameterID == "FEEDBACK")
        chorus.setFeedback (newValue);
    
    if (parameterID == "MIX")
        chorus.setMix (newValue);
    
    
    if (parameterID == "DRY")
        reverbParameters.dryLevel = newValue;
        reverb.setParameters(reverbParameters);
      
    if (parameterID == "WET")
        reverbParameters.wetLevel = newValue;
        reverb.setParameters(reverbParameters);
        
    if (parameterID == "ROOM")
        reverbParameters.roomSize = newValue;
        reverb.setParameters(reverbParameters);
        
    if (parameterID == "DAMP")
        reverbParameters.damping = newValue;
        reverb.setParameters(reverbParameters);
}

juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // OSC select
    params.push_back (std::make_unique<juce::AudioParameterChoice> ("OSC1", "Oscillator 1", juce::StringArray { "Sine", "Saw", "Square", "Triangle"}, 0));

    // ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, .01f}, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, .01f}, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, .01f}, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, .01f}, 0.4f));
    
    using Range = juce::NormalisableRange<float>;
        
    params.push_back (std::make_unique<juce::AudioParameterInt>  ("RATE", "Rate", 0, 99, 50));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", Range { 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterInt>  ("CENTERDELAY", "Center Delay", 1, 100, 7));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", Range { -1.0f, 1.0f, 0.01f }, 0.2f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", Range { 0.0f, 1.0f, 0.01f }, 0.5f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DRY", "Dry Level", Range { 0.0f, 1.0f, 0.01f }, 0.2f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("WET", "Wet Level", Range { 0.0f, 1.0f, 0.01f }, 0.8f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ROOM", "Room Level", Range { 0.0f, 1.0f, 0.01f }, 0.65f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DAMP", "Damp Level", Range { 0.0f, 1.0f, 0.01f }, 0.8f));

    
    return { params.begin(), params.end() };
    
}

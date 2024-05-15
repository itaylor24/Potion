/*
  ==============================================================================

    AdsrData.cpp
    Created: 8 May 2024 2:19:28pm
    Author:  Isaac Taylor

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update (const float attack, const float decay, const float sustain, const float release){
    
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters (adsrParams);
    
}

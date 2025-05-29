//
// Created by Praneeth Bandi on 5/29/25.
//

#include "../include/Oscillator.h"

#include <algorithm>
#include <cmath>

Oscillator::Oscillator(float freq, float amp, int sampleRate, int bitDepth) : frequency(freq), amplitude(amp), sampleRate(sampleRate), bitDepth(bitDepth) {
    offset = 2 * M_PI * frequency / sampleRate;
    angle = 0.0f;
    maxAmplitude = pow(2, bitDepth - 1) - 1;
}

int Oscillator::process() {
    auto sample = amplitude * sin(angle);
    angle += offset;
    int intSample = static_cast<int>(sample * maxAmplitude);
    return intSample;
}

int Oscillator::getSampleRate() const {
    return sampleRate;
}

int Oscillator::getBitDepth() const {
    return bitDepth;
}



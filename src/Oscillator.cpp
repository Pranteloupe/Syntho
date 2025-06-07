//
// Created by Praneeth Bandi on 5/29/25.
//

#include "../include/Oscillator.h"

#include <algorithm>
#include <cmath>

Oscillator::Oscillator(float freq, float amp, int sampleRate) : frequency(freq), amplitude(amp), sampleRate(sampleRate) {
    offset = 2 * M_PI * frequency / sampleRate;
    angle = 0.0f;
}

float Oscillator::process() {
    auto sample = amplitude * sin(angle);
    angle += offset;
    return sample;
}

int Oscillator::getSampleRate() const {
    return sampleRate;
}

void Oscillator::setFrequency(float freq) {
    frequency = freq;
    angle = 0.0f;
    offset = 2 * M_PI * frequency / sampleRate;
}

float Oscillator::getFrequency() const {
    return frequency;
}




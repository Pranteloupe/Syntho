//
// Created by Praneeth Bandi on 5/29/25.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H



class Oscillator {
public:
    Oscillator(float freq, float amp, int sampleRate, int bitDepth);
    int process();
    [[nodiscard]] int getSampleRate() const;
    [[nodiscard]] int getBitDepth() const;

private:
    float frequency;
    float amplitude;
    float angle;
    float offset;
    int sampleRate;
    int bitDepth;
    double maxAmplitude;
};



#endif //OSCILLATOR_H

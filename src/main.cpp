#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include "portaudio.h"

#include "../include/Oscillator.h"
using namespace std;

#define SAMPLE_RATE 44100
#define NUM_SECONDS 2
#define FRAMES_PER_BUFFER 1024
#define NUM_CHANNELS 2

void writeToFile(ofstream &file, int value, int size) {
  file.write(reinterpret_cast<const char*>(&value), size);
}

int stopProgram(const PaError error) {
  std::cerr << "Port Audio error: " << Pa_GetErrorText(error) << std::endl;
  PaError endError = Pa_Terminate();
  if (endError != paNoError) {
    std::cerr << "Termination Error: " << Pa_GetErrorText(endError) << std::endl;
  }
  return 1;
}

int main() {
  PaStream *stream;
  PaStreamParameters outputParameters;
  float buffer[FRAMES_PER_BUFFER][NUM_CHANNELS];

  PaError err = Pa_Initialize();
  if (err != paNoError) {
    stopProgram(err);
  }

  outputParameters.device = Pa_GetDefaultOutputDevice();
  outputParameters.channelCount = NUM_CHANNELS;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  err = Pa_OpenStream(&stream, nullptr, &outputParameters, SAMPLE_RATE,
    FRAMES_PER_BUFFER, paClipOff, nullptr, nullptr);
  if (err != paNoError) {
    stopProgram(err);
  }

  Oscillator leftOscillator(440, 0.5, 44100);
  Oscillator rightOscillator(440, 0.7, 44100);

  for (int k = 0; k < 3; k++) {
    err = Pa_StartStream(stream);
    if (err != paNoError) {
      stopProgram(err);
    }

    constexpr int bufferCount = ((NUM_SECONDS * SAMPLE_RATE) / FRAMES_PER_BUFFER);
    for (int i = 0; i < bufferCount; i++) {
      for (auto & j : buffer) {
        j[0] = leftOscillator.process();
        j[1] = rightOscillator.process();
      }
      err = Pa_WriteStream(stream, buffer, FRAMES_PER_BUFFER);
      if (err != paNoError) {
        stopProgram(err);
      }
    }
    err = Pa_StopStream(stream);
    if (err != paNoError) {
      stopProgram(err);
    }
    rightOscillator.setFrequency(rightOscillator.getFrequency() + 200);

    Pa_Sleep(1000);
  }

  err = Pa_CloseStream(stream);
  if (err != paNoError) {
    stopProgram(err);
  }

  err = Pa_Terminate();
  if (err != paNoError) {
    stopProgram(err);
  }

  return 0;
  // Oscillator oscillator(440, 0.5, 44100, 16);
  // ofstream audioFile;
  // audioFile.open("waveform.wav", ios::binary);
  //
  // int sampleRate = oscillator.getSampleRate();
  // int bitDepth = oscillator.getBitDepth();
  //
  // //Header chunk
  // audioFile << "RIFF";
  // audioFile << "----"; //placeholder for size
  // audioFile << "WAVE";
  //
  // //Format chunk
  // audioFile << "fmt "; //space included so it can be 4 bytes
  // writeToFile(audioFile, 16, 4); //Size
  // writeToFile(audioFile, 1, 2); //Compression Code
  // writeToFile(audioFile, 1, 2); //# of channels
  // writeToFile(audioFile, sampleRate, 4);
  // writeToFile(audioFile, sampleRate * bitDepth / 8, 4); //Byte Rate
  // writeToFile(audioFile, bitDepth / 8, 2); //Block Align
  // writeToFile(audioFile, bitDepth, 2);
  //
  // //Data Chunk
  // audioFile << "data";
  // audioFile << "----";
  //
  // long long preData = audioFile.tellp(); //returns current point in file
  //
  // for (int i = 0; i < sampleRate * 5; i++) {
  //   int sample = oscillator.process();
  //   writeToFile(audioFile, sample, 2);
  // }
  //
  // long long postData = audioFile.tellp();
  //
  // audioFile.seekp(preData - 4);
  // writeToFile(audioFile, static_cast<int>(postData - preData), 4);
  //
  // audioFile.seekp(4, ios::beg);
  // writeToFile(audioFile, static_cast<int>(postData - 8), 4); //Subtract 8 to not include header id and size
  //
  // audioFile.close();
  //
  // return 0;
}
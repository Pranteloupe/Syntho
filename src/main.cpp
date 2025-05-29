#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include "../include/Oscillator.h"
using namespace std;

void writeToFile(ofstream &file, int value, int size) {
  file.write(reinterpret_cast<const char*>(&value), size);
}

int main() {
  Oscillator oscillator(440, 0.5, 44100, 16);
  ofstream audioFile;
  audioFile.open("waveform.wav", ios::binary);

  int sampleRate = oscillator.getSampleRate();
  int bitDepth = oscillator.getBitDepth();

  //Header chunk
  audioFile << "RIFF";
  audioFile << "----"; //placeholder for size
  audioFile << "WAVE";

  //Format chunk
  audioFile << "fmt "; //space included so it can be 4 bytes
  writeToFile(audioFile, 16, 4); //Size
  writeToFile(audioFile, 1, 2); //Compression Code
  writeToFile(audioFile, 1, 2); //# of channels
  writeToFile(audioFile, sampleRate, 4);
  writeToFile(audioFile, sampleRate * bitDepth / 8, 4); //Byte Rate
  writeToFile(audioFile, bitDepth / 8, 2); //Block Align
  writeToFile(audioFile, bitDepth, 2);

  //Data Chunk
  audioFile << "data";
  audioFile << "----";

  long long preData = audioFile.tellp(); //returns current point in file

  for (int i = 0; i < sampleRate * 5; i++) {
    int sample = oscillator.process();
    writeToFile(audioFile, sample, 2);
  }

  long long postData = audioFile.tellp();

  audioFile.seekp(preData - 4);
  writeToFile(audioFile, static_cast<int>(postData - preData), 4);

  audioFile.seekp(4, ios::beg);
  writeToFile(audioFile, static_cast<int>(postData - 8), 4); //Subtract 8 to not include header id and size

  audioFile.close();

  return 0;
}
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const int sampleRate = 44100;

/* Bit depth */
const int bitDepth = 16;

/* Write sine wave osc */
class SineOscillator
{
    mutable float frequency, amplitude, angle = 0.0f, offset = 0.0;

public:
    SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp)
    {
        offset = 2 * M_PI * frequency / sampleRate;
    }
    /*
    Generate next sample value when called
    y(t)=A sin(2πfx + ϕ) A = amplitude from 1 to -1
    f is frequency, ϕ is phase offset, x is x axis, 
    which is sampling intervals. for example 44100 
    samples (comparable to time domain in analog audio)
 */
    float process()
    {
        /* Asin(2pif/sampling rate) */
        float sample = amplitude * sin(angle);
        angle += offset;
        return sample;
    }
};

int main()
{
    int duration = 2;
    ofstream audioFile;
    audioFile.open("waveform", ios::binary);
    SineOscillator sineOscillator(440, 0.5);
    float maxAmplitude = pow(2, bitDepth - 1) - 1;
    for (int i = 0; i < sampleRate * duration; i++)
    {
        float sample = sineOscillator.process();
        int intSample = static_cast<int>(sample * maxAmplitude);
        audioFile.write(reinterpret_cast<char *>(&intSample), 2);
    }
    audioFile.close();
    return 0;
}
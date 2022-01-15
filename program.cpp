#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

const int sampleRate = 44100;

/* Write sine wave osc */
class SineOscillator
{
   mutable float frequency,amplitude, angle = 0.0f, offset = 0.0;

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
    audioFile.open("waveform");
    SineOscillator sineOscillator(440, 0.5);
    for (int i = 0; i < sampleRate * duration; i++)
    {
        audioFile << sineOscillator.process() << endl;
    }
    audioFile.close();
    cout << sizeof(float) << endl;
    cout << sizeof(int) << endl;
    return 0;
}
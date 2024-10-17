#include <iostream>
#include<vector>
#include <cmath>   // For sin() and other math functions
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define pi if it's not available
#endif
vector<float>sine;
vector<float>square;
vector<float>triangular;
class base {
public:
    float time;
    float frequency;
    float amplitude;
    float phase;

    // Constructor
    base(float time, float frequency, float amplitude, float phase) {
        this->time = time;
        this->frequency = frequency;
        this->amplitude = amplitude;
        this->phase = phase;
    }

    // Virtual function to calculate the wave value at a particular time
    virtual void waveattime() {
        for (int i = 0; i < 100; i++) {
            sine.push_back(int(amplitude * sin(2 * M_PI * frequency * time + phase) + 32767));
            time += 0.01; // Increment time to simulate different wave points
        }
    }

    // Virtual function to handle frequency changes
    virtual void changeFrequency(float newFrequency) {
        frequency = newFrequency;
    }

    // Virtual function to handle amplitude changes
    virtual void changeAmplitude(float newAmplitude) {
        amplitude = newAmplitude;
    }

    // Virtual function to handle phase changes
    virtual void changePhase(float newPhase) {
        phase = newPhase;
    }
};

// Derived class for square wave
class square_wave : public base {
public:
    square_wave(float time, float frequency, float amplitude, float phase) 
        : base(time, frequency, amplitude, phase) {}

    // Override waveattime to generate square wave
    void waveattime() override {
        for (int i = 0; i < 100; i++) {
            // Square wave logic: output high (+amplitude) or low (-amplitude) based on the sine wave's sign
            if (sin(2 * M_PI * frequency * time + phase) >= 0)
                square.push_back(int(amplitude + 32767));  // High state
            else
                square.push_back(int(-amplitude + 32767)); // Low state
            time += 0.01;
        }
    }
};

// Derived class for triangular wave
class triangular_wave : public base {
public:
    triangular_wave(float time, float frequency, float amplitude, float phase) 
        : base(time, frequency, amplitude, phase) {}

    // Override waveattime to generate triangular wave
    void waveattime() override {
        for (int i = 0; i < 100; i++) {
            // Triangular wave logic: Linear rise and fall
            float cycle = fmod(time * frequency + phase, 1.0f);  // Normalize to one period
            float value = (cycle < 0.5) ? (2.0 * cycle) : (2.0 * (1 - cycle)); // Rise or fall in the cycle
            triangular.push_back(int(amplitude * (2 * value - 1) + 32767));  // Scale between -amplitude and +amplitude
            time += 0.01;
        }
    }
};

int main() {
    // Base sine wave
    int t,f,a,p;
    cin>>t>>f>>a>>p;
    base b(t,f,a,p); // Create base object with time=0, frequency=440Hz, amplitude=1, phase=0
    cout << "Sine Wave:\n";
    b.waveattime();                // Display sine wave

    // Square wave
    square_wave sq(t,f,a,p);
    cout << "\nSquare Wave:\n";
    sq.waveattime();               // Display square wave

    // Triangular wave
    triangular_wave tri(t,f,a,p);
    cout << "\nTriangular Wave:\n";
    tri.waveattime();              // Display triangular wave

    return 0;
}

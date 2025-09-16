#include <iostream>
#include <vector>
#include "LIFNeuron.hpp"

int main() {
    LIFNeuron neuron;
    std::vector<double> inputs = {0.5, 0.7, 1.2, 0.0, 0.0, 1.5}; // toy current
    for (double I : inputs) {
        neuron.step(I);
        std::cout << "V=" << neuron.getPotential() 
                  << " Spiked=" << neuron.didSpike() << "\n";
    }
    return 0;
}

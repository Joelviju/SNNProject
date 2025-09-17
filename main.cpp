/*#include <iostream>
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
} */
#include "src/SNNNetwork.hpp"
#include <iostream>

int main() {
    // 2 input neurons, 2 output neurons
    SNNNetwork net(2, 2);

    // XOR training set
    std::vector<std::vector<double>> inputs = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };
    std::vector<int> targets = {0, 1, 1, 0};

    // Train
    net.train(inputs, targets, 10, 0.1);

    return 0;
}


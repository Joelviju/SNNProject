#ifndef SNNNETWORK_HPP
#define SNNNETWORK_HPP

#include <vector>
#include "LIFNeuron.hpp"

class SNNNetwork {
private:
    std::vector<LIFNeuron> inputNeurons;
    std::vector<LIFNeuron> outputNeurons;
    std::vector<std::vector<double>> weights;

public:
    SNNNetwork(int inputSize, int outputSize);

    void step(const std::vector<double>& input);
    void applySTDP();

    // NEW: supervised training with surrogate gradients
    void train(const std::vector<std::vector<double>>& inputs,
               const std::vector<int>& targets,
               int epochs, double lr);
};

#endif

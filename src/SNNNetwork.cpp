#include "SNNNetwork.hpp"
#include <iostream>
#include <cmath>

// Simple surrogate gradient (fast sigmoid derivative)
double surrogateGradient(double v, double vth) {
    double x = (v - vth) * 10.0;
    double sig = 1.0 / (1.0 + exp(-x));
    return sig * (1.0 - sig);
}

SNNNetwork::SNNNetwork(int inputSize, int outputSize) {
    for (int i = 0; i < inputSize; ++i)
        inputNeurons.push_back(LIFNeuron());

    for (int j = 0; j < outputSize; ++j)
        outputNeurons.push_back(LIFNeuron());

    weights.resize(inputSize, std::vector<double>(outputSize, 0.1));
}

void SNNNetwork::step(const std::vector<double>& input) {
    // input neurons
    for (size_t i = 0; i < inputNeurons.size(); ++i) {
        inputNeurons[i].step(input[i]);
    }

    // output neurons
    for (size_t j = 0; j < outputNeurons.size(); ++j) {
        double totalInput = 0.0;
        for (size_t i = 0; i < inputNeurons.size(); ++i) {
            if (inputNeurons[i].didSpike()) {
                totalInput += weights[i][j];
            }
        }
        outputNeurons[j].step(totalInput);
    }
}

void SNNNetwork::applySTDP() {
    // keep this for unsupervised experiments
}

void SNNNetwork::train(const std::vector<std::vector<double>>& inputs,
                       const std::vector<int>& targets,
                       int epochs, double lr) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        double totalLoss = 0.0;

        for (size_t sample = 0; sample < inputs.size(); ++sample) {
            // 1. Forward pass
            step(inputs[sample]);

            // 2. Compute outputs (spikes)
            std::vector<double> outputs;
            for (auto& neuron : outputNeurons)
                outputs.push_back(neuron.didSpike() ? 1.0 : 0.0);

            // 3. Loss (MSE with one-hot target)
            std::vector<double> targetVec(outputs.size(), 0.0);
            targetVec[targets[sample]] = 1.0;

            double loss = 0.0;
            for (size_t i = 0; i < outputs.size(); i++) {
                double diff = outputs[i] - targetVec[i];
                loss += 0.5 * diff * diff;
            }
            totalLoss += loss;

            // 4. Backprop with surrogate gradients
            for (size_t j = 0; j < outputNeurons.size(); j++) {
                double error = outputs[j] - targetVec[j];
                double gradOut = error * surrogateGradient(outputNeurons[j].getPotential(), 1.0);

                for (size_t i = 0; i < inputNeurons.size(); i++) {
                    double grad = gradOut * (inputNeurons[i].didSpike() ? 1.0 : 0.0);
                    weights[i][j] -= lr * grad;
                }
            }

            // 5. Reset neurons after each sample
            for (auto& n : inputNeurons) n.reset();
            for (auto& n : outputNeurons) n.reset();
        }

        std::cout << "Epoch " << epoch << " - Loss: " << totalLoss << std::endl;
    }
}

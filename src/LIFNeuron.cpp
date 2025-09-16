#include "LIFNeuron.hpp"

LIFNeuron::LIFNeuron(double vth, double tau, double vreset)
    : v(0.0), vth(vth), tau(tau), vreset(vreset), spiked(false) {}

void LIFNeuron::step(double input_current) {
    v += (-v / tau) + input_current;
    spiked = (v >= vth);
    if (spiked) v = vreset;
}

double LIFNeuron::getPotential() const { return v; }
bool LIFNeuron::didSpike() const { return spiked; }
void LIFNeuron::reset() { v = 0.0; spiked = false; }



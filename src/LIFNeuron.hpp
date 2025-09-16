#ifndef LIFNEURON_HPP
#define LIFNEURON_HPP

class LIFNeuron {
private:
    double v;       // membrane potential
    double vth;     // threshold
    double vreset;  // reset value
    double tau;     // time constant
    bool spiked;    // did it fire this step?

public:
    LIFNeuron(double vth=1.0, double tau=20.0, double vreset=0.0);

    void step(double input_current);
    double getPotential() const;
    bool didSpike() const;
    void reset();
};

#endif // LIFNEURON_HPP

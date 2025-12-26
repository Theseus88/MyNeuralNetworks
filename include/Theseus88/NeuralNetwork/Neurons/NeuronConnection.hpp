// NeuronConnection.hpp
#ifndef THESEUS88_NEURONCONNECTION_HPP
#define THESEUS88_NEURONCONNECTION_HPP

#include "../NeuralNetworkCore.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class NeuronConnection {
    public:
        // Public Member Variables
        T m_input, m_weight, m_gradient, m_velocity, m_lookaheadWeight, m_lookaheadGradient;

        // Public Member Constructors
        NeuronConnection();

        // Public Member Mutators
        void setGradient(const T gradient);
        void setLookaheadGradient(const T gradient);

        // Public Member Accessors
        const T getWeightedInput(void) const;
        const T getLookaheadWeightedInput(void) const;

        // Public Member Functions
        void saveNeuronConnection(JsonWriter& writer, const bool wroteKeyAlready = false) const;

    };

};

#endif // THESEUS88_NEURONCONNECTION_HPP
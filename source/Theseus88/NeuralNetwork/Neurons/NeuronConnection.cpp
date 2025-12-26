// source/Theseus88/NeuralNetwork/Neurons/NeuronConnection.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronConnection.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> NeuronConnection<T>::NeuronConnection()
    : m_input(static_cast<T>(0.0)), m_weight(static_cast<T>(0.0)), m_gradient(static_cast<T>(0.0)), m_velocity(static_cast<T>(0.0)), m_lookaheadWeight(static_cast<T>(0.0)), m_lookaheadGradient(static_cast<T>(0.0)) {};

    template <typename T> void NeuronConnection<T>::setGradient(const T gradient) {
        m_gradient = m_weight * gradient; // should this be m_gradient = m_weight * m_input * gradient; instead?
    };
    template <typename T> void NeuronConnection<T>::setLookaheadGradient(const T gradient) {
        m_lookaheadGradient = m_lookaheadWeight * gradient; // should this be m_lookaheadGradient = m_lookaheadWeight * m_input * gradient; instead?
    };

    // Public Member Accessors
    template <typename T> const T NeuronConnection<T>::getWeightedInput() const {
        return m_input * m_weight;
    };
    template <typename T> const T NeuronConnection<T>::getLookaheadWeightedInput() const {
        return m_input * m_lookaheadWeight;
    };

    // Public Member Functions
    template <typename T> void NeuronConnection<T>::saveNeuronConnection(JsonWriter& writer, const bool wroteKeyAlready) const {
        writer.writeObjectStart(!wroteKeyAlready);
        //writer.writeNumber("Connection Input", m_input);
        writer.writeNumber("Connection Weight", m_weight);
        //writer.writeNumber("Connection Gradient", m_gradient);
        writer.writeNumber("Connection Velocity", m_velocity);
        //writer.writeNumber("Connection Lookahead Weight", m_lookaheadWeight);
        //writer.writeNumber("Connection Lookahead Gradient", m_lookaheadGradient);
        writer.writeObjectEnd();
    };

    // Explicit Template Instantiations
    template class NeuronConnection<float>;
    template class NeuronConnection<double>;
    template class NeuronConnection<long double>;

};
// source/Theseus88/NeuralNetwork/Neurons/NeuronConnection.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronConnection.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> NeuronConnection<T>::NeuronConnection()
    : m_input(static_cast<T>(0.0)), m_weight(static_cast<T>(0.0)), m_gradient(static_cast<T>(0.0)), m_velocity(static_cast<T>(0.0)), m_moment1(static_cast<T>(0.0)), m_moment2(static_cast<T>(0.0)) {};

    // Public Member Accessors
    template <typename T> const T NeuronConnection<T>::getWeightedInput() const {
        return m_input * m_weight;
    };

    // Public Member Functions
    template <typename T> void NeuronConnection<T>::saveNeuronConnection(JsonWriter& writer, const bool wroteKeyAlready) const {
        writer.writeObjectStart(!wroteKeyAlready);
        //writer.writeNumber("Connection Input", m_input);
        writer.writeNumber("Connection Weight", m_weight);
        writer.writeNumber("Connection Gradient", m_gradient);
        writer.writeNumber("Connection Velocity", m_velocity);
        writer.writeNumber("Connection Moment 1", m_moment1);
        writer.writeNumber("Connection Moment 2", m_moment2);
        writer.writeObjectEnd();
    };

    // Explicit Template Instantiations
    template class NeuronConnection<float>;
    template class NeuronConnection<double>;
    template class NeuronConnection<long double>;

};
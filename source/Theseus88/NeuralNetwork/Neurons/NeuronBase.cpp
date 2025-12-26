// source/Theseus88/NeuralNetwork/Neurons/NeuronBase.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronBase<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Base Error: ") + errorMessage + "\n");
    };

    // Protected Member Functions
    template <typename T> void NeuronBase<T>::updateNeuronConnections() {
        m_neuronConnections.clear();
        if (m_neuronConnections.capacity() != m_connectionCount) m_neuronConnections.reserve(m_connectionCount);
        for (std::size_t i = 0; i < m_connectionCount; i++) {
            m_neuronConnections.emplace_back();
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::NeuronBase(const NeuronType neuronType)
    : M_NEURONDATATYPE(dataTypeToString(T())), M_NEURONTYPE(neuronType), m_connectionCount(0), m_isFinalized(false) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::~NeuronBase() {};

    // Public Member Function Mutators
    template <typename T> void NeuronBase<T>::setRandomizeFunction(const typename RandomizeFunctions<T>::Method randomizeMethod) {
        m_randomizeFunction = RandomizeFunctions<T>::getRandomizeFunction(randomizeMethod);
    };
    template <typename T> void NeuronBase<T>::setActivationFunction(const typename ActivationFunctions<T>::Method activationMethod) {
        m_activationFunction = ActivationFunctions<T>::getActivationFunction(activationMethod);
    };
    template <typename T> void NeuronBase<T>::setDerivativeFunction(const typename ActivationFunctions<T>::Method derivativeMethod) {
        m_derivativeFunction = ActivationFunctions<T>::getActivationFunction(derivativeMethod);
    };
    template <typename T> void NeuronBase<T>::setErrorFunction(const typename ErrorFunctions<T>::Method errorMethod) {
        m_errorFunction = ErrorFunctions<T>::getErrorFunction(errorMethod);
    };
    template <typename T> void NeuronBase<T>::setOptimizerFunction(const typename OptimizerFunctions<T>::Method optimizerMethod) {
        m_optimizerFunction = OptimizerFunctions<T>::getOptimizerFunction(optimizerMethod);
    };

    // Public Member Mutators
    template <typename T> void NeuronBase<T>::setConnectionCount(const size_t connectionCount) {
        if (connectionCount == m_connectionCount) return;
        if (connectionCount <= 0) throwError("Connection count must be greater than 0.");
        m_isFinalized = false;
        m_connectionCount = connectionCount;
    };

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronBase<T>::saveLayerNeuron(JsonWriter& writer) const {
        writer.writeObjectStart();
        writer.writeString("Neuron Data Type", M_NEURONDATATYPE);
        writer.writeString("Neuron Type", neuronTypeToString(M_NEURONTYPE));
        writer.writeNumber("Neuron Connection Count", m_connectionCount);
        writer.writeArrayStart("Neuron Connections");
        for (auto& connection : m_neuronConnections) {
            writer.writeObjectStart();
            writer.writeNumber("Connection Weight", connection.m_weight);
            writer.writeNumber("Connection Gradient", connection.m_gradient);
            writer.writeNumber("Connection Velocity", connection.m_velocity);
            writer.writeNumber("Connection Lookahead Weight", connection.m_lookaheadWeight);
            writer.writeNumber("Connection Lookahead Gradient", connection.m_lookaheadGradient);
            writer.writeObjectEnd();
        };
        writer.writeArrayEnd();
        writer.writeObjectStart("Neuron Bias Connection");
        writer.writeNumber("Connection Weight", m_biasConnection.m_weight);
        writer.writeNumber("Connection Gradient", m_biasConnection.m_gradient);
        writer.writeNumber("Connection Velocity", m_biasConnection.m_velocity);
        writer.writeNumber("Connection Lookahead Weight", m_biasConnection.m_lookaheadWeight);
        writer.writeNumber("Connection Lookahead Gradient", m_biasConnection.m_lookaheadGradient);
        writer.writeObjectEnd();
    };

    // ADD COMMENT HERE LATER
    template class NeuronBase<float>;
    template class NeuronBase<double>;
    template class NeuronBase<long double>;

};
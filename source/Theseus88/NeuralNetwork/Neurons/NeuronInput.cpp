// source/Theseus88/NeuralNetwork/Neurons/NeuronInput.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronInput.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronInput<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Input Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronInput<T>::NeuronInput()
    : NeuronBase<T>(NeuronType::Input) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronInput<T>::~NeuronInput() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronInput<T>::finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParameterOne, const T randomizeParameterTwo) { // Still working on code here...
        NeuronBase<T>::m_connectionCount = 1;
        NeuronBase<T>::updateNeuronConnections();
        for (auto& connection : NeuronBase<T>::m_neuronConnections) connection.m_weight = static_cast<T>(1);
        NeuronBase<T>::m_biasConnection.m_input = static_cast<T>(0);
        NeuronBase<T>::m_biasConnection.m_weight = static_cast<T>(0);
        NeuronBase<T>::m_isFinalized = true;
    };
    template <typename T> void NeuronInput<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        writer.writeObjectEnd();
    };
    template <typename T> const T NeuronInput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        // Optimization: Bypass connection loop and weighted sum for simple pass-through.
        // Note: This assumes the neuron maps to the first input (index 0) based on current connection count of 1.
        if (inputVector.empty()) return static_cast<T>(0);
        
        // TODO: Fix logic. Currently this forces all Input Neurons to read index 0. 
        // Ideally, this neuron should know which index 'i' it is responsible for.
        NeuronBase<T>::m_output = inputVector[0];
        return NeuronBase<T>::m_output;

        /* Original Logic (Redundant if optimization is active)
        std::size_t limit = std::min(inputVector.size(), NeuronBase<T>::m_neuronConnections.size());
        for (std::size_t i = 0; i < limit; i++) NeuronBase<T>::m_neuronConnections[i].m_input = inputVector[i];
        NeuronBase<T>::calculateWeightedSum();
        NeuronBase<T>::m_output = NeuronBase<T>::m_weightedSum;
        return NeuronBase<T>::m_output;
        */
    };
    template <typename T> const std::vector<T>& NeuronInput<T>::propagateBackward(const T targetOutputValue) { // Still working on code here
        return NeuronBase<T>::m_errorVector;
    };

    // ADD COMMENT HERE LATER
    template class NeuronInput<float>;
    template class NeuronInput<double>;
    template class NeuronInput<long double>;

};
// source/Theseus88/NeuralNetwork/Neurons/NeuronFeedforward.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronFeedforward.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronFeedforward<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Feedforward Error: ") + errorMessage + "\n");
    };

    // Private Member Functions

    // ADD COMMENT HERE LATER
    template <typename T> NeuronFeedforward<T>::NeuronFeedforward()
    : NeuronBase<T>(NeuronType::Feedforward) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronFeedforward<T>::~NeuronFeedforward() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronFeedforward<T>::finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParameterOne, const T randomizeParameterTwo) { // Still working on code here...
        NeuronBase<T>::m_connectionCount = inputVectorSize;
        NeuronBase<T>::updateNeuronConnections();
        NeuronBase<T>::m_biasConnection.m_input = static_cast<T>(1);
        NeuronBase<T>::m_randomizeFunction(NeuronBase<T>::m_neuronConnections, NeuronBase<T>::m_biasConnection, randomizeParameterOne, randomizeParameterTwo);
        NeuronBase<T>::m_isFinalized = true;
    };
    template <typename T> void NeuronFeedforward<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        //writer.writeNumber("Weighted Sum", m_weightedSum);
        writer.writeObjectEnd();
    };
    template <typename T> const T NeuronFeedforward<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        for (std::size_t i = 0; i < inputVector.size(); i++) NeuronBase<T>::m_neuronConnections[i].m_input = inputVector[i];
        NeuronBase<T>::calculateWeightedSum();
        NeuronBase<T>::calculateOutput();
        return NeuronBase<T>::m_output;
    };
    template <typename T> const std::vector<T>& NeuronFeedforward<T>::propagateBackward(const T targetOutputValue) { // Still working on code here

    };

    // ADD COMMENT HERE LATER
    template class NeuronFeedforward<float>;
    template class NeuronFeedforward<double>;
    template class NeuronFeedforward<long double>;

};
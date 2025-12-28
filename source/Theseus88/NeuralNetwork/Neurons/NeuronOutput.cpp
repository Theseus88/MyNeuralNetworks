// source/Theseus88/NeuralNetwork/Neurons/NeuronOutput.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronOutput.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronOutput<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Output Error: ") + errorMessage + "\n");
    };

    // Private Member Functions

    // ADD COMMENT HERE LATER
    template <typename T> NeuronOutput<T>::NeuronOutput()
    : NeuronBase<T>(NeuronType::Output) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronOutput<T>::~NeuronOutput() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronOutput<T>::finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParameterOne, const T randomizeParameterTwo) { // Still working on code here...
        NeuronBase<T>::m_connectionCount = inputVectorSize;
        NeuronBase<T>::updateNeuronConnections();
        NeuronBase<T>::m_biasConnection.m_input = static_cast<T>(1);
        NeuronBase<T>::m_randomizeFunction(NeuronBase<T>::m_neuronConnections, NeuronBase<T>::m_biasConnection, randomizeParameterOne, randomizeParameterTwo);
        NeuronBase<T>::m_isFinalized = true;
    };
    template <typename T> void NeuronOutput<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        //writer.writeNumber("Weighted Sum", m_weightedSum);
        writer.writeObjectEnd();
    };
    template <typename T> const T NeuronOutput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        for (std::size_t i = 0; i < inputVector.size(); i++) NeuronBase<T>::m_neuronConnections[i].m_input = inputVector[i];
        NeuronBase<T>::calculateWeightedSum();
        NeuronBase<T>::calculateOutput();
        return NeuronBase<T>::m_output;
    };

    // ADD COMMENT HERE LATER
    template class NeuronOutput<float>;
    template class NeuronOutput<double>;
    template class NeuronOutput<long double>;

};
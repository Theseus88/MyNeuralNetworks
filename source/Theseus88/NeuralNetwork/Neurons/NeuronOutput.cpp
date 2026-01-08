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
    template <typename T> NeuronOutput<T>::NeuronOutput(const std::size_t uniqueNeuronId)
    : NeuronBase<T>(NeuronType::Output, uniqueNeuronId) {};

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
    template <typename T> const std::vector<T>& NeuronOutput<T>::propagateBackward(const T targetOutputValue) {
        T errorDerivative = NeuronBase<T>::m_errorFunction(*this, NeuronBase<T>::m_output, targetOutputValue);
        T activationDerivative = NeuronBase<T>::m_derivativeFunction(NeuronBase<T>::m_weightedSum);
        T delta = errorDerivative * activationDerivative;

        if (NeuronBase<T>::m_errorVector.size() != NeuronBase<T>::m_neuronConnections.size()) NeuronBase<T>::m_errorVector.resize(NeuronBase<T>::m_neuronConnections.size());

        for (std::size_t i = 0; i < NeuronBase<T>::m_neuronConnections.size(); i++) {
            // Calculate gradient for the weight: dE/dW = delta * Input
            NeuronBase<T>::m_neuronConnections[i].m_gradient = delta * NeuronBase<T>::m_neuronConnections[i].m_input;
            // Calculate error to propagate to the previous layer: dE/dInput = delta * Weight
            NeuronBase<T>::m_errorVector[i] = delta * NeuronBase<T>::m_neuronConnections[i].m_weight;
        };

        NeuronBase<T>::m_biasConnection.m_gradient = delta * NeuronBase<T>::m_biasConnection.m_input;

        // Update weights using the optimizer
        NeuronBase<T>::m_optimizerFunction(*this);

        return NeuronBase<T>::m_errorVector;
    };

    // ADD COMMENT HERE LATER
    template class NeuronOutput<float>;
    template class NeuronOutput<double>;
    template class NeuronOutput<long double>;

};
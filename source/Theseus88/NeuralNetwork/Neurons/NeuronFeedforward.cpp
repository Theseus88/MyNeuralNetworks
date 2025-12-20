// source/Theseus88/NeuralNetwork/Neurons/NeuronFeedforward.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronFeedforward.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronFeedforward<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Feedforward Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronFeedforward<T>::NeuronFeedforward()
    : NeuronBase<T>(NeuronType::Feedforward) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronFeedforward<T>::~NeuronFeedforward() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronFeedforward<T>::finalizeLayerNeuron(const size_t inputVectorSize) { // Still working on code here...
        NeuronBase<T>::m_connectionCount = inputVectorSize;
        NeuronBase<T>::updateNeuronConnections();
    };
    template <typename T> void NeuronFeedforward<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        writer.writeObjectEnd();
    };
    /*template <typename T> const T NeuronInput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...

    };*/

    // ADD COMMENT HERE LATER
    template class NeuronFeedforward<float>;
    template class NeuronFeedforward<double>;
    template class NeuronFeedforward<long double>;

};
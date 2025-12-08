// source/Theseus88/NeuralNetwork/Neurons/NeuronOutput.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronOutput.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronOutput<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Output Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronOutput<T>::NeuronOutput()
    : NeuronBase<T>(NeuronType::Output) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronOutput<T>::~NeuronOutput() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronOutput<T>::finalizeLayerNeuron() { // Still working on code here...

    };
    template <typename T> void NeuronOutput<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        writer.writeObjectEnd();
    };
    /*template <typename T> const T NeuronInput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...

    };*/

    // ADD COMMENT HERE LATER
    template class NeuronOutput<float>;
    template class NeuronOutput<double>;
    template class NeuronOutput<long double>;

};
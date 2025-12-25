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
    : NeuronBase<T>(NeuronType::Input), m_index(0) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronInput<T>::~NeuronInput() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronInput<T>::finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParamterOne, const T randomizeParamterTwo) { // Still working on code here...
        NeuronBase<T>::m_connectionCount = 1;
        NeuronBase<T>::updateNeuronConnections(randomizeParamterOne, randomizeParamterTwo);
    };
    template <typename T> void NeuronInput<T>::saveLayerNeuron(JsonWriter& writer) const { // Still working on code here...
        NeuronBase<T>::saveLayerNeuron(writer);
        writer.writeObjectEnd();
    };
    /*template <typename T> const T NeuronInput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...

    };*/

    // ADD COMMENT HERE LATER
    template class NeuronInput<float>;
    template class NeuronInput<double>;
    template class NeuronInput<long double>;

};
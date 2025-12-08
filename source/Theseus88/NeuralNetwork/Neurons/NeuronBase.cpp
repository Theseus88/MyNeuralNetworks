// source/Theseus88/NeuralNetwork/Neurons/NeuronBase.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronBase<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Base Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::NeuronBase(const NeuronType neuronType)
    : M_NEURONDATATYPE(dataTypeToString(T())), M_NEURONTYPE(neuronType) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::~NeuronBase() {};

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronBase<T>::saveLayerNeuron(JsonWriter& writer) const {
        writer.writeObjectStart();
        writer.writeString("Neuron Data Type", M_NEURONDATATYPE);
        writer.writeString("Neuron Type", neuronTypeToString(M_NEURONTYPE));
    };

    // ADD COMMENT HERE LATER
    template class NeuronBase<float>;
    template class NeuronBase<double>;
    template class NeuronBase<long double>;

};
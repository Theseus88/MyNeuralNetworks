// source/Theseus88/NeuralNetwork/Factories/FactoryNeuron.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Factories/FactoryNeuron.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> template <typename... Args> std::unique_ptr<NeuronBase<T>> FactoryNeuron<T>::createNeuron(const NeuronType neuronType, Args&&... args) {
        switch (neuronType) {
            case NeuronType::Input:
                return std::make_unique<NeuronInput<T>>(std::forward<Args>(args)...);
            case NeuronType::Output:
                return std::make_unique<NeuronOutput<T>>(std::forward<Args>(args)...);
            case NeuronType::Feedforward:
                return std::make_unique<NeuronFeedforward<T>>(std::forward<Args>(args)...);
            default:
                throw std::invalid_argument("Neuron Factory Error: Unknown neuron type.");
        };
    };

    // Explicit Template Instantiations
    template class FactoryNeuron<float>;
    template class FactoryNeuron<double>;
    template class FactoryNeuron<long double>;

    template std::unique_ptr<NeuronBase<float>> FactoryNeuron<float>::createNeuron(const NeuronType neuronType);
    template std::unique_ptr<NeuronBase<double>> FactoryNeuron<double>::createNeuron(const NeuronType neuronType);
    template std::unique_ptr<NeuronBase<long double>> FactoryNeuron<long double>::createNeuron(const NeuronType neuronType);

};
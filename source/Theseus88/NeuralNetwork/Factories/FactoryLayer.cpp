// source/Theseus88/NeuralNetwork/Factories/FactoryLayer.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Factories/FactoryLayer.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> template <LayerType LType, typename... Args> std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer(Args&&... args) {
        if constexpr (LType == LayerType::Input) {
            return std::make_unique<LayerInput<T>>(std::forward<Args>(args)...);
        } else if constexpr (LType == LayerType::Output) {
            return std::make_unique<LayerOutput<T>>(std::forward<Args>(args)...);
        } else if constexpr (LType == LayerType::Dense) {
            return std::make_unique<LayerDense<T>>(std::forward<Args>(args)...);
        };
        throw std::invalid_argument("LayerFactory Error: Unknown layer type.");
    };

    // Explicit Template Instantiations
    template class FactoryLayer<float>;
    template class FactoryLayer<double>;
    template class FactoryLayer<long double>;

    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(int& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(int&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(int& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(int&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(int& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(int&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);

    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(int& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(int&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(int& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(int&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(int& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(int&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);

    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(int& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(int&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<float>> FactoryLayer<float>::createLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(int& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(int&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<double>> FactoryLayer<double>::createLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(int& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(int&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(size_t& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(size_t&& neuronCount);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template std::unique_ptr<LayerBase<long double>> FactoryLayer<long double>::createLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);

};
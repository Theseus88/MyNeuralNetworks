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

    #define INSTANTIATE_CREATE_LAYER(T, LType) \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(int&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(const int&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(int&&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(int&, NeuronType&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(const int&, const NeuronType&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(int&&, NeuronType&&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(size_t&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(const size_t&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(size_t&&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(size_t&, NeuronType&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(const size_t&, const NeuronType&); \
        template std::unique_ptr<LayerBase<T>> FactoryLayer<T>::createLayer<LType>(size_t&&, NeuronType&&)

    #define INSTANTIATE_ALL_LAYERS(T) \
        INSTANTIATE_CREATE_LAYER(T, LayerType::Input); \
        INSTANTIATE_CREATE_LAYER(T, LayerType::Output); \
        INSTANTIATE_CREATE_LAYER(T, LayerType::Dense)

    INSTANTIATE_ALL_LAYERS(float);
    INSTANTIATE_ALL_LAYERS(double);
    INSTANTIATE_ALL_LAYERS(long double);

};
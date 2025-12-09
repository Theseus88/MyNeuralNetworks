// source/Theseus88/NeuralNetwork/Functions/ActivationFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/ActivationFunctions.hpp"

namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<const T(const T)> ActivationFunctions<T>::getActivationFunction(const Method& method) {
        switch (method) {
            case Method::Sigmoid: return sigmoid;
            case Method::SigmoidDerivative: return sigmoidDerivative;
            case Method::Relu: return relu;
            case Method::ReluDerivative: return reluDerivative;
            case Method::Tanh: return tanh;
            case Method::TanhDerivative: return tanhDerivative;
            case Method::Linear: return linear;
            case Method::LinearDerivative: return linearDerivative;
            default: throw std::runtime_error("Activation Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> const T ActivationFunctions<T>::sigmoid(const T x) {
        return static_cast<T>(1.0) / (static_cast<T>(1.0) + std::exp(-x));
    };
    template <typename T> const T ActivationFunctions<T>::sigmoidDerivative(const T x) {
        return sigmoid(x) * (static_cast<T>(1.0) - sigmoid(x));
    };
    template <typename T> const T ActivationFunctions<T>::relu(const T x) {
        return std::max(static_cast<T>(0.0), x);
    };
    template <typename T> const T ActivationFunctions<T>::reluDerivative(const T x) {
        return (x > 0) ? static_cast<T>(1.0) : static_cast<T>(0.0);
    };
    template <typename T> const T ActivationFunctions<T>::tanh(const T x) {
        return std::tanh(x);
    };
    template <typename T> const T ActivationFunctions<T>::tanhDerivative(const T x) {
        return static_cast<T>(1.0) - std::pow(std::tanh(x), 2);
    };
    template <typename T> const T ActivationFunctions<T>::linear(const T x) {
        return x;
    };
    template <typename T> const T ActivationFunctions<T>::linearDerivative(const T x) {
        return static_cast<T>(1.0);
    };

    // Explicit Template Instantiations
    template class ActivationFunctions<float>;
    template class ActivationFunctions<double>;
    template class ActivationFunctions<long double>;

};
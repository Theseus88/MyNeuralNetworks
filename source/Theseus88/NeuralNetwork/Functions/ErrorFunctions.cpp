// source/Theseus88/NeuralNetwork/Functions/ErrorFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/ErrorFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<const T(NeuronBase<T>&, const T, const T)> ErrorFunctions<T>::getErrorFunction(const ErrorMethod method) {
        switch (method) {
            case ErrorMethod::None: return none;
            case ErrorMethod::MeanSquaredError: return meanSquaredError;
            case ErrorMethod::MeanAbsoluteError: return meanAbsoluteError;
            case ErrorMethod::SquaredError: return squaredError;
            case ErrorMethod::BinaryCrossEntropy: return binaryCrossEntropy;
            case ErrorMethod::HingeLoss: return hingeLoss;
            case ErrorMethod::FocalLoss: return focalLoss;
            default: throw std::runtime_error("Error Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> const T ErrorFunctions<T>::none(NeuronBase<T>& neuron, const T predicted, const T target) {
        throw std::runtime_error("Error Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
        return static_cast<T>(0.0);
    };
    template <typename T> const T ErrorFunctions<T>::meanSquaredError(NeuronBase<T>& neuron, const T predicted, const T target) {
        return predicted - target;
    };
    template <typename T> const T ErrorFunctions<T>::meanAbsoluteError(NeuronBase<T>& neuron, const T predicted, const T target) {
        return (predicted > target) ? static_cast<T>(1.0) : (predicted < target) ? static_cast<T>(-1.0) : static_cast<T>(0.0);
    };
    template <typename T> const T ErrorFunctions<T>::squaredError(NeuronBase<T>& neuron, const T predicted, const T target) {
        return 2 * (predicted - target);
    };
    template <typename T> const T ErrorFunctions<T>::binaryCrossEntropy(NeuronBase<T>& neuron, const T predicted, const T target) {
        const T epsilon = static_cast<T>(1e-8);
        return -(target / (predicted + epsilon)) + ((static_cast<T>(1.0) - target) / (static_cast<T>(1.0) - predicted + epsilon));
    };
    template <typename T> const T ErrorFunctions<T>::hingeLoss(NeuronBase<T>& neuron, const T predicted, const T target) {
        return (1 - target * predicted < 0) ? static_cast<T>(0.0) : -target;
    };
    template <typename T> const T ErrorFunctions<T>::focalLoss(NeuronBase<T>& neuron, const T predicted, const T target) {
        const T epsilon = static_cast<T>(1e-8);
        const T alpha = static_cast<T>(0.25);
        const T gamma = static_cast<T>(2.0);

        const T p = std::max(epsilon, std::min(predicted, static_cast<T>(1.0) - epsilon));
        const T one_minus_p = static_cast<T>(1.0) - p;

        if (target > static_cast<T>(0.5)) {
            // y = 1
            return alpha * std::pow(one_minus_p, gamma - static_cast<T>(1.0)) * ((gamma * std::log(p)) - (one_minus_p / p));
        } else {
            // y = 0
            return (static_cast<T>(1.0) - alpha) * std::pow(p, gamma - static_cast<T>(1.0)) * ((p / one_minus_p) - (gamma * std::log(one_minus_p)));
        };
    };

    // Explicit Template Instantiations
    template class ErrorFunctions<float>;
    template class ErrorFunctions<double>;
    template class ErrorFunctions<long double>;

};
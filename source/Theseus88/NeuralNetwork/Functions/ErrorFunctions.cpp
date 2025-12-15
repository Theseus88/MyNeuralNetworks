// source/Theseus88/NeuralNetwork/Functions/ErrorFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/ErrorFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<const T(NeuronBase<T>&, const T, const T)> ErrorFunctions<T>::getErrorFunction(const Method method) {
        switch (method) {
            case Method::None: return none;
            case Method::MeanSquaredError: return meanSquaredError;
            case Method::MeanAbsoluteError: return meanAbsoluteError;
            case Method::SquaredError: return squaredError;
            case Method::BinaryCrossEntropy: return binaryCrossEntropy;
            case Method::HingeLoss: return hingeLoss;
            case Method::FocalLoss: return focalLoss;
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
        //const T& epsilon = neuron.getEpsilon();
        //return -(target / (predicted + epsilon)) + ((1 - target) / (1 - predicted + epsilon));
    };
    template <typename T> const T ErrorFunctions<T>::hingeLoss(NeuronBase<T>& neuron, const T predicted, const T target) {
        return (1 - target * predicted < 0) ? static_cast<T>(0.0) : -target;
    };
    template <typename T> const T ErrorFunctions<T>::focalLoss(NeuronBase<T>& neuron, const T predicted, const T target) {
        //const T& epsilon = neuron.getEpsilon();
        //const T& alpha = neuron.getAlpha();
        //const T& gamma = neuron.getGamma();

        //const T pt = (target == 1) ? predicted : (1 - predicted);
        //const T modulating_factor = std::pow((1 - pt), gamma);

        //if (target == 1) {
        //    return -alpha * modulating_factor * (std::log(predicted + epsilon) + (gamma * (1 - pt) / (predicted + epsilon)));
        //} else {
        //    return (1 - alpha) * modulating_factor * (-std::log(1 - predicted + epsilon) - (gamma * pt / (1 - predicted + epsilon)));
        //};
    };

    // Explicit Template Instantiations
    template class ErrorFunctions<float>;
    template class ErrorFunctions<double>;
    template class ErrorFunctions<long double>;

};
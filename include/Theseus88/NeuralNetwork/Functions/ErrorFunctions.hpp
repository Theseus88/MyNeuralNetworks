// include/Theseus88/NeuralNetwork/Functions/ErrorFunctions.hpp
#ifndef THESEUS88_ERRORFUNCTIONS_HPP
#define THESEUS88_ERRORFUNCTIONS_HPP

#include "../NeuralNetworkCore.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class ErrorFunctions {
    public:
        // ADD COMMENT HERE LATER
        enum class Method { None, MeanSquaredError, MeanAbsoluteError, SquaredError, BinaryCrossEntropy, HingeLoss, FocalLoss };
        static constexpr const char* errorMethodToString(Method type) {
            switch (type) {
                case Method::None: return "None";
                case Method::MeanSquaredError: return "Mean Squared Error";
                case Method::MeanAbsoluteError: return "Mean Absolute Error";
                case Method::SquaredError: return "Squared Error";
                case Method::BinaryCrossEntropy: return "Binary Cross Entropy";
                case Method::HingeLoss: return "Hinge Loss";
                case Method::FocalLoss: return "Focal Loss";
                default: return "Unknown";
            };
        };

        /*// ADD COMMENT HERE LATER
        static std::function<const T(NeuralNetworkNeuron<T>&, const T, const T)> getErrorFunction(const Method method);

        // ADD COMMENT HERE LATER
        static const T meanSquaredError(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);
        static const T meanAbsoluteError(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);
        static const T squaredError(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);
        static const T binaryCrossEntropy(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);
        static const T hingeLoss(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);
        static const T focalLoss(NeuralNetworkNeuron<T>& neuron, const T predicted, const T target);*/

    };

};

#endif // THESEUS88_ERRORFUNCTIONS_HPP
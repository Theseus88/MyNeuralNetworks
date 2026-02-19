// include/Theseus88/NeuralNetwork/NeuralNetworkCore.hpp
#ifndef THESEUS88_NEURALNETWORKCORE_HPP
#define THESEUS88_NEURALNETWORKCORE_HPP

// ADD COMMENT HERE LATER
#include <algorithm>    // std::min, std::max, std::transform, std::fill
#include <execution>    // std::execution::par, std::execution::par_unseq
#include <filesystem>   // std::filesystem
#include <fstream>      // std::ofstream
#include <functional>   // std::function
#include <cmath>        // std::pow, std::exp, std::tanh, std::log, std::sqrt
#include <cstddef>      // std::size_t
#include <memory>       // std::unique_ptr, std::make_unique
#include <random>       // std::random_device, std::mt19937, std::uniform_real_distribution
#include <ranges>       // std::views::reverse
#include <stdexcept>    // std::runtime_error
#include <string>       // std::string
#include <type_traits>  // std::is_same_v
#include <utility>      // std::move, std::forward
#include <vector>       // std::vector

// ADD COMMENT HERE LATER
#include "../JsonUtilities/JsonUtilities.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    constexpr const char* dataTypeToString(float) { return "float"; };
    constexpr const char* dataTypeToString(double) { return "double"; };
    constexpr const char* dataTypeToString(long double) { return "long double"; };

    // ADD COMMENT HERE LATER
    enum class NeuronType : int { Input, Output, Feedforward };
    constexpr const char* neuronTypeToString(NeuronType type) {
        switch (type) {
            case NeuronType::Input: return "Input";
            case NeuronType::Output: return "Output";
            case NeuronType::Feedforward: return "Feedforward";
            default: return "Unknown";
        };
    };
    inline NeuronType stringToNeuronType(const std::string& str) {
        if (str == "Input") return NeuronType::Input;
        if (str == "Output") return NeuronType::Output;
        if (str == "Feedforward") return NeuronType::Feedforward;
        throw std::runtime_error("Unknown NeuronType: " + str);
    };

    // ADD COMMENT HERE LATER
    enum class LayerType : int { Input, Output, Dense };
    constexpr const char* layerTypeToString(LayerType type) {
        switch (type) {
            case LayerType::Input: return "Input";
            case LayerType::Output: return "Output";
            case LayerType::Dense: return "Dense";
            default: return "Unknown";
        };
    };
    inline LayerType stringToLayerType(const std::string& str) {
        if (str == "Input") return LayerType::Input;
        if (str == "Output") return LayerType::Output;
        if (str == "Dense") return LayerType::Dense;
        throw std::runtime_error("Unknown LayerType: " + str);
    };

    // Global Method Enums
    enum class RandomizeMethod { None, Uniform, Normal };
    inline RandomizeMethod stringToRandomizeMethod(const std::string& str) {
        if (str == "None") return RandomizeMethod::None;
        if (str == "Uniform") return RandomizeMethod::Uniform;
        if (str == "Normal") return RandomizeMethod::Normal;
        throw std::runtime_error("Unknown RandomizeMethod: " + str);
    };

    enum class ActivationMethod { None, Sigmoid, SigmoidDerivative, Relu, ReluDerivative, Tanh, TanhDerivative, Linear, LinearDerivative };
    inline ActivationMethod stringToActivationMethod(const std::string& str) {
        if (str == "None") return ActivationMethod::None;
        if (str == "Sigmoid") return ActivationMethod::Sigmoid;
        if (str == "Sigmoid Derivative") return ActivationMethod::SigmoidDerivative;
        if (str == "Relu") return ActivationMethod::Relu;
        if (str == "Relu Derivative") return ActivationMethod::ReluDerivative;
        if (str == "Tanh") return ActivationMethod::Tanh;
        if (str == "Tanh Derivative") return ActivationMethod::TanhDerivative;
        if (str == "Linear") return ActivationMethod::Linear;
        if (str == "Linear Derivative") return ActivationMethod::LinearDerivative;
        throw std::runtime_error("Unknown ActivationMethod: " + str);
    };

    enum class ErrorMethod { None, MeanSquaredError, MeanAbsoluteError, SquaredError, BinaryCrossEntropy, HingeLoss, FocalLoss };
    inline ErrorMethod stringToErrorMethod(const std::string& str) {
        if (str == "None") return ErrorMethod::None;
        if (str == "Mean Squared Error") return ErrorMethod::MeanSquaredError;
        if (str == "Mean Absolute Error") return ErrorMethod::MeanAbsoluteError;
        if (str == "Squared Error") return ErrorMethod::SquaredError;
        if (str == "Binary Cross Entropy") return ErrorMethod::BinaryCrossEntropy;
        if (str == "Hinge Loss") return ErrorMethod::HingeLoss;
        if (str == "Focal Loss") return ErrorMethod::FocalLoss;
        throw std::runtime_error("Unknown ErrorMethod: " + str);
    };

    enum class OptimizerMethod { None, StochasticGradientDescent, StochasticGradientDescentWithClassicalMomentum, StochasticGradientDescentWithNesterovMomentum, AdaptiveGradient, RootMeanSquaredPropagation, AdaptiveMomentEstimation };
    inline OptimizerMethod stringToOptimizerMethod(const std::string& str) {
        if (str == "None") return OptimizerMethod::None;
        if (str == "Stochastic Gradient Descent") return OptimizerMethod::StochasticGradientDescent;
        if (str == "Stochastic Gradient Descent With Classical Momentum") return OptimizerMethod::StochasticGradientDescentWithClassicalMomentum;
        if (str == "Stochastic Gradient Descent With Nesterov Momentum") return OptimizerMethod::StochasticGradientDescentWithNesterovMomentum;
        if (str == "Adaptive Gradient") return OptimizerMethod::AdaptiveGradient;
        if (str == "Root Mean Squared Propagation") return OptimizerMethod::RootMeanSquaredPropagation;
        if (str == "Adaptive Moment Estimation") return OptimizerMethod::AdaptiveMomentEstimation;
        throw std::runtime_error("Unknown OptimizerMethod: " + str);
    };

    // Forward Declarations
    template <typename T> class NeuronConnection;
    template <typename T> class NeuronBase;
    template <typename T> class NeuronInput;
    template <typename T> class NeuronOutput;
    template <typename T> class NeuronFeedforward;
    template <typename T> class FactoryNeuron;
    template <typename T> class LayerBase;
    template <typename T> class LayerInput;
    template <typename T> class LayerOutput;
    template <typename T> class LayerDense;
    template <typename T> class FactoryLayer;
    template <typename T> class NeuralNetwork;

};



#endif // THESEUS88_NEURALNETWORKCORE_HPP
// include/Theseus88/NeuralNetwork/Functions/OptimizerFunctions.hpp
#ifndef THESEUS88_OPTIMIZERFUNCTIONS_HPP
#define THESEUS88_OPTIMIZERFUNCTIONS_HPP

#include "../NeuralNetworkCore.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class OptimizerFunctions {
    public:
        // ADD COMMENT HERE LATER
        enum class Method { None, StochasticGradientDescent, StochasticGradientDescentWithClassicalMomentum, StochasticGradientDescentWithNesterovMomentum, AdaptiveGradient, RootMeanSquaredPropagation, AdaptiveMomentEstimation };
        static constexpr const char* optimizerMethodToString(Method type) {
            switch (type) {
                case Method::None: return "None";
                case Method::StochasticGradientDescent: return "Stochastic Gradient Descent";
                case Method::StochasticGradientDescentWithClassicalMomentum: return "Stochastic Gradient Descent with Classical Momentum";
                case Method::StochasticGradientDescentWithNesterovMomentum: return "Stochastic Gradient Descent with Nesterov Momentum";
                case Method::AdaptiveGradient: return "Adaptive Gradient";
                case Method::RootMeanSquaredPropagation: return "Root Mean Squared Propagation";
                case Method::AdaptiveMomentEstimation: return "Adaptive Moment Estimation";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<void(NeuronBase<T>&)> getOptimizerFunction(const Method method);

        // ADD COMMENT HERE LATER
        static void none(NeuronBase<T>& neuron);
        static void stochasticGradientDescent(NeuronBase<T>& neuron);
        static void stochasticGradientDescentWithClassicalMomentum(NeuronBase<T>& neuron);
        static void stochasticGradientDescentWithNesterovMomentum(NeuronBase<T>& neuron);
        static void adaptiveGradient(NeuronBase<T>& neuron);
        static void rootMeanSquaredPropagation(NeuronBase<T>& neuron);
        static void adaptiveMomentEstimation(NeuronBase<T>& neuron);

    };

};

#endif // THESEUS88_OPTIMIZERFUNCTIONS_HPP
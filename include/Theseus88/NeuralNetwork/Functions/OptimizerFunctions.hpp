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
        //enum class Method { None, StochasticGradientDescent, StochasticGradientDescentWithClassicalMomentum, StochasticGradientDescentWithNesterovMomentum, AdaptiveGradient, RootMeanSquaredPropagation, AdaptiveMomentEstimation };
        static constexpr const char* optimizerMethodToString(OptimizerMethod type) {
            switch (type) {
                case OptimizerMethod::None: return "None";
                case OptimizerMethod::StochasticGradientDescent: return "Stochastic Gradient Descent";
                case OptimizerMethod::StochasticGradientDescentWithClassicalMomentum: return "Stochastic Gradient Descent with Classical Momentum";
                case OptimizerMethod::StochasticGradientDescentWithNesterovMomentum: return "Stochastic Gradient Descent with Nesterov Momentum";
                case OptimizerMethod::AdaptiveGradient: return "Adaptive Gradient";
                case OptimizerMethod::RootMeanSquaredPropagation: return "Root Mean Squared Propagation";
                case OptimizerMethod::AdaptiveMomentEstimation: return "Adaptive Moment Estimation";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<void(NeuronBase<T>&)> getOptimizerFunction(const OptimizerMethod method);

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
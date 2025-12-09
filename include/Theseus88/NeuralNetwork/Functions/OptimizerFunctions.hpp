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
        enum class Method { StochasticGradientDescent, StochasticGradientDescentWithClassicalMomentum, StochasticGradientDescentWithNesterovMomentum, AdaptiveGradient, RootMeanSquaredPropagation, AdaptiveMomentEstimation };

        /*// ADD COMMENT HERE LATER
        static std::function<void(NeuralNetworkNeuron<T>&)> getOptimizerFunction(const Method method);

        // ADD COMMENT HERE LATER
        static void stochasticGradientDescent(NeuralNetworkNeuron<T>& neuron);
        static void stochasticGradientDescentWithClassicalMomentum(NeuralNetworkNeuron<T>& neuron);
        static void stochasticGradientDescentWithNesterovMomentum(NeuralNetworkNeuron<T>& neuron);
        static void adaptiveGradient(NeuralNetworkNeuron<T>& neuron);
        static void rootMeanSquaredPropagation(NeuralNetworkNeuron<T>& neuron);
        static void adaptiveMomentEstimation(NeuralNetworkNeuron<T>& neuron);*/

    };

};

#endif // THESEUS88_OPTIMIZERFUNCTIONS_HPP
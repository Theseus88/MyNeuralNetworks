// include/Theseus88/NeuralNetwork/Functions/ActivationFunctions.hpp
#ifndef THESEUS88_ACTIVATIONFUNCTIONS_HPP
#define THESEUS88_ACTIVATIONFUNCTIONS_HPP

#include "../NeuralNetworkCore.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class ActivationFunctions {
    public:
        // ADD COMMENT HERE LATER
        enum class Method { Sigmoid, SigmoidDerivative, Relu, ReluDerivative, Tanh, TanhDerivative, Linear, LinearDerivative };

        // ADD COMMENT HERE LATER
        static std::function<const T(const T)> getActivationFunction(const Method& method);

        // ADD COMMENT HERE LATER
        static const T sigmoid(const T x);
        static const T sigmoidDerivative(const T x);
        static const T relu(const T x);
        static const T reluDerivative(const T x);
        static const T tanh(const T x);
        static const T tanhDerivative(const T x);
        static const T linear(const T x);
        static const T linearDerivative(const T x);

    };

};

#endif // THESEUS88_ACTIVATIONFUNCTIONS_HPP
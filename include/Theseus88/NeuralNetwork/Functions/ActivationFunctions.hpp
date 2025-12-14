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
        enum class Method { None, Sigmoid, SigmoidDerivative, Relu, ReluDerivative, Tanh, TanhDerivative, Linear, LinearDerivative };
        static constexpr const char* activationMethodToString(Method type) {
            switch (type) {
                case Method::None: return "None";
                case Method::Sigmoid: return "Sigmoid";
                case Method::Relu: return "Relu";
                case Method::Tanh: return "Tanh";
                case Method::Linear: return "Linear";
                default: return "Unknown";
            };
        };
        static constexpr const char* derivativeMethodToString(Method type) {
            switch (type) {
                case Method::None: return "None";
                case Method::SigmoidDerivative: return "Sigmoid Derivative";
                case Method::ReluDerivative: return "Relu Derivative";
                case Method::TanhDerivative: return "Tanh Derivative";
                case Method::LinearDerivative: return "Linear Derivative";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<const T(const T)> getActivationFunction(const Method& method);

        // ADD COMMENT HERE LATER
        static const T none(const T x);
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
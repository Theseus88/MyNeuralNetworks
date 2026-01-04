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
        //enum class Method { None, Sigmoid, SigmoidDerivative, Relu, ReluDerivative, Tanh, TanhDerivative, Linear, LinearDerivative };
        static constexpr const char* activationMethodToString(ActivationMethod type) {
            switch (type) {
                case ActivationMethod::None: return "None";
                case ActivationMethod::Sigmoid: return "Sigmoid";
                case ActivationMethod::Relu: return "Relu";
                case ActivationMethod::Tanh: return "Tanh";
                case ActivationMethod::Linear: return "Linear";
                default: return "Unknown";
            };
        };
        static constexpr const char* derivativeMethodToString(ActivationMethod type) {
            switch (type) {
                case ActivationMethod::None: return "None";
                case ActivationMethod::SigmoidDerivative: return "Sigmoid Derivative";
                case ActivationMethod::ReluDerivative: return "Relu Derivative";
                case ActivationMethod::TanhDerivative: return "Tanh Derivative";
                case ActivationMethod::LinearDerivative: return "Linear Derivative";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<const T(const T)> getActivationFunction(const ActivationMethod& method);

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
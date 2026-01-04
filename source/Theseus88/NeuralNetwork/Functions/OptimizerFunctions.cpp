// source/Theseus88/NeuralNetwork/Functions/OptimizerFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/OptimizerFunctions.hpp"
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronBase.hpp"


// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<void(NeuronBase<T>&)> OptimizerFunctions<T>::getOptimizerFunction(const OptimizerMethod method) {
        switch (method) {
            case OptimizerMethod::None: return none;
            case OptimizerMethod::StochasticGradientDescent: return stochasticGradientDescent;
            case OptimizerMethod::StochasticGradientDescentWithClassicalMomentum: return stochasticGradientDescentWithClassicalMomentum;
            case OptimizerMethod::StochasticGradientDescentWithNesterovMomentum: return stochasticGradientDescentWithNesterovMomentum;
            case OptimizerMethod::AdaptiveGradient: return adaptiveGradient;
            case OptimizerMethod::RootMeanSquaredPropagation: return rootMeanSquaredPropagation;
            case OptimizerMethod::AdaptiveMomentEstimation: return adaptiveMomentEstimation;
            default: throw std::runtime_error("Optimizer Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> void OptimizerFunctions<T>::none(NeuronBase<T>& neuron) {
        throw std::runtime_error("Optimizer Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
    };
    template <typename T> void OptimizerFunctions<T>::stochasticGradientDescent(NeuronBase<T>& neuron) {
        for (auto& connection : neuron.m_neuronConnections) {
            connection.m_weight -= neuron.m_learningRate * connection.m_gradient;
        };
        neuron.m_biasConnection.m_weight -= neuron.m_learningRate * neuron.m_biasConnection.m_gradient;
    };
    template <typename T> void OptimizerFunctions<T>::stochasticGradientDescentWithClassicalMomentum(NeuronBase<T>& neuron) {
        for (auto& connection : neuron.m_neuronConnections) {
            T velocity = (neuron.m_momentum * connection.m_velocity) - (neuron.m_learningRate * connection.m_gradient);
            connection.m_velocity = velocity;
            connection.m_weight += velocity;
        };
        T biasVelocity = (neuron.m_momentum * neuron.m_biasConnection.m_velocity) - (neuron.m_learningRate * neuron.m_biasConnection.m_gradient);
        neuron.m_biasConnection.m_velocity = biasVelocity;
        neuron.m_biasConnection.m_weight += biasVelocity;
    };
    template <typename T> void OptimizerFunctions<T>::stochasticGradientDescentWithNesterovMomentum(NeuronBase<T>& neuron) {
        for (auto& connection : neuron.m_neuronConnections) {
            T velocity = (neuron.m_momentum * connection.m_velocity) - (neuron.m_learningRate * connection.m_gradient);
            connection.m_velocity = velocity;
            connection.m_weight += (neuron.m_momentum * velocity) - (neuron.m_learningRate * connection.m_gradient);
        };
        T biasVelocity = (neuron.m_momentum * neuron.m_biasConnection.m_velocity) - (neuron.m_learningRate * neuron.m_biasConnection.m_gradient);
        neuron.m_biasConnection.m_velocity = biasVelocity;
        neuron.m_biasConnection.m_weight += (neuron.m_momentum * biasVelocity) - (neuron.m_learningRate * neuron.m_biasConnection.m_gradient);
    };
    template <typename T> void OptimizerFunctions<T>::adaptiveGradient(NeuronBase<T>& neuron) {
        const T epsilon = static_cast<T>(1e-8);
        for (auto& connection : neuron.m_neuronConnections) {
            connection.m_velocity += std::pow(connection.m_gradient, 2);
            connection.m_weight -= (neuron.m_learningRate / (std::sqrt(connection.m_velocity) + epsilon)) * connection.m_gradient;
        };
        neuron.m_biasConnection.m_velocity += std::pow(neuron.m_biasConnection.m_gradient, 2);
        neuron.m_biasConnection.m_weight -= (neuron.m_learningRate / (std::sqrt(neuron.m_biasConnection.m_velocity) + epsilon)) * neuron.m_biasConnection.m_gradient;
    };
    template <typename T> void OptimizerFunctions<T>::rootMeanSquaredPropagation(NeuronBase<T>& neuron) {
        const T epsilon = static_cast<T>(1e-8);
        const T decay = neuron.m_momentum;
        for (auto& connection : neuron.m_neuronConnections) {
            connection.m_velocity = (decay * connection.m_velocity) + ((static_cast<T>(1.0) - decay) * std::pow(connection.m_gradient, 2));
            connection.m_weight -= (neuron.m_learningRate / (std::sqrt(connection.m_velocity) + epsilon)) * connection.m_gradient;
        };
        neuron.m_biasConnection.m_velocity = (decay * neuron.m_biasConnection.m_velocity) + ((static_cast<T>(1.0) - decay) * std::pow(neuron.m_biasConnection.m_gradient, 2));
        neuron.m_biasConnection.m_weight -= (neuron.m_learningRate / (std::sqrt(neuron.m_biasConnection.m_velocity) + epsilon)) * neuron.m_biasConnection.m_gradient;
    };
    template <typename T> void OptimizerFunctions<T>::adaptiveMomentEstimation(NeuronBase<T>& neuron) {
        const T beta1 = neuron.m_momentum;
        const T beta2 = static_cast<T>(0.999);
        const T epsilon = static_cast<T>(1e-8);
        for (auto& connection : neuron.m_neuronConnections) {
            connection.m_moment1 = (beta1 * connection.m_moment1) + ((static_cast<T>(1.0) - beta1) * connection.m_gradient);
            connection.m_moment2 = (beta2 * connection.m_moment2) + ((static_cast<T>(1.0) - beta2) * std::pow(connection.m_gradient, 2));
            connection.m_weight -= (neuron.m_learningRate * connection.m_moment1) / (std::sqrt(connection.m_moment2) + epsilon);
        };
        neuron.m_biasConnection.m_moment1 = (beta1 * neuron.m_biasConnection.m_moment1) + ((static_cast<T>(1.0) - beta1) * neuron.m_biasConnection.m_gradient);
        neuron.m_biasConnection.m_moment2 = (beta2 * neuron.m_biasConnection.m_moment2) + ((static_cast<T>(1.0) - beta2) * std::pow(neuron.m_biasConnection.m_gradient, 2));
        neuron.m_biasConnection.m_weight -= (neuron.m_learningRate * neuron.m_biasConnection.m_moment1) / (std::sqrt(neuron.m_biasConnection.m_moment2) + epsilon);
    };

    // Explicit Template Instantiations
    template class OptimizerFunctions<float>;
    template class OptimizerFunctions<double>;
    template class OptimizerFunctions<long double>;

};
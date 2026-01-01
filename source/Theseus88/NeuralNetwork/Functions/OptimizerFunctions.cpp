// source/Theseus88/NeuralNetwork/Functions/OptimizerFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/OptimizerFunctions.hpp"
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronBase.hpp"


// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<void(NeuronBase<T>&)> OptimizerFunctions<T>::getOptimizerFunction(const Method method) {
        switch (method) {
            case Method::None: return none;
            case Method::StochasticGradientDescent: return stochasticGradientDescent;
            case Method::StochasticGradientDescentWithClassicalMomentum: return stochasticGradientDescentWithClassicalMomentum;
            case Method::StochasticGradientDescentWithNesterovMomentum: return stochasticGradientDescentWithNesterovMomentum;
            case Method::AdaptiveGradient: return adaptiveGradient;
            case Method::RootMeanSquaredPropagation: return rootMeanSquaredPropagation;
            case Method::AdaptiveMomentEstimation: return adaptiveMomentEstimation;
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
        //const T& gradient = neuron.getGradient();
        //std::vector<NeuralNetworkConnection<T>>& neuronConnections = neuron.getNeuronConnections();
        //NeuralNetworkConnection<T>& biasConnection = neuron.getBiasConnection();
        //const T& learningRate = neuron.getLearningRate();
        //const T& momentum = neuron.getMomentum();

        //for (auto& connection : neuronConnections) {
        //    connection.setWeight(connection.getWeight() + (connection.setVelocity((momentum * connection.getVelocity()) - (learningRate * gradient * connection.getInput()))));
        //};
        //biasConnection.setWeight(biasConnection.getWeight() + (biasConnection.setVelocity((momentum * biasConnection.getVelocity()) - (learningRate * gradient * biasConnection.getInput()))));
    };
    template <typename T> void OptimizerFunctions<T>::stochasticGradientDescentWithNesterovMomentum(NeuronBase<T>& neuron) {
        //std::vector<NeuralNetworkConnection<T>>& neuronConnections = neuron.getNeuronConnections();
        //NeuralNetworkConnection<T>& biasConnection = neuron.getBiasConnection();
        //const T& learningRate = neuron.getLearningRate();
        //const T& momentum = neuron.getMomentum();

        //for (auto& connection : neuronConnections) {
        //    connection.setLookaheadWeight(connection.getWeight() + (momentum * connection.getVelocity()));
        //};
        //biasConnection.setLookaheadWeight(biasConnection.getWeight() + (momentum * biasConnection.getVelocity()));        
        
        //neuron.lookaheadForwardPropagate();
        //neuron.lookaheadBackwardPropagate();
        //const T& lookaheadGradient = neuron.getLookaheadGradient();

        //for (auto& connection : neuronConnections) {
        //    connection.setWeight(connection.getWeight() + (connection.setVelocity((momentum * connection.getVelocity()) - (learningRate * lookaheadGradient * connection.getInput()))));
        //};
        //biasConnection.setWeight(biasConnection.getWeight() + (biasConnection.setVelocity((momentum * biasConnection.getVelocity()) - (learningRate * lookaheadGradient * biasConnection.getInput()))));
    };
    template <typename T> void OptimizerFunctions<T>::adaptiveGradient(NeuronBase<T>& neuron) {
        //const T& gradient = neuron.getGradient();
        //std::vector<NeuralNetworkConnection<T>>& neuronConnections = neuron.getNeuronConnections();
        //NeuralNetworkConnection<T>& biasConnection = neuron.getBiasConnection();
        //const T& learningRate = neuron.getLearningRate();
        //const T& epsilon = neuron.getEpsilon();

        //for (auto& connection : neuronConnections) {
        //    connection._velocity += std::pow(gradient * connection._input, 2);
        //    connection._weight -= ((learningRate / (epsilon + std::sqrt(connection._velocity))) * (gradient * connection._input));
        //};
        //biasConnection._velocity += std::pow(gradient * biasConnection._input, 2);
        //biasConnection._weight -= ((learningRate / (epsilon + std::sqrt(biasConnection._velocity))) * (gradient * biasConnection._input));
    };
    template <typename T> void OptimizerFunctions<T>::rootMeanSquaredPropagation(NeuronBase<T>& neuron) {

    };
    template <typename T> void OptimizerFunctions<T>::adaptiveMomentEstimation(NeuronBase<T>& neuron) {

    };

    // Explicit Template Instantiations
    template class OptimizerFunctions<float>;
    template class OptimizerFunctions<double>;
    template class OptimizerFunctions<long double>;

};
// source/Theseus88/NeuralNetwork/Layers/LayerDense.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Layers/LayerDense.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void LayerDense<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Layer Dense Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerDense<T>::LayerDense(const int neuronCount, const NeuronType neuronType)
    : LayerDense<T>(std::size_t(neuronCount), neuronType) {};
    template <typename T> LayerDense<T>::LayerDense(const size_t neuronCount, const NeuronType neuronType)
    : LayerBase<T>(LayerType::Dense, neuronType, neuronCount), m_randomizeParameterOne(static_cast<T>(-1.0)), m_randomizeParameterTwo(static_cast<T>(1.0)), m_randomizeMethod(RandomizeFunctions<T>::Method::Uniform), m_activationMethod(ActivationFunctions<T>::Method::Sigmoid), m_derivativeMethod(ActivationFunctions<T>::Method::SigmoidDerivative), m_errorMethod(ErrorFunctions<T>::Method::MeanSquaredError), m_optimizerMethod(OptimizerFunctions<T>::Method::StochasticGradientDescent) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerDense<T>::~LayerDense() {};

    // Public Member Mutators
    template <typename T> void LayerDense<T>::setRandomizeParameterOne(const T randomizeParameterOne) {
        m_randomizeParameterOne = randomizeParameterOne;
    };
    template <typename T> void LayerDense<T>::setRandomizeParameterTwo(const T randomizeParameterTwo) {
        m_randomizeParameterTwo = randomizeParameterTwo;
    };
    template <typename T> void LayerDense<T>::setRandomizeMethod(const typename RandomizeFunctions<T>::Method randomizeMethod) {
        m_randomizeMethod = randomizeMethod;
    };
    template <typename T> void LayerDense<T>::setActivationMethod(const typename ActivationFunctions<T>::Method activationMethod) {
        m_activationMethod = activationMethod;
    };
    template <typename T> void LayerDense<T>::setDerivativeMethod(const typename ActivationFunctions<T>::Method derivativeMethod) {
        m_derivativeMethod = derivativeMethod;
    };
    template <typename T> void LayerDense<T>::setErrorMethod(const typename ErrorFunctions<T>::Method errorMethod) {
        m_errorMethod = errorMethod;
    };
    template <typename T> void LayerDense<T>::setOptimizerMethod(const typename OptimizerFunctions<T>::Method optimizerMethod) {
        m_optimizerMethod = optimizerMethod;
    };

    // Public Member Accessors
    template <typename T> const T LayerDense<T>::getRandomizeParameterOne() const {
        return m_randomizeParameterOne;
    };
    template <typename T> const T LayerDense<T>::getRandomizeParameterTwo() const {
        return m_randomizeParameterTwo;
    };
    template <typename T> const typename RandomizeFunctions<T>::Method LayerDense<T>::getRandomizeMethod() const {
        return m_randomizeMethod;
    };
    template <typename T> const typename ActivationFunctions<T>::Method LayerDense<T>::getActivationMethod() const {
        return m_activationMethod;
    };
    template <typename T> const typename ActivationFunctions<T>::Method LayerDense<T>::getDerivativeMethod() const {
        return m_derivativeMethod;
    };
    template <typename T> const typename ErrorFunctions<T>::Method LayerDense<T>::getErrorMethod() const {
        return m_errorMethod;
    };
    template <typename T> const typename OptimizerFunctions<T>::Method LayerDense<T>::getOptimizerMethod() const {
        return m_optimizerMethod;
    };

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerDense<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        LayerBase<T>::m_inputVectorSize = inputVectorSize;
        LayerBase<T>::updateLayerNeurons();
        LayerBase<T>::m_outputVector.clear();
        LayerBase<T>::m_outputVector.resize(LayerBase<T>::m_neuronCount);
        for (auto& neuron : LayerBase<T>::m_layerNeurons) neuron->finalizeLayerNeuron();
        LayerBase<T>::m_isFinalized = true;
        return LayerBase<T>::m_outputVector.size();
    };
    template <typename T> void LayerDense<T>::saveNetworkLayer(JsonWriter& writer, const bool includeNeurons) const { // Still working on code here...
        LayerBase<T>::saveNetworkLayer(writer, false);
        writer.writeNumber("Layer Neuron Randomize Parameter One", m_randomizeParameterOne);
        writer.writeNumber("Layer Neuron Randomize Parameter Two", m_randomizeParameterTwo);
        if (includeNeurons) {
            writer.writeNumber("Layer Neuron Count", LayerBase<T>::m_neuronCount);
            writer.writeArrayStart("Layer Neurons");
            for (const auto& neuronPtr : LayerBase<T>::m_layerNeurons) neuronPtr->saveLayerNeuron(writer);
            writer.writeArrayEnd();
        };
        writer.writeObjectEnd();
    };
    template <typename T> const std::vector<T>& LayerDense<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        if (!LayerBase<T>::m_isFinalized) throwError("The network layer is not finalized.");
        if (inputVector.size() != LayerBase<T>::m_inputVectorSize) throwError("The input vector's size does not match the expected vector size.");
        LayerBase<T>::m_inputVectorPtr = &inputVector;
        return LayerBase<T>::m_outputVector;
    };

    // ADD COMMENT HERE LATER
    template class LayerDense<float>;
    template class LayerDense<double>;
    template class LayerDense<long double>;

};
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
    : LayerBase<T>(LayerType::Dense, neuronType, neuronCount) {
        LayerBase<T>::setRandomizeParameterOne(static_cast<T>(-1.0));
        LayerBase<T>::setRandomizeParameterTwo(static_cast<T>(1.0));
        LayerBase<T>::setRandomizeMethod(RandomizeFunctions<T>::Method::Uniform);
        LayerBase<T>::setActivationMethod(ActivationFunctions<T>::Method::Sigmoid);
        LayerBase<T>::setDerivativeMethod(ActivationFunctions<T>::Method::SigmoidDerivative);
        LayerBase<T>::setErrorMethod(ErrorFunctions<T>::Method::MeanSquaredError);
        LayerBase<T>::setOptimizerMethod(OptimizerFunctions<T>::Method::StochasticGradientDescent);
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerDense<T>::~LayerDense() {};

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerDense<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        LayerBase<T>::m_inputVectorSize = inputVectorSize;
        LayerBase<T>::updateLayerNeurons();
        LayerBase<T>::m_outputVector.clear();
        LayerBase<T>::m_outputVector.resize(LayerBase<T>::m_neuronCount);
        for (auto& neuron : LayerBase<T>::m_layerNeurons) neuron->finalizeLayerNeuron(LayerBase<T>::m_inputVectorSize);
        LayerBase<T>::m_isFinalized = true;
        return LayerBase<T>::m_outputVector.size();
    };
    template <typename T> void LayerDense<T>::saveNetworkLayer(JsonWriter& writer) const { // Still working on code here...
        LayerBase<T>::saveNetworkLayer(writer);
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
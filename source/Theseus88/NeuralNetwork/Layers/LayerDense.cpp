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
        LayerBase<T>::setOptimizerMethod(OptimizerFunctions<T>::Method::StochasticGradientDescent);
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerDense<T>::~LayerDense() {};

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerDense<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        return LayerBase<T>::finalizeNetworkLayer(inputVectorSize);
    };
    template <typename T> void LayerDense<T>::saveNetworkLayer(JsonWriter& writer) const { // Still working on code here...
        LayerBase<T>::saveNetworkLayer(writer);
        writer.writeObjectEnd();
    };
    template <typename T> const std::vector<T>& LayerDense<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        if (!LayerBase<T>::m_isFinalized) throwError("The network layer is not finalized.");
        if (inputVector.size() != LayerBase<T>::m_inputVectorSize) throwError("The input vector's size does not match the expected vector size.");
        LayerBase<T>::m_inputVectorPtr = &inputVector;

        // Still working on code here...
        std::size_t totalConnections = LayerBase<T>::m_layerNeurons.size() * inputVector.size();
        if (totalConnections >= 20000) {
            std::transform(
                //std::execution::par_unseq, // or std::execution::par
                LayerBase<T>::m_layerNeurons.begin(),
                LayerBase<T>::m_layerNeurons.end(),
                LayerBase<T>::m_outputVector.begin(),
                [&inputVector](const std::unique_ptr<NeuronBase<T>>& neuron) {
                    return neuron->propagateForward(inputVector);
                }
            );
        } else {
            std::transform(
                LayerBase<T>::m_layerNeurons.begin(),
                LayerBase<T>::m_layerNeurons.end(),
                LayerBase<T>::m_outputVector.begin(),
                [&inputVector](const std::unique_ptr<NeuronBase<T>>& neuron) {
                    return neuron->propagateForward(inputVector);
                }
            );
        };

        return LayerBase<T>::m_outputVector;
    };
    template <typename T> const std::vector<T>& LayerDense<T>::propagateBackward(const std::vector<T>& targetOutputVector) { // Still working on code here...
        // Note: For Dense layers, 'targetOutputVector' is actually the error vector from the next layer.
        
        if (!LayerBase<T>::m_isFinalized) throwError("The network layer is not finalized.");
        if (targetOutputVector.size() != LayerBase<T>::m_outputVector.size()) throwError("The target output vector size does not match the layer output vector size.");

        if (LayerBase<T>::m_errorVector.size() != LayerBase<T>::m_inputVectorSize) LayerBase<T>::m_errorVector.resize(LayerBase<T>::m_inputVectorSize);
        std::fill(LayerBase<T>::m_errorVector.begin(), LayerBase<T>::m_errorVector.end(), static_cast<T>(0));

        for (size_t i = 0; i < LayerBase<T>::m_layerNeurons.size(); i++) {
            const std::vector<T>& neuronErrors = LayerBase<T>::m_layerNeurons[i]->propagateBackward(targetOutputVector[i]);
            for (size_t j = 0; j < LayerBase<T>::m_inputVectorSize; j++) LayerBase<T>::m_errorVector[j] += neuronErrors[j];
        };

        return LayerBase<T>::m_errorVector;
    };

    // ADD COMMENT HERE LATER
    template class LayerDense<float>;
    template class LayerDense<double>;
    template class LayerDense<long double>;

};
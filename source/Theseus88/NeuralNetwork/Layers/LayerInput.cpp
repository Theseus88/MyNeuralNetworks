// source/Theseus88/NeuralNetwork/Layers/LayerInput.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Layers/LayerInput.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void LayerInput<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Layer Input Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerInput<T>::LayerInput(const int neuronCount, const NeuronType neuronType)
    : LayerInput<T>(std::size_t(neuronCount), neuronType) {};
    template <typename T> LayerInput<T>::LayerInput(const size_t neuronCount, const NeuronType neuronType)
    : LayerBase<T>(LayerType::Input, neuronType, neuronCount) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerInput<T>::~LayerInput() {};

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerInput<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        return LayerBase<T>::finalizeNetworkLayer(inputVectorSize);
    };
    template <typename T> void LayerInput<T>::saveNetworkLayer(JsonWriter& writer) const { // Still working on code here...
        LayerBase<T>::saveNetworkLayer(writer);
        writer.writeObjectEnd();
    };
    template <typename T> const std::vector<T>& LayerInput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        if (!LayerBase<T>::m_isFinalized) throwError("The network layer is not finalized.");
        if (inputVector.size() != LayerBase<T>::m_inputVectorSize) throwError("The input vector's size does not match the expected vector size.");
        LayerBase<T>::m_inputVectorPtr = &inputVector;

        // Still working on code here...
        for (std::size_t i = 0; i < LayerBase<T>::m_outputVector.size(); i++) {
            LayerBase<T>::m_outputVector[i] = LayerBase<T>::m_layerNeurons[i]->propagateForward({inputVector[i]});
        };

        return LayerBase<T>::m_outputVector;
    };

    // ADD COMMENT HERE LATER
    template class LayerInput<float>;
    template class LayerInput<double>;
    template class LayerInput<long double>;

};
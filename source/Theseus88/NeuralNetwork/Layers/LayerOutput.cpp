// source/Theseus88/NeuralNetwork/Layers/LayerOutput.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Layers/LayerOutput.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void LayerOutput<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Layer Output Error: ") + errorMessage + "\n");
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerOutput<T>::LayerOutput(const int neuronCount, const NeuronType neuronType)
    : LayerOutput<T>(std::size_t(neuronCount), neuronType) {};
    template <typename T> LayerOutput<T>::LayerOutput(const size_t neuronCount, const NeuronType neuronType)
    : LayerBase<T>(LayerType::Output, neuronType, neuronCount) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerOutput<T>::~LayerOutput() {};

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerOutput<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        LayerBase<T>::m_inputVectorSize = inputVectorSize;
        LayerBase<T>::updateLayerNeurons();
        LayerBase<T>::m_outputVector.clear();
        LayerBase<T>::m_outputVector.resize(LayerBase<T>::m_neuronCount);
        for (auto& neuron : LayerBase<T>::m_layerNeurons) neuron->finalizeLayerNeuron();
        LayerBase<T>::m_isFinalized = true;
        return LayerBase<T>::m_outputVector.size();
    };
    template <typename T> void LayerOutput<T>::saveNetworkLayer(JsonWriter& writer, const bool includeNeurons) const { // Still working on code here...
        LayerBase<T>::saveNetworkLayer(writer, includeNeurons);
        writer.writeObjectEnd();
    };
    template <typename T> const std::vector<T>& LayerOutput<T>::propagateForward(const std::vector<T>& inputVector) { // Still working on code here...
        if (!LayerBase<T>::m_isFinalized) throwError("The network layer is not finalized.");
        if (inputVector.size() != LayerBase<T>::m_inputVectorSize) throwError("The input vector's size does not match the expected vector size.");
        LayerBase<T>::m_inputVectorPtr = &inputVector;
        return LayerBase<T>::m_outputVector;
    };

    // ADD COMMENT HERE LATER
    template class LayerOutput<float>;
    template class LayerOutput<double>;
    template class LayerOutput<long double>;

};
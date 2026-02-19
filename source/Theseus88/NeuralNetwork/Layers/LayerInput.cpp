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
    template <typename T> LayerInput<T>::LayerInput(const size_t neuronCount, const NeuronType neuronType, const size_t uniqueLayerID)
    : LayerBase<T>(LayerType::Input, neuronType, neuronCount, uniqueLayerID) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerInput<T>::~LayerInput() {};

    // ADD COMMENT HERE LATER
    template <typename T> const std::size_t LayerInput<T>::finalizeNetworkLayer(const std::size_t inputVectorSize) { // Still working on code here...
        return LayerBase<T>::finalizeNetworkLayer(inputVectorSize);
    };
    template <typename T> void LayerInput<T>::loadNetworkLayer(JsonReader& reader) {
        LayerBase<T>::m_layerNeurons.clear();
        LayerBase<T>::m_layerNeurons.reserve(LayerBase<T>::m_neuronCount);
        
        reader.readArrayStart("Layer Neurons");
        for (std::size_t i = 0; i < LayerBase<T>::m_neuronCount; ++i) {
            reader.readObjectStart();
            
            std::string nDataType = reader.readString("Neuron Data Type");
            NeuronType nType = stringToNeuronType(reader.readString("Neuron Type"));
            
            auto neuron = FactoryNeuron<T>::createNeuron(nType);
            neuron->loadLayerNeuron(reader);
            LayerBase<T>::m_layerNeurons.emplace_back(std::move(neuron));
            
            reader.readObjectEnd();
        };
        reader.readArrayEnd();
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
    template <typename T> const std::vector<T>& LayerInput<T>::propagateBackward(const std::vector<T>& targetOutputVector) { // Still working on code here...
        return LayerBase<T>::m_errorVector; // Input layer has no weights to update and no previous layer to propagate to.
    };
    

    // ADD COMMENT HERE LATER
    template class LayerInput<float>;
    template class LayerInput<double>;
    template class LayerInput<long double>;

};
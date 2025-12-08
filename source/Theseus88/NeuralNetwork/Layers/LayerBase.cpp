// source/Theseus88/NeuralNetwork/Layers/LayerBase.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Layers/LayerBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> void LayerBase<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Layer Base Error: ") + errorMessage + "\n");
    };

    // Protected Member Functions
    template <typename T> void LayerBase<T>::updateLayerNeurons() { // Still working on code here...
        m_layerNeurons.clear();
        if (m_layerNeurons.capacity() != m_neuronCount) m_layerNeurons.reserve(m_neuronCount);
        for (std::size_t i = 0; i < m_neuronCount; i++) m_layerNeurons.emplace_back(FactoryNeuron<T>::createNeuron(m_neuronType));
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerBase<T>::LayerBase(const LayerType layerType, const NeuronType neuronType, const size_t neuronCount)
    : M_LAYERDATATYPE(dataTypeToString(T())), M_LAYERTYPE(layerType), m_neuronType(neuronType), m_neuronCount(neuronCount), m_layerNeurons(), m_outputVector(), m_isFinalized(false) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerBase<T>::~LayerBase() {};

    // Public Member Mutators
    template <typename T> void LayerBase<T>::setInputVectorSize(const std::size_t inputVectorSize) {
        if (inputVectorSize == m_inputVectorSize) return;
        m_isFinalized = false;
        m_inputVectorSize = inputVectorSize;
    };
    template <typename T> void LayerBase<T>::setNeuronType(const NeuronType neuronType) {
        if (neuronType == m_neuronType) return;
        m_isFinalized = false;
        m_neuronType = neuronType;
    };
    template <typename T> void LayerBase<T>::setNeuronCount(const std::size_t neuronCount) {
        if (neuronCount == m_neuronCount) return;
        m_isFinalized = false;
        m_neuronCount = neuronCount;
    };
    template <typename T> void LayerBase<T>::setLayerNeuronsCapacity(const std::size_t neuronCapacity) {
        if (neuronCapacity == m_layerNeurons.capacity()) return;
        if (neuronCapacity < m_neuronCount) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (neuronCapacity < m_layerNeurons.size()) throwError("ADD ERROR MESSAGE HERE LATER.");
        m_isFinalized = false;
        m_layerNeurons.reserve(neuronCapacity);
    };

    // Public Member Accessors
    template <typename T> const std::string LayerBase<T>::getLayerDataType() const {
        return M_LAYERDATATYPE;
    };
    template <typename T> const LayerType LayerBase<T>::getLayerType() const {
        return M_LAYERTYPE;
    };
    template <typename T> const std::size_t LayerBase<T>::getInputVectorSize() const {
        return m_inputVectorSize;
    };
    template <typename T> const std::size_t LayerBase<T>::getOutputVectorSize() const {
        return m_outputVector.size();
    };
    template <typename T> const NeuronType LayerBase<T>::getNeuronType() const {
        return m_neuronType;
    };
    template <typename T> const std::size_t LayerBase<T>::getNeuronCount() const {
        return m_neuronCount;
    };
    template <typename T> const std::size_t LayerBase<T>::getLayerNeuronsCapacity() const {
        return m_layerNeurons.capacity();
    };
    template <typename T> const std::size_t LayerBase<T>::getLayerNeuronsSize() const {
        return m_layerNeurons.size();
    };
    template <typename T> const std::vector<T>& LayerBase<T>::getInputVector() const {
        return *m_inputVectorPtr;
    };
    template <typename T> const std::vector<T>& LayerBase<T>::getOutputVector() const {
        return m_outputVector;
    };
    template <typename T> const bool LayerBase<T>::getIsFinalized() const {
        return m_isFinalized;
    };

    // Public Member Functions
    template <typename T> void LayerBase<T>::saveNetworkLayer(JsonWriter& writer) const { // Still working on code here...
        writer.writeObjectStart();
        writer.writeString("Layer Data Type", M_LAYERDATATYPE);
        writer.writeString("Layer Type", layerTypeToString(M_LAYERTYPE));
        writer.writeNumber("Layer Input Vector Size", m_inputVectorSize);
        writer.writeNumber("Layer Output Vector Size", m_outputVector.size());
        writer.writeString("Layer Neuron Type", neuronTypeToString(m_neuronType));
        writer.writeNumber("Layer Neuron Count", m_neuronCount);
        writer.writeArrayStart("Layer Neurons");
        for (const auto& neuronPtr : m_layerNeurons) neuronPtr->saveLayerNeuron(writer);
        writer.writeArrayEnd();
    };

    // ADD COMMENT HERE LATER
    template class LayerBase<float>;
    template class LayerBase<double>;
    template class LayerBase<long double>;

};
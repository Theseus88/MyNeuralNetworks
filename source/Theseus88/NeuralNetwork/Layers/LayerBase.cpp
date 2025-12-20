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
        for (std::size_t i = 0; i < m_neuronCount; i++) {
            m_layerNeurons.emplace_back(FactoryNeuron<T>::createNeuron(m_neuronType));
            m_layerNeurons[i]->setRandomizeFunction(m_randomizeMethod);
            m_layerNeurons[i]->setActivationFunction(m_activationMethod);
            m_layerNeurons[i]->setDerivativeFunction(m_derivativeMethod);
            m_layerNeurons[i]->setErrorFunction(m_errorMethod);
            m_layerNeurons[i]->setOptimizerFunction(m_optimizerMethod);
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> LayerBase<T>::LayerBase(const LayerType layerType, const NeuronType neuronType, const size_t neuronCount)
    : M_LAYERDATATYPE(dataTypeToString(T())), M_LAYERTYPE(layerType), m_neuronType(neuronType), m_randomizeParameterOne(static_cast<T>(0.0)), m_randomizeParameterTwo(static_cast<T>(0.0)), m_randomizeMethod(RandomizeFunctions<T>::Method::None), m_activationMethod(ActivationFunctions<T>::Method::None), m_derivativeMethod(ActivationFunctions<T>::Method::None), m_errorMethod(ErrorFunctions<T>::Method::None), m_optimizerMethod(OptimizerFunctions<T>::Method::None), m_neuronCount(neuronCount), m_layerNeurons(), m_outputVector(), m_isFinalized(false) {};

    // ADD COMMENT HERE LATER
    template <typename T> LayerBase<T>::~LayerBase() {};

    // Public Member Mutators
    template <typename T> void LayerBase<T>::setInputVectorSize(const std::size_t inputVectorSize) {
        if (inputVectorSize == m_inputVectorSize) return;
        if (inputVectorSize <= 0) throwError("Input Vector Size must be greater than 0.");
        m_isFinalized = false;
        m_inputVectorSize = inputVectorSize;
    };
    template <typename T> void LayerBase<T>::setNeuronType(const NeuronType neuronType) {
        if (neuronType == m_neuronType) return;
        m_isFinalized = false;
        m_neuronType = neuronType;
    };
    template <typename T> void LayerBase<T>::setRandomizeParameterOne(const T randomizeParameterOne) {
        m_randomizeParameterOne = randomizeParameterOne;
    };
    template <typename T> void LayerBase<T>::setRandomizeParameterTwo(const T randomizeParameterTwo) {
        m_randomizeParameterTwo = randomizeParameterTwo;
    };
    template <typename T> void LayerBase<T>::setRandomizeMethod(const typename RandomizeFunctions<T>::Method randomizeMethod) {
        m_randomizeMethod = randomizeMethod;
    };
    template <typename T> void LayerBase<T>::setActivationMethod(const typename ActivationFunctions<T>::Method activationMethod) {
        m_activationMethod = activationMethod;
    };
    template <typename T> void LayerBase<T>::setDerivativeMethod(const typename ActivationFunctions<T>::Method derivativeMethod) {
        m_derivativeMethod = derivativeMethod;
    };
    template <typename T> void LayerBase<T>::setErrorMethod(const typename ErrorFunctions<T>::Method errorMethod) {
        m_errorMethod = errorMethod;
    };
    template <typename T> void LayerBase<T>::setOptimizerMethod(const typename OptimizerFunctions<T>::Method optimizerMethod) {
        m_optimizerMethod = optimizerMethod;
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
    template <typename T> const T LayerBase<T>::getRandomizeParameterOne() const {
        return m_randomizeParameterOne;
    };
    template <typename T> const T LayerBase<T>::getRandomizeParameterTwo() const {
        return m_randomizeParameterTwo;
    };
    template <typename T> const typename RandomizeFunctions<T>::Method LayerBase<T>::getRandomizeMethod() const {
        return m_randomizeMethod;
    };
    template <typename T> const typename ActivationFunctions<T>::Method LayerBase<T>::getActivationMethod() const {
        return m_activationMethod;
    };
    template <typename T> const typename ActivationFunctions<T>::Method LayerBase<T>::getDerivativeMethod() const {
        return m_derivativeMethod;
    };
    template <typename T> const typename ErrorFunctions<T>::Method LayerBase<T>::getErrorMethod() const {
        return m_errorMethod;
    };
    template <typename T> const typename OptimizerFunctions<T>::Method LayerBase<T>::getOptimizerMethod() const {
        return m_optimizerMethod;
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
        writer.writeNumber("Layer Neuron Randomize Parameter One", m_randomizeParameterOne);
        writer.writeNumber("Layer Neuron Randomize Parameter Two", m_randomizeParameterTwo);
        writer.writeString("Layer Neuron Randomize Method", RandomizeFunctions<T>::randomizeMethodToString(m_randomizeMethod));
        writer.writeString("Layer Neuron Activation Method", ActivationFunctions<T>::activationMethodToString(m_activationMethod));
        writer.writeString("Layer Neuron Derivative Method", ActivationFunctions<T>::derivativeMethodToString(m_derivativeMethod));
        writer.writeString("Layer Neuron Error Method", ErrorFunctions<T>::errorMethodToString(m_errorMethod));
        writer.writeString("Layer Neuron Optimizer Method", OptimizerFunctions<T>::optimizerMethodToString(m_optimizerMethod));
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
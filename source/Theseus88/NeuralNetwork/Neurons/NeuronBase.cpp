// source/Theseus88/NeuralNetwork/Neurons/NeuronBase.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Neurons/NeuronBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // Protected Static Variables
    template <typename T> std::size_t NeuronBase<T>::s_nextUniqueNeuronId = 0;

    // Private Static Functions
    template <typename T> void NeuronBase<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neuron Base Error: ") + errorMessage + "\n");
    };

    // Private Member Functions

    // Protected Member Functions
    template <typename T> void NeuronBase<T>::updateNeuronConnections() {
        m_neuronConnections.clear();
        if (m_neuronConnections.capacity() != m_connectionCount) m_neuronConnections.reserve(m_connectionCount);
        for (std::size_t i = 0; i < m_connectionCount; i++) {
            m_neuronConnections.emplace_back();
        };
    };
    template <typename T> void NeuronBase<T>::calculateWeightedSum() { // Still working on code here...
        m_weightedSum = static_cast<T>(0);
        for (const auto& connection : m_neuronConnections) m_weightedSum += connection.getWeightedInput();
        m_weightedSum += m_biasConnection.getWeightedInput();
    };
    template <typename T> void NeuronBase<T>::calculateOutput() { // Still working on code here...
        m_output = m_activationFunction(m_weightedSum);
    };

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::NeuronBase(const NeuronType neuronType, const std::size_t uniqueNeuronId)
    : M_NEURONDATATYPE(dataTypeToString(T())), M_NEURONTYPE(neuronType), M_UNIQUENEURONID(uniqueNeuronId), m_connectionCount(0), m_isFinalized(false), m_weightedSum(static_cast<T>(0)), m_output(static_cast<T>(0)), m_learningRate(static_cast<T>(0.01)), m_momentum(static_cast<T>(0.9)) {};

    // ADD COMMENT HERE LATER
    template <typename T> NeuronBase<T>::~NeuronBase() {};

    // Public Static Mutators
    template <typename T> void NeuronBase<T>::setNextUniqueNeuronId(const std::size_t nextUniqueNeuronId) {
        s_nextUniqueNeuronId = nextUniqueNeuronId;
    };

    // Public Member Function Mutators
    template <typename T> void NeuronBase<T>::setRandomizeFunction(const RandomizeMethod randomizeMethod) {
        m_randomizeFunction = RandomizeFunctions<T>::getRandomizeFunction(randomizeMethod);
    };
    template <typename T> void NeuronBase<T>::setActivationFunction(const ActivationMethod activationMethod) {
        m_activationFunction = ActivationFunctions<T>::getActivationFunction(activationMethod);
    };
    template <typename T> void NeuronBase<T>::setDerivativeFunction(const ActivationMethod derivativeMethod) {
        m_derivativeFunction = ActivationFunctions<T>::getActivationFunction(derivativeMethod);
    };
    template <typename T> void NeuronBase<T>::setErrorFunction(const ErrorMethod errorMethod) {
        m_errorFunction = ErrorFunctions<T>::getErrorFunction(errorMethod);
    };
    template <typename T> void NeuronBase<T>::setOptimizerFunction(const OptimizerMethod optimizerMethod) {
        m_optimizerFunction = OptimizerFunctions<T>::getOptimizerFunction(optimizerMethod);
    };

    // Public Member Mutators
    template <typename T> void NeuronBase<T>::setConnectionCount(const size_t connectionCount) {
        if (connectionCount == m_connectionCount) return;
        if (connectionCount <= 0) throwError("Connection count must be greater than 0.");
        m_isFinalized = false;
        m_connectionCount = connectionCount;
    };
    template <typename T> void NeuronBase<T>::setLearningRate(const T learningRate) {
        m_learningRate = learningRate;
    };
    template <typename T> void NeuronBase<T>::setMomentum(const T momentum) {
        m_momentum = momentum;
    };

    // Public Static Accessors
    template <typename T> const std::size_t NeuronBase<T>::getNextUniqueNeuronId() {
        return s_nextUniqueNeuronId;
    };

    // Public Member Accessors
    template <typename T> const std::size_t NeuronBase<T>::getUniqueNeuronId() const {
        return M_UNIQUENEURONID;
    };

    // ADD COMMENT HERE LATER
    template <typename T> void NeuronBase<T>::saveLayerNeuron(JsonWriter& writer) const {
        writer.writeObjectStart();
        writer.writeString("Neuron Data Type", M_NEURONDATATYPE);
        writer.writeString("Neuron Type", neuronTypeToString(M_NEURONTYPE));
        writer.writeNumber("Neuron Unique Id", M_UNIQUENEURONID);
        writer.writeNumber("Neuron Connection Count", m_connectionCount);
        writer.writeArrayStart("Neuron Connections");
        for (auto& connection : m_neuronConnections) {
            connection.saveNeuronConnection(writer);
        };
        writer.writeArrayEnd();
        if (M_NEURONTYPE != NeuronType::Input) {
            writer.writeKeyOnly("Neuron Bias Connection");
            m_biasConnection.saveNeuronConnection(writer, true);
        };
    };

    // ADD COMMENT HERE LATER
    template class NeuronBase<float>;
    template class NeuronBase<double>;
    template class NeuronBase<long double>;

};
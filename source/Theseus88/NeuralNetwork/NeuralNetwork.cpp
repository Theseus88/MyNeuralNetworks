// source/Theseus88/NeuralNetwork/NeuralNetwork.cpp
#include "../../../include/Theseus88/NeuralNetwork/NeuralNetwork.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // Private Static Functions
    template <typename T> void NeuralNetwork<T>::throwError(const char* errorMessage) {
        throw std::runtime_error(std::string("Neural Network Error: ") + errorMessage + "\n");
    };
    template <typename T> void NeuralNetwork<T>::verifyLayerIndex(const std::size_t layerIndex) const {
         if (layerIndex >= m_networkLayers.size()) throwError("Layer index is out of bounds.");
    };
    template <typename T> template <typename U> const std::vector<U>& NeuralNetwork<T>::propagateForwardImpl(const std::vector<U>& inputVector) {
        if constexpr (!std::is_same_v<T, U>) {
            std::string errorMessage = "Data type mismatch. The network expects " + std::string(dataTypeToString(T())) + ".";
            throwError(errorMessage.c_str());
            static const std::vector<U> emptyVector;
            return emptyVector;
        } else {
            if (!m_isFinalized) throwError("The network is not finalized.");
            if (inputVector.size() != m_inputVector.size()) throwError("Input vector size mismatch.");
            m_inputVector = inputVector;
            const std::vector<U>* ioVectorPtr = &m_inputVector;
            for (const auto& layer : m_networkLayers) ioVectorPtr = &layer->propagateForward(*ioVectorPtr);
            m_outputVectorPtr = ioVectorPtr;
            return *m_outputVectorPtr;
        };
    };
    template <typename T> template <typename U> void NeuralNetwork<T>::propagateBackwardImpl(const std::vector<U>& targetOutputVector) {
        if constexpr (!std::is_same_v<T, U>) {
            std::string errorMessage = "Data type mismatch. The network expects " + std::string(dataTypeToString(T())) + ".";
            throwError(errorMessage.c_str());
        } else {
            const std::vector<U>* ioVectorPtr = &targetOutputVector;
            for (auto& layer : m_networkLayers | std::views::reverse) ioVectorPtr = &layer->propagateBackward(*ioVectorPtr);
        };
    };
    template <typename T> void NeuralNetwork<T>::load(JsonReader& reader) {
        // The caller (either the constructor or INeuralNetwork::loadNeuralNetwork)
        // has already read the opening '{' and the "Network Data Type" key-value pair.
        // This function is responsible for reading the remaining network properties.
    
        // Read network-level properties
        setNetworkName(reader.readString("Network Name"));
        bool wasFinalized = reader.readBoolean("Network Is Finalized");
        setLearningRate(reader.readNumber<T>("Network Learning Rate"));
        setMomentum(reader.readNumber<T>("Network Momentum"));
        setInputVectorSize(reader.readNumber<std::size_t>("Network Input Vector Size"));
        setOutputVectorSize(reader.readNumber<std::size_t>("Network Output Vector Size"));
    
        // The layer count is useful for reserving capacity, but not strictly necessary for the loop.
        std::size_t layerCount = reader.readNumber<std::size_t>("Network Layer Count");
        m_networkLayers.clear();
        m_networkLayers.reserve(layerCount);
    
        // Read the array of layers
        reader.readArrayStart("Network Layers");
        for (std::size_t i = 0; i < layerCount; ++i) {
            if (!reader.hasNext()) throwError("Layer count mismatch: Fewer layers in array than specified.");
            reader.readObjectStart(); // Each layer is an object in the array
    
            // Read and verify the data type for this layer
            std::string layerDataType = reader.readString("Layer Data Type");
            if (layerDataType != M_NETWORKDATATYPE) throwError(("Layer Data Type mismatch. Expected " + M_NETWORKDATATYPE + " but found " + layerDataType).c_str());

            // The next field of each layer object must be its type.
            std::string layerTypeStr = reader.readString("Layer Type");
            LayerType layerType = stringToLayerType(layerTypeStr);
    
            // Read properties required for constructor and setup
            std::size_t uniqueId = reader.readNumber<std::size_t>("Layer Unique Id");
            std::size_t inputVectorSize = reader.readNumber<std::size_t>("Layer Input Vector Size");
            reader.readNumber<std::size_t>("Layer Output Vector Size"); // Consume and ignore

            NeuronType neuronType = stringToNeuronType(reader.readString("Layer Neuron Type"));

            T randP1 = reader.readNumber<T>("Layer Neuron Randomize Parameter One");
            T randP2 = reader.readNumber<T>("Layer Neuron Randomize Parameter Two");
            
            RandomizeMethod randMethod = stringToRandomizeMethod(reader.readString("Layer Neuron Randomize Method"));
            ActivationMethod actMethod = stringToActivationMethod(reader.readString("Layer Neuron Activation Method"));
            ActivationMethod derMethod = stringToActivationMethod(reader.readString("Layer Neuron Derivative Method"));
            ErrorMethod errMethod = stringToErrorMethod(reader.readString("Layer Neuron Error Method"));
            OptimizerMethod optMethod = stringToOptimizerMethod(reader.readString("Layer Neuron Optimizer Method"));

            std::size_t neuronCount = reader.readNumber<std::size_t>("Layer Neuron Count");

            // Create the appropriate layer type using the FactoryLayer with specific constructor arguments.
            std::unique_ptr<LayerBase<T>> newLayer;
            switch (layerType) {
                case LayerType::Input:  newLayer = FactoryLayer<T>::template createLayer<LayerType::Input>(neuronCount, neuronType, uniqueId);  break;
                case LayerType::Dense:  newLayer = FactoryLayer<T>::template createLayer<LayerType::Dense>(neuronCount, neuronType, uniqueId);  break;
                case LayerType::Output: newLayer = FactoryLayer<T>::template createLayer<LayerType::Output>(neuronCount, neuronType, uniqueId); break;
                default: throwError("Unknown or unsupported layer type encountered during loading.");
            };
    
            // Apply read properties
            newLayer->setInputVectorSize(inputVectorSize);
            newLayer->setRandomizeParameterOne(randP1);
            newLayer->setRandomizeParameterTwo(randP2);
            newLayer->setRandomizeMethod(randMethod);
            newLayer->setActivationMethod(actMethod);
            newLayer->setDerivativeMethod(derMethod);
            newLayer->setErrorMethod(errMethod);
            newLayer->setOptimizerMethod(optMethod);
            // setNeuronCount is handled by constructor.

            // Load neurons (rest of the object)
            newLayer->loadNetworkLayer(reader);
            m_networkLayers.emplace_back(std::move(newLayer));
    
            reader.readObjectEnd(); // End of the current layer object
        };
        if (reader.hasNext()) throwError("Layer count mismatch: More layers in array than specified.");
        reader.readArrayEnd();
    
        // If the network was saved in a finalized state, re-finalize it after loading.
        if (wasFinalized) finalizeNeuralNetwork();
    };

    // Public Member Constructors
    template <typename T> NeuralNetwork<T>::NeuralNetwork()
    : NeuralNetwork(std::string(""), static_cast<std::size_t>(0), static_cast<std::size_t>(0)) {};
    template <typename T> NeuralNetwork<T>::NeuralNetwork(const std::filesystem::path& path) {
        std::ifstream fileStream(path);
        if (!fileStream.is_open()) throwError(std::string("Failed to open file for loading: " + path.string()).c_str());
        JsonReader reader(fileStream);
        reader.readObjectStart();
        std::string dataType = reader.readString("Network Data Type");
        if (dataType != M_NETWORKDATATYPE) throwError(std::string("Data type mismatch. File contains \"" + dataType + "\", but network is initialized as \"" + M_NETWORKDATATYPE + "\".").c_str());
        load(reader);
        reader.readObjectEnd();
    };
    template <typename T> NeuralNetwork<T>::NeuralNetwork(const char* networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize)
    : NeuralNetwork(std::string(networkName), inputVectorSize, outputVectorSize) {};    
    template <typename T> NeuralNetwork<T>::NeuralNetwork(const std::string& networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize)
    : NeuralNetwork(std::string(networkName), inputVectorSize, outputVectorSize) {};
    template <typename T> NeuralNetwork<T>::NeuralNetwork(std::string&& networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize)
    : M_NETWORKDATATYPE(dataTypeToString(T())), m_networkName(std::move(networkName)), m_learningRate(static_cast<T>(0.01)), m_momentum(static_cast<T>(0.9)), m_outputVectorSize(outputVectorSize), m_networkLayers(), m_outputVectorPtr(nullptr), m_isFinalized(false) {
        // ADD COMMENT HERE LATER
        setInputVectorSize(inputVectorSize);
        setNetworkLayersCapacity(S_DEFAULTLAYERCAPACITY);
        addNetworkLayer<LayerType::Input>(m_inputVector.size());
    };

    // Public Member Destructor
    template <typename T> NeuralNetwork<T>::~NeuralNetwork() {};

    // Public Member Mutators
    template <typename T> void NeuralNetwork<T>::setNetworkName(const char* networkName) {
        setNetworkName(std::string(networkName));
    };
    template <typename T> void NeuralNetwork<T>::setNetworkName(const std::string& networkName) {
        setNetworkName(std::string(networkName));
    };
    template <typename T> void NeuralNetwork<T>::setNetworkName(std::string&& networkName) {
        if (m_networkName == networkName) return;
        m_isFinalized = false;
        m_networkName = std::move(networkName);
    };
    template <typename T> void NeuralNetwork<T>::setInputVectorSize(const std::size_t inputVectorSize) {
        if (inputVectorSize == m_inputVector.size()) return;
        m_isFinalized = false;
        m_inputVector.clear();
        m_inputVector.reserve(inputVectorSize);
        m_inputVector.resize(inputVectorSize);
    };
    template <typename T> void NeuralNetwork<T>::setOutputVectorSize(const std::size_t outputVectorSize) {
        if (outputVectorSize == m_outputVectorSize) return;
        m_isFinalized = false;
        m_outputVectorSize = outputVectorSize;
    };
    template <typename T> void NeuralNetwork<T>::setLearningRate(const double learningRate) {
        m_learningRate = learningRate;
    };
    template <typename T> void NeuralNetwork<T>::setMomentum(const double momentum) {
        m_momentum = momentum;
    };
    template <typename T> void NeuralNetwork<T>::setNetworkLayersCapacity(const std::size_t layerCapacity) {
        if (layerCapacity == m_networkLayers.capacity()) return;
        if (layerCapacity < m_networkLayers.size()) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (layerCapacity < S_MINIMUMLAYERCOUNT) throwError("ADD ERROR MESSAGE HERE LATER.");
        m_isFinalized = false;
        m_networkLayers.reserve(layerCapacity);
    };
    template <typename T> void NeuralNetwork<T>::setRandomizeMethod(const RandomizeMethod randomizeMethod) {    // Still working on code here...
        //for (auto& layer : m_networkLayers) layer->setRandomizeMethod(randomizeMethod);
    };
    template <typename T> void NeuralNetwork<T>::setActivationMethod(const ActivationMethod activationMethod) { // Still working on code here...
        //for (auto& layer : m_networkLayers) layer->setActivationMethod(activationMethod);
    };
    template <typename T> void NeuralNetwork<T>::setDerivativeMethod(const ActivationMethod derivativeMethod) { // Still working on code here...
        //for (auto& layer : m_networkLayers) layer->setDerivativeMethod(derivativeMethod);
    };
    template <typename T> void NeuralNetwork<T>::setErrorMethod(const ErrorMethod errorMethod) {                // Still working on code here...
        //for (auto& layer : m_networkLayers) layer->setErrorMethod(errorMethod);
    };
    template <typename T> void NeuralNetwork<T>::setOptimizerMethod(const OptimizerMethod optimizerMethod) {    // Still working on code here...
        //for (auto& layer : m_networkLayers) layer->setOptimizerMethod(optimizerMethod);
    };

    // Public Member Accessors
    template <typename T> const std::string NeuralNetwork<T>::getNetworkDataType() const {
        return M_NETWORKDATATYPE;
    };
    template <typename T> const std::string NeuralNetwork<T>::getNetworkName() const {
        return m_networkName;
    };
    template <typename T> const std::size_t NeuralNetwork<T>::getInputVectorSize() const {
        return m_inputVector.size();
    };
    template <typename T> const std::size_t NeuralNetwork<T>::getOutputVectorSize() const {
        return m_outputVectorSize;
    };
    template <typename T> const double NeuralNetwork<T>::getLearningRate() const {
        return m_learningRate;
    };
    template <typename T> const double NeuralNetwork<T>::getMomentum() const {
        return m_momentum;
    };
    template <typename T> const std::size_t NeuralNetwork<T>::getNetworkLayersCapacity() const {
        return m_networkLayers.capacity();
    };
    template <typename T> const std::size_t NeuralNetwork<T>::getNetworkLayersSize() const {
        return m_networkLayers.size();
    };
    template <typename T> LayerBase<T>& NeuralNetwork<T>::getNetworkLayer(const int layerIndex) {
        return getNetworkLayer(std::size_t(layerIndex));
    };
    template <typename T> LayerBase<T>& NeuralNetwork<T>::getNetworkLayer(const std::size_t layerIndex) {
        verifyLayerIndex(layerIndex);
        return *m_networkLayers[layerIndex];
    };
    template <typename T> const std::vector<T>& NeuralNetwork<T>::getInputVector() const {
        if (!m_isFinalized) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_inputVector.size() == 0) throwError("ADD ERROR MESSAGE HERE LATER.");
        return m_inputVector;
    };
    template <typename T> const std::vector<T>& NeuralNetwork<T>::getOutputVector() const {
        if (!m_isFinalized) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_outputVectorPtr == nullptr) throwError("ADD ERROR MESSAGE HERE LATER.");
        return *m_outputVectorPtr;
    };
    template <typename T> const bool NeuralNetwork<T>::getIsFinalized() const {
        return m_isFinalized;
    };

    // Public Member Functions
    template <typename T> template <LayerType LType, typename... Args> const std::size_t NeuralNetwork<T>::addNetworkLayer(Args&&... args) {
        m_isFinalized = false;
        const std::size_t newLayerIndex = m_networkLayers.size();
        m_networkLayers.emplace_back(FactoryLayer<T>::template createLayer<LType>(std::forward<Args>(args)...));
        return newLayerIndex;
    };
    template <typename T> template <LayerType LType, typename... Args> void NeuralNetwork<T>::insertNetworkLayer(const std::size_t layerIndex, Args&&... args) {
        m_isFinalized = false;
        if (layerIndex > (m_networkLayers.size() - 1)) {
            m_networkLayers.emplace_back(FactoryLayer<T>::template createLayer<LType>(std::forward<Args>(args)...));
        } else {
            m_networkLayers.insert((m_networkLayers.begin() + layerIndex), FactoryLayer<T>::template createLayer<LType>(std::forward<Args>(args)...));
        };
    };
    template <typename T> void NeuralNetwork<T>::removeNetworkLayer(const size_t layerIndex) {
        verifyLayerIndex(layerIndex);
        if (layerIndex == 0) throwError("ADD ERROR MESSAGE HERE LATER.");
        m_isFinalized = false;
        m_networkLayers.erase(m_networkLayers.begin() + layerIndex);
    };
    template <typename T> void NeuralNetwork<T>::finalizeNeuralNetwork() {
        if (m_isFinalized) return;
        if (m_inputVector.size() == 0) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_outputVectorSize == 0) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_networkLayers[0]->getLayerType() != LayerType::Input) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_networkLayers.back()->getLayerType() != LayerType::Output) addNetworkLayer<LayerType::Output>(m_outputVectorSize);
        if (m_networkLayers.size() < S_MINIMUMLAYERCOUNT) throwError("ADD ERROR MESSAGE HERE LATER.");
        if (m_networkLayers[0]->getLayerNeuronsSize() != m_inputVector.size()) m_networkLayers[0]->setNeuronCount(m_inputVector.size());
        if (m_networkLayers.back()->getLayerNeuronsSize() != m_outputVectorSize) m_networkLayers.back()->setNeuronCount(m_outputVectorSize);
        std::size_t ioVectorSize = m_inputVector.size();
        for (auto& layer : m_networkLayers) {
            ioVectorSize = layer->finalizeNetworkLayer(ioVectorSize);
            layer->setLearningRate(m_learningRate);
            layer->setMomentum(m_momentum);
        };
        m_isFinalized = true;
    };
    template <typename T> const std::vector<float>& NeuralNetwork<T>::propagateForward(const std::vector<float>& inputVector) {
        return propagateForwardImpl(inputVector);
    };
    template <typename T> const std::vector<double>& NeuralNetwork<T>::propagateForward(const std::vector<double>& inputVector) {
        return propagateForwardImpl(inputVector);
    };
    template <typename T> const std::vector<long double>& NeuralNetwork<T>::propagateForward(const std::vector<long double>& inputVector) {
        return propagateForwardImpl(inputVector);
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<float>& targetOutputVector) {
        propagateBackwardImpl(targetOutputVector);
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<double>& targetOutputVector) {
        propagateBackwardImpl(targetOutputVector);
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<long double>& targetOutputVector) {
        propagateBackwardImpl(targetOutputVector);
    };
    template <typename T> void NeuralNetwork<T>::saveNeuralNetwork(const std::filesystem::path& path) {
        //if (!m_isFinalized) throwError("Cannot save the network. It is not finalized.");
        std::ofstream outputFile(path);
        if (!outputFile.is_open()) throwError("Failed to open file for saving.");
        JsonWriter writer(outputFile);
        writer.writeObjectStart();
        writer.writeString("Network Data Type", M_NETWORKDATATYPE);
        writer.writeString("Network Name", m_networkName);
        writer.writeBoolean("Network Is Finalized", m_isFinalized);
        writer.writeNumber("Network Learning Rate", m_learningRate);
        writer.writeNumber("Network Momentum", m_momentum);
        writer.writeNumber("Network Input Vector Size", m_inputVector.size());
        writer.writeNumber("Network Output Vector Size", m_outputVectorSize);
        writer.writeNumber("Network Layer Count", m_networkLayers.size());
        writer.writeArrayStart("Network Layers");
        for (const auto& layerPtr : m_networkLayers) layerPtr->saveNetworkLayer(writer);
        writer.writeArrayEnd();
        writer.writeObjectEnd();
    };

    // Explicit Template Instantiations
    template class NeuralNetwork<float>;
    template class NeuralNetwork<double>;
    template class NeuralNetwork<long double>;

    #define INSTANTIATE_ADD_LAYER(T, LType) \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(int&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(const int&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(int&&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(int&, NeuronType&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(const int&, const NeuronType&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(int&&, NeuronType&&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(const size_t&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&, NeuronType&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(const size_t&, const NeuronType&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&&, NeuronType&&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&, NeuronType&, size_t&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(const size_t&, const NeuronType&, const size_t&); \
        template const std::size_t NeuralNetwork<T>::addNetworkLayer<LType>(size_t&&, NeuronType&&, size_t&&)

    #define INSTANTIATE_INSERT_LAYER(T, LType) \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, int&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, const int&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, int&&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, int&, NeuronType&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, const int&, const NeuronType&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, int&&, NeuronType&&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, const size_t&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&, NeuronType&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, const size_t&, const NeuronType&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&&, NeuronType&&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&, NeuronType&, size_t&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, const size_t&, const NeuronType&, const size_t&); \
        template void NeuralNetwork<T>::insertNetworkLayer<LType>(const std::size_t, size_t&&, NeuronType&&, size_t&&)

    #define INSTANTIATE_ALL_LAYERS(T) \
        INSTANTIATE_ADD_LAYER(T, LayerType::Input); \
        INSTANTIATE_ADD_LAYER(T, LayerType::Output); \
        INSTANTIATE_ADD_LAYER(T, LayerType::Dense); \
        INSTANTIATE_INSERT_LAYER(T, LayerType::Input); \
        INSTANTIATE_INSERT_LAYER(T, LayerType::Output); \
        INSTANTIATE_INSERT_LAYER(T, LayerType::Dense)

    INSTANTIATE_ALL_LAYERS(float);
    INSTANTIATE_ALL_LAYERS(double);
    INSTANTIATE_ALL_LAYERS(long double);

};
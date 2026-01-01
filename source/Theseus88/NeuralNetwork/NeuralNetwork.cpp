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

    // Public Member Constructors
    template <typename T> NeuralNetwork<T>::NeuralNetwork()
    : NeuralNetwork(std::string(""), static_cast<std::size_t>(0), static_cast<std::size_t>(0)) {}; 
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
        for (auto& layer : m_networkLayers) ioVectorSize = layer->finalizeNetworkLayer(ioVectorSize);
        m_isFinalized = true;
    };
    template <typename T> const std::vector<float>& NeuralNetwork<T>::propagateForward(const std::vector<float>& inputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, float>) {
            throwError("Data type mismatch. The network expects float.");
            static const std::vector<float> emptyVector;
            return emptyVector;
        } else {
            if (!m_isFinalized) throwError("The network is not finalized.");
            if (inputVector.size() != m_inputVector.size()) throwError("Input vector size mismatch.");
            m_inputVector = inputVector;
            const std::vector<float>* ioVectorPtr = &m_inputVector;
            for (const auto& layer : m_networkLayers) ioVectorPtr = &layer->propagateForward(*ioVectorPtr);
            m_outputVectorPtr = ioVectorPtr;
            return *m_outputVectorPtr;
        };
    };
    template <typename T> const std::vector<double>& NeuralNetwork<T>::propagateForward(const std::vector<double>& inputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, double>) {
            throwError("Data type mismatch. The network expects double.");
            static const std::vector<double> emptyVector;
            return emptyVector;
        } else {
            if (!m_isFinalized) throwError("The network is not finalized.");
            if (inputVector.size() != m_inputVector.size()) throwError("Input vector size mismatch.");
            m_inputVector = inputVector;
            const std::vector<double>* ioVectorPtr = &m_inputVector;
            for (const auto& layer : m_networkLayers) ioVectorPtr = &layer->propagateForward(*ioVectorPtr);
            m_outputVectorPtr = ioVectorPtr;
            return *m_outputVectorPtr;
        };
    };
    template <typename T> const std::vector<long double>& NeuralNetwork<T>::propagateForward(const std::vector<long double>& inputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, long double>) {
            throwError("Data type mismatch. The network expects long double.");
            static const std::vector<long double> emptyVector;
            return emptyVector;
        } else {
            if (!m_isFinalized) throwError("The network is not finalized.");
            if (inputVector.size() != m_inputVector.size()) throwError("Input vector size mismatch.");
            m_inputVector = inputVector;
            const std::vector<long double>* ioVectorPtr = &m_inputVector;
            for (const auto& layer : m_networkLayers) ioVectorPtr = &layer->propagateForward(*ioVectorPtr);
            m_outputVectorPtr = ioVectorPtr;
            return *m_outputVectorPtr;
        };
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<float>& targetOutputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, float>) {
            throwError("Data type mismatch. The network expects float.");
        } else {
            const std::vector<float>* ioVectorPtr = &targetOutputVector;
            for (auto& layer : m_networkLayers | std::views::reverse) ioVectorPtr = &layer->propagateBackward(*ioVectorPtr);
        };
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<double>& targetOutputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, double>) {
            throwError("Data type mismatch. The network expects double.");
        } else {
            const std::vector<double>* ioVectorPtr = &targetOutputVector;
            for (auto& layer : m_networkLayers | std::views::reverse) ioVectorPtr = &layer->propagateBackward(*ioVectorPtr);
        };
    };
    template <typename T> void NeuralNetwork<T>::propagateBackward(const std::vector<long double>& targetOutputVector) { // Still working on code here...
        if constexpr (!std::is_same_v<T, long double>) {
            throwError("Data type mismatch. The network expects long double.");
        } else {
            const std::vector<long double>* ioVectorPtr = &targetOutputVector;
            for (auto& layer : m_networkLayers | std::views::reverse) ioVectorPtr = &layer->propagateBackward(*ioVectorPtr);
        };
    };
    template <typename T> void NeuralNetwork<T>::saveNeuralNetwork(const std::filesystem::path& path) {
        std::ofstream outputFile(path);
        if (!outputFile.is_open()) throwError("ADD ERROR MESSAGE HERE LATER.");
        JsonWriter writer(outputFile);
        writer.writeObjectStart();
        writer.writeString("Network Data Type", M_NETWORKDATATYPE);
        writer.writeString("Network Name", m_networkName);
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
    template <typename T> void NeuralNetwork<T>::loadNeuralNetwork() {};

    // Explicit Template Instantiations
    template class NeuralNetwork<float>;
    template class NeuralNetwork<double>;
    template class NeuralNetwork<long double>;

    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(int& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(int&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(int& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(int&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(int& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(int&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Input>(size_t&& neuronCount, NeuronType&& neuronType);

    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(int& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(int&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(int& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(int&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(int& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(int&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Output>(size_t&& neuronCount, NeuronType&& neuronType);

    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(int& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(int&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<float>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(int& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(int&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<double>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(int& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(int&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(int& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(int&& neuronCount, NeuronType&& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(size_t& neuronCount, NeuronType& neuronType);
    template const std::size_t NeuralNetwork<long double>::addNetworkLayer<LayerType::Dense>(size_t&& neuronCount, NeuronType&& neuronType);

    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Input>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);

    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Output>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);

    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<float>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, int&& neuronCount, NeuronType&& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t& neuronCount, NeuronType& neuronType);
    template void NeuralNetwork<long double>::insertNetworkLayer<LayerType::Dense>(const std::size_t layerIndex, size_t&& neuronCount, NeuronType&& neuronType);

};
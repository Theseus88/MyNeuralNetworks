// include/Theseus88/NeuralNetwork/NeuralNetwork.hpp
#ifndef THESEUS88_NEURALNETWORK_HPP
#define THESEUS88_NEURALNETWORK_HPP

#include "NeuralNetworkCore.hpp"

#include "Factories/FactoryNeuron.hpp"
#include "Factories/FactoryLayer.hpp"

#include "Functions/RandomizeFunctions.hpp"
#include "Functions/ActivationFunctions.hpp"
#include "Functions/ErrorFunctions.hpp"
#include "Functions/OptimizerFunctions.hpp"

#include "INeuralNetwork.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // Neural Network Class
    template <typename T> class NeuralNetwork : public INeuralNetwork {
    private:
        // Private Static Constants
        static const std::size_t S_MINIMUMLAYERCOUNT = 2;
        static const std::size_t S_DEFAULTLAYERCAPACITY = 10;

        // Private Member Constants
        const std::string M_NETWORKDATATYPE;

        // Private Member Variables
        std::string m_networkName;
        std::size_t m_outputVectorSize;
        double m_learningRate, m_momentum;
        std::vector<std::unique_ptr<LayerBase<T>>> m_networkLayers;
        std::vector<T> m_inputVector;
        const std::vector<T>* m_outputVectorPtr;
        bool m_isFinalized;

        // Private Static Functions
        static void throwError(const char* errorMessage);
        void verifyLayerIndex(const std::size_t layerIndex) const;
        template <typename U> const std::vector<U>& propagateForwardImpl(const std::vector<U>& inputVector);
        template <typename U> void propagateBackwardImpl(const std::vector<U>& targetOutputVector);

    public:
        // Public Member Constructors
        NeuralNetwork();
        NeuralNetwork(const std::filesystem::path& path);
        NeuralNetwork(const char* networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);
        NeuralNetwork(const std::string& networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);
        NeuralNetwork(std::string&& networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);

        // Public Member Destructor
        ~NeuralNetwork();

        // Public Member Mutators
        void setNetworkName(const char* networkName) override;
        void setNetworkName(const std::string& networkName) override;
        void setNetworkName(std::string&& networkName) override;
        void setInputVectorSize(const std::size_t inputVectorSize) override;
        void setOutputVectorSize(const std::size_t outputVectorSize) override;
        void setLearningRate(const double learningRate) override;
        void setMomentum(const double momentum) override;
        void setNetworkLayersCapacity(const std::size_t layerCapacity) override;
        void setRandomizeMethod(const RandomizeMethod randomizeMethod) override;
        void setActivationMethod(const ActivationMethod activationMethod) override;
        void setDerivativeMethod(const ActivationMethod derivativeMethod) override;
        void setErrorMethod(const ErrorMethod errorMethod) override;
        void setOptimizerMethod(const OptimizerMethod optimizerMethod) override;

        // Public Member Accessors
        const std::string getNetworkDataType() const override;
        const std::string getNetworkName() const override;
        const std::size_t getInputVectorSize() const override;
        const std::size_t getOutputVectorSize() const override;
        const double getLearningRate() const override;
        const double getMomentum() const override;
        const std::size_t getNetworkLayersCapacity() const override;
        const std::size_t getNetworkLayersSize() const override;
        LayerBase<T>& getNetworkLayer(const int layerIndex);
        LayerBase<T>& getNetworkLayer(const std::size_t layerIndex);
        const std::vector<T>& getInputVector() const;
        const std::vector<T>& getOutputVector() const;
        const bool getIsFinalized() const override;

        // Public Member Functions
        template <LayerType LType, typename... Args> const std::size_t addNetworkLayer(Args&&... args);
        template <LayerType LType, typename... Args> void insertNetworkLayer(const std::size_t layerIndex, Args&&... args);
        void removeNetworkLayer(const size_t layerIndex) override;
        void finalizeNeuralNetwork() override;
        const std::vector<float>& propagateForward(const std::vector<float>& inputVector) override;
        const std::vector<double>& propagateForward(const std::vector<double>& inputVector) override;
        const std::vector<long double>& propagateForward(const std::vector<long double>& inputVector) override;
        void propagateBackward(const std::vector<float>& targetOutputVector) override;
        void propagateBackward(const std::vector<double>& targetOutputVector) override;
        void propagateBackward(const std::vector<long double>& targetOutputVector) override;
        void saveNeuralNetwork(const std::filesystem::path& path) override;

    };

};

#endif // THESEUS88_NEURALNETWORK_HPP
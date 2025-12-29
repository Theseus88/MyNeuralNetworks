// include/Theseus88/NeuralNetwork/INeuralNetwork.hpp
#ifndef THESEUS88_INEURALNETWORK_HPP
#define THESEUS88_INEURALNETWORK_HPP

#include "NeuralNetworkCore.hpp"

namespace Theseus88 {

    class INeuralNetwork {
    public:
        INeuralNetwork() = default;
        virtual ~INeuralNetwork() = default;

        // ADD COMMENT HERE LATER
        static std::unique_ptr<INeuralNetwork> newNeuralNetwork(const char* dataType, const char* networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);
        static std::unique_ptr<INeuralNetwork> newNeuralNetwork(const std::string& dataType, const std::string& networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);
        static std::unique_ptr<INeuralNetwork> newNeuralNetwork(std::string&& dataType, std::string&& networkName, const std::size_t inputVectorSize = 0, const std::size_t outputVectorSize = 0);
        //static std::unique_ptr<INeuralNetwork> loadNeuralNetwork(const std::filesystem::path& path);

        // Public Pure Virtual Member Mutators
        virtual void setNetworkName(const char* networkName) = 0;
        virtual void setNetworkName(const std::string& networkName) = 0;
        virtual void setNetworkName(std::string&& networkName) = 0;
        virtual void setInputVectorSize(const std::size_t inputVectorSize) = 0;
        virtual void setOutputVectorSize(const std::size_t outputVectorSize) = 0;
        virtual void setLearningRate(const double learningRate) = 0;
        virtual void setMomentum(const double momentum) = 0;
        virtual void setNetworkLayersCapacity(const std::size_t layerCapacity) = 0;

        // Public Pure Virtual Member Accessors
        virtual const std::string getNetworkDataType() const = 0;
        virtual const std::string getNetworkName() const = 0;
        virtual const std::size_t getInputVectorSize() const = 0;
        virtual const std::size_t getOutputVectorSize() const = 0;
        virtual const double getLearningRate() const = 0;
        virtual const double getMomentum() const = 0;
        virtual const std::size_t getNetworkLayersCapacity() const = 0;
        virtual const std::size_t getNetworkLayersSize() const = 0;
        virtual const bool getIsFinalized() const = 0;

        // Public Pure Virtual Member Functions
        virtual void removeNetworkLayer(const size_t layerIndex) = 0;
        virtual void finalizeNeuralNetwork() = 0;
        virtual const std::vector<float>& propagateForward(const std::vector<float>& inputVector) = 0;
        virtual const std::vector<double>& propagateForward(const std::vector<double>& inputVector) = 0;
        virtual const std::vector<long double>& propagateForward(const std::vector<long double>& inputVector) = 0;
        virtual void saveNeuralNetwork(const std::filesystem::path& path) = 0;
        virtual void loadNeuralNetwork() = 0;
    
    };

};

#endif // THESEUS88_INEURALNETWORK_HPP
// source/Theseus88/NeuralNetwork/INeuralNetwork.cpp
#include "../../../include/Theseus88/NeuralNetwork/INeuralNetwork.hpp"
#include "../../../include/Theseus88/JsonUtilities/JsonUtilities.hpp"
#include "../../../include/Theseus88/NeuralNetwork/NeuralNetwork.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    std::unique_ptr<INeuralNetwork> INeuralNetwork::newNeuralNetwork(const char* dataType, const char* networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize) {
        return newNeuralNetwork(std::string(dataType), std::string(networkName), inputVectorSize, outputVectorSize);
    };
    std::unique_ptr<INeuralNetwork> INeuralNetwork::newNeuralNetwork(const std::string& dataType, const std::string& networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize) {
        return newNeuralNetwork(std::string(dataType), std::string(networkName), inputVectorSize, outputVectorSize);
    };
    std::unique_ptr<INeuralNetwork> INeuralNetwork::newNeuralNetwork(std::string&& dataType, std::string&& networkName, const std::size_t inputVectorSize, const std::size_t outputVectorSize) {
        if (dataType == "float") {
            return std::make_unique<NeuralNetwork<float>>(networkName, inputVectorSize, outputVectorSize);
        } else if (dataType == "double") {
            return std::make_unique<NeuralNetwork<double>>(networkName, inputVectorSize, outputVectorSize);
        } else if (dataType == "long double") {
            return std::make_unique<NeuralNetwork<long double>>(networkName, inputVectorSize, outputVectorSize);
        } else {
            throw std::runtime_error("Unsupported data type specified for new network creation: " + dataType);
        };
    };
    std::unique_ptr<INeuralNetwork> INeuralNetwork::loadNeuralNetwork(const std::filesystem::path& path) {
        std::ifstream fileStream(path);
        if (!fileStream.is_open()) throw std::runtime_error("Failed to open file for loading: " + path.string());
    
        JsonReader reader(fileStream);
        std::unique_ptr<INeuralNetwork> network = nullptr;
    
        reader.readObjectStart();
        // The first key-value pair must be the data type for the factory to work.
        std::string dataType = reader.readString("Network Data Type");
    
        if (dataType == "float") {
            network = std::make_unique<NeuralNetwork<float>>();
        } else if (dataType == "double") {
            network = std::make_unique<NeuralNetwork<double>>();
        } else if (dataType == "long double") {
            network = std::make_unique<NeuralNetwork<long double>>();
        } else {
            throw std::runtime_error("Unknown or unsupported data type in network file: " + dataType);
        };
    
        network->load(reader); // Polymorphically call the load function for the created network type.
        //reader.readObjectEnd(); // The factory that opens the object should be the one to close it.
        return network;
    };

};
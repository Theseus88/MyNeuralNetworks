// source/Theseus88/NeuralNetwork/INeuralNetwork.cpp
#include "../../../include/Theseus88/NeuralNetwork/INeuralNetwork.hpp"
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
    /*std::unique_ptr<INeuralNetwork> INeuralNetwork::loadNeuralNetwork(const std::filesystem::path& path) {
        // Still need to finish code here...
    };*/

};
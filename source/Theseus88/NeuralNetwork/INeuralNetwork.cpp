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
    std::unique_ptr<INeuralNetwork> INeuralNetwork::loadNeuralNetwork(const std::filesystem::path& path) {
        std::ifstream inputFile(path);
        if (!inputFile.is_open()) throw std::runtime_error("Failed to open file for loading: " + path.string());

        // Simple scan to find the data type before full parsing
        std::string line;
        std::string dataType;
        while (std::getline(inputFile, line)) {
            if (line.find("Network Data Type") != std::string::npos) {
                if (line.find("float") != std::string::npos) dataType = "float";
                else if (line.find("long double") != std::string::npos) dataType = "long double";
                else if (line.find("double") != std::string::npos) dataType = "double";
                break;
            };
        };
        inputFile.close();

        if (dataType == "float") {
            return std::make_unique<NeuralNetwork<float>>(path);
        } else if (dataType == "double") {
            return std::make_unique<NeuralNetwork<double>>(path);
        } else if (dataType == "long double") {
            return std::make_unique<NeuralNetwork<long double>>(path);
        } else {
            throw std::runtime_error("Unknown or unsupported data type in network file.");
        };
    };

};
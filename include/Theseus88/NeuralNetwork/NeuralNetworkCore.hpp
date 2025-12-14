// include/Theseus88/NeuralNetwork/NeuralNetworkCore.hpp
#ifndef THESEUS88_NEURALNETWORKCORE_HPP
#define THESEUS88_NEURALNETWORKCORE_HPP

// ADD COMMENT HERE LATER
#include <algorithm>    // std::max
#include <filesystem>   // std::filesystem
#include <fstream>      // std::ofstream
#include <functional>   // std::function
#include <cmath>        // std::pow, std::exp, std::tanh, std::log, std::sqrt
#include <cstddef>      // std::size_t
#include <memory>       // std::unique_ptr, std::make_unique
#include <random>       // std::random_device, std::mt19937, std::uniform_real_distribution
#include <stdexcept>    // std::runtime_error
#include <string>       // std::string
#include <utility>      // std::move, std::forward
#include <vector>       // std::vector

// ADD COMMENT HERE LATER
#include "../JsonUtilities/JsonUtilities.hpp"
#include "Functions/RandomizeFunctions.hpp"
#include "Functions/ActivationFunctions.hpp"
#include "Functions/ErrorFunctions.hpp"
#include "Functions/OptimizerFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    constexpr const char* dataTypeToString(float) { return "float"; };
    constexpr const char* dataTypeToString(double) { return "double"; };
    constexpr const char* dataTypeToString(long double) { return "long double"; };

    // ADD COMMENT HERE LATER
    enum class NeuronType : int { Input, Output, Feedforward };
    constexpr const char* neuronTypeToString(NeuronType type) {
        switch (type) {
            case NeuronType::Input: return "Input";
            case NeuronType::Output: return "Output";
            case NeuronType::Feedforward: return "Feedforward";
            default: return "Unknown";
        };
    };
    enum class LayerType : int { Input, Output, Dense };
    constexpr const char* layerTypeToString(LayerType type) {
        switch (type) {
            case LayerType::Input: return "Input";
            case LayerType::Output: return "Output";
            case LayerType::Dense: return "Dense";
            default: return "Unknown";
        };
    };

    // Forward Declarations
    template <typename T> class NeuronBase;
    template <typename T> class NeuronInput;
    template <typename T> class NeuronOutput;
    template <typename T> class NeuronFeedforward;
    template <typename T> class FactoryNeuron;
    template <typename T> class LayerBase;
    template <typename T> class LayerInput;
    template <typename T> class LayerOutput;
    template <typename T> class LayerDense;
    template <typename T> class FactoryLayer;
    template <typename T> class NeuralNetwork;

};

#endif // THESEUS88_NEURALNETWORKCORE_HPP
// source/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> std::function<void(std::vector<NeuronConnection<T>>&, NeuronConnection<T>&, const T, const T)> RandomizeFunctions<T>::getRandomizeFunction(const RandomizeMethod method) {
        switch (method) {
            case RandomizeMethod::None: return none;
            case RandomizeMethod::Uniform: return uniform;
            case RandomizeMethod::Normal: return normal;
            default: throw std::runtime_error("Randomize Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> void RandomizeFunctions<T>::none(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T, const T) {
        throw std::runtime_error("Randomize Functions Error: ADD ERROR MESSAGE HERE LATER.\n");
    };
    template <typename T> void RandomizeFunctions<T>::uniform(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T minVal, const T maxVal) {
        if (minVal >= maxVal) throw std::runtime_error("Randomize Functions Error: Invalid range for uniform randomization.\n");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> distrib(minVal, maxVal);
        for (auto& connection : neuronConnections) connection.m_weight = distrib(gen);
        biasConnection.m_weight = distrib(gen);
    };
    template <typename T> void RandomizeFunctions<T>::normal(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T mean, const T stddev) {
        if (stddev <= static_cast<T>(0.0)) throw std::runtime_error("Randomize Functions Error: Standard deviation must be positive for normal randomization.\n");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<T> distrib(mean, stddev);
        for (auto& connection : neuronConnections) connection.m_weight = distrib(gen);
        biasConnection.m_weight = distrib(gen);
    };

    // Explicit Template Instantiations
    template class RandomizeFunctions<float>;
    template class RandomizeFunctions<double>;
    template class RandomizeFunctions<long double>;

};
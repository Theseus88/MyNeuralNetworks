// source/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.cpp
#include "../../../../include/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.hpp"

namespace Theseus88 {

    /*// ADD COMMENT HERE LATER
    template <typename T> std::function<void(std::vector<NeuralNetworkConnection<T>>&, NeuralNetworkConnection<T>&, const T, const T)> RandomizeFunctions<T>::getRandomizeFunction(const Method method) {
        switch (method) {
            case Method::Uniform: return uniform;
            case Method::Normal: return normal;
            default: throw std::invalid_argument("");
        };
    };

    // ADD COMMENT HERE LATER
    template <typename T> void RandomizeFunctions<T>::uniform(std::vector<NeuralNetworkConnection<T>>& neuronConnections, NeuralNetworkConnection<T>& biasConnection, const T minVal, const T maxVal)
    {
        if (minVal >= maxVal) throw std::invalid_argument("Invalid range for uniform randomization.");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> distrib(minVal, maxVal);
        for (auto& connection : neuronConnections) connection.setWeight(distrib(gen));
        biasConnection.setWeight(distrib(gen));
    };
    template <typename T> void RandomizeFunctions<T>::normal(std::vector<NeuralNetworkConnection<T>>& neuronConnections, NeuralNetworkConnection<T>& biasConnection, const T mean, const T stddev)
    {
        if (stddev <= static_cast<T>(0.0)) throw std::invalid_argument("Standard deviation must be positive for normal randomization.");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<T> distrib(mean, stddev);
        for (auto& connection : neuronConnections) connection.setWeight(distrib(gen));
        biasConnection.setWeight(distrib(gen));
    };*/

    // Explicit Template Instantiations
    template class RandomizeFunctions<float>;
    template class RandomizeFunctions<double>;
    template class RandomizeFunctions<long double>;

};
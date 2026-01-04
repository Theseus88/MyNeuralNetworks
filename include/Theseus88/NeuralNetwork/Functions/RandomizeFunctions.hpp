// include/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.hpp
#ifndef THESEUS88_RANDOMIZEFUNCTIONS_HPP
#define THESEUS88_RANDOMIZEFUNCTIONS_HPP

#include "../NeuralNetworkCore.hpp"
#include "../Neurons/NeuronConnection.hpp" // Full definition needed for NeuronConnection<T>

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class RandomizeFunctions {
    public:
        // ADD COMMENT HERE LATER
        //enum class Method { None, Uniform, Normal };
        static constexpr const char* randomizeMethodToString(RandomizeMethod type) {
            switch (type) {
                case RandomizeMethod::None: return "None";
                case RandomizeMethod::Uniform: return "Uniform";
                case RandomizeMethod::Normal: return "Normal";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<void(std::vector<NeuronConnection<T>>&, NeuronConnection<T>&, const T, const T)> getRandomizeFunction(const RandomizeMethod method);

        // ADD COMMENT HERE LATER
        static void none(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T, const T);
        static void uniform(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T minVal, const T maxVal);
        static void normal(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T mean, const T stddev);

    };

};

#endif // THESEUS88_RANDOMIZEFUNCTIONS_HPP
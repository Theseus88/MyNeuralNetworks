// include/Theseus88/NeuralNetwork/Functions/RandomizeFunctions.hpp
#ifndef THESEUS88_RANDOMIZEFUNCTIONS_HPP
#define THESEUS88_RANDOMIZEFUNCTIONS_HPP

#include "../NeuralNetworkCore.hpp"
#include "../Neurons/NeuronConnection.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class RandomizeFunctions {
    public:
        // ADD COMMENT HERE LATER
        enum class Method { None, Uniform, Normal };
        static constexpr const char* randomizeMethodToString(Method type) {
            switch (type) {
                case Method::None: return "None";
                case Method::Uniform: return "Uniform";
                case Method::Normal: return "Normal";
                default: return "Unknown";
            };
        };

        // ADD COMMENT HERE LATER
        static std::function<void(std::vector<NeuronConnection<T>>&, NeuronConnection<T>&, const T, const T)> getRandomizeFunction(const Method method);

        // ADD COMMENT HERE LATER
        static void none(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T, const T);
        static void uniform(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T minVal, const T maxVal);
        static void normal(std::vector<NeuronConnection<T>>& neuronConnections, NeuronConnection<T>& biasConnection, const T mean, const T stddev);

    };

};

#endif // THESEUS88_RANDOMIZEFUNCTIONS_HPP
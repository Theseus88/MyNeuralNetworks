// include/Theseus88/NeuralNetwork/Factories/FactoryNeuron.hpp
#ifndef THESEUS88_FACTORYNEURON_HPP
#define THESEUS88_FACTORYNEURON_HPP

#include "../NeuralNetworkCore.hpp"
#include "../Neurons/NeuronBase.hpp"
#include "../Neurons/NeuronInput.hpp"
#include "../Neurons/NeuronOutput.hpp"
#include "../Neurons/NeuronFeedforward.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class FactoryNeuron {
    public:
        // ADD COMMENT HERE LATER
        template <typename... Args>
        static std::unique_ptr<NeuronBase<T>> createNeuron(const NeuronType neuronType, Args&&... args);

    };

};

#endif // THESEUS88_FACTORYNEURON_HPP
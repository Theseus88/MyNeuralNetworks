// NeuronInput.hpp
#ifndef THESEUS88_NEURONINPUT_HPP
#define THESEUS88_NEURONINPUT_HPP

#include "../NeuralNetworkCore.hpp"
#include "NeuronBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class NeuronInput : public NeuronBase<T> {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Static Functions
        static void throwError(const char* errorMessage);

        // Private Member Variables
        std::size_t m_index;

    public:
        // Default Constructors
        NeuronInput();

        // Default Destructor
        ~NeuronInput();

        // ADD COMMENT HERE LATER
        void finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParamterOne, const T randomizeParamterTwo) override; // Still working on code here...
        void saveLayerNeuron(JsonWriter& writer) const override; // Still working on code here...
        //const T propagateForward(const std::vector<T>& inputVector) override; // Still working on code here...

    };

};

#endif // THESEUS88_NEURONINPUT_HPP
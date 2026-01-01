// LayerInput.hpp
#ifndef THESEUS88_LAYERINPUT_HPP
#define THESEUS88_LAYERINPUT_HPP

#include "LayerBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class LayerInput : public LayerBase<T> {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Member Functions
        static void throwError(const char* errorMessage);

    public:
        // ADD COMMENT HERE LATER
        LayerInput() = delete;
        LayerInput(const int neuronCount, const NeuronType neuronType = NeuronType::Input);
        LayerInput(const size_t neuronCount, const NeuronType neuronType = NeuronType::Input);

        // ADD COMMENT HERE LATER
        ~LayerInput();

        // Public Member Functions
        const size_t finalizeNetworkLayer(const size_t inputVectorSize) override; // Still working on code here...
        void saveNetworkLayer(JsonWriter& writer) const override; // Still working on code here...
        const std::vector<T>& propagateForward(const std::vector<T>& inputVector) override; // Still working on code here...
        const std::vector<T>& propagateBackward(const std::vector<T>& targetOutputVector) override; // Still working on code here...

    };

};

#endif // THESEUS88_LAYERINPUT_HPP
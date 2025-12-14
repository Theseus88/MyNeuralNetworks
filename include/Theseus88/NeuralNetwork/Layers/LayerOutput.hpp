// LayerOutput.hpp
#ifndef THESEUS88_LAYEROUTPUT_HPP
#define THESEUS88_LAYEROUTPUT_HPP

#include "LayerBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class LayerOutput : public LayerBase<T> {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Member Functions
        static void throwError(const char* errorMessage);

    public:
        // ADD COMMENT HERE LATER
        LayerOutput() = delete;
        LayerOutput(const int neuronCount, const NeuronType neuronType = NeuronType::Output);
        LayerOutput(const size_t neuronCount, const NeuronType neuronType = NeuronType::Output);

        // ADD COMMENT HERE LATER
        ~LayerOutput();

        // Public Member Functions
        const size_t finalizeNetworkLayer(const size_t inputVectorSize) override; // Still working on code here...
        void saveNetworkLayer(JsonWriter& writer) const override; // Still working on code here...
        const std::vector<T>& propagateForward(const std::vector<T>& inputVector) override; // Still working on code here...

    };

};

#endif // THESEUS88_LAYEROUTPUT_HPP
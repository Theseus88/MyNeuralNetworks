// include/Theseus88/NeuralNetwork/Factories/FactoryLayer.hpp
#ifndef THESEUS88_FACTORYLAYER_HPP
#define THESEUS88_FACTORYLAYER_HPP

#include "../NeuralNetworkCore.hpp"
#include "../Layers/LayerBase.hpp"
#include "../Layers/LayerInput.hpp"
#include "../Layers/LayerOutput.hpp"
#include "../Layers/LayerDense.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class FactoryLayer {
    public:
        // ADD COMMENT HERE LATER
        template <LayerType LType, typename... Args>
        static std::unique_ptr<LayerBase<T>> createLayer(Args&&... args);

    };

};

#endif // THESEUS88_FACTORYLAYER_HPP
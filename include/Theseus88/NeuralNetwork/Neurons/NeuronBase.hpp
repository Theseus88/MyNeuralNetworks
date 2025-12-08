// NeuronBase.hpp
#ifndef THESEUS88_NEURONBASE_HPP
#define THESEUS88_NEURONBASE_HPP

#include "../NeuralNetworkCore.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class NeuronBase {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Static Functions
        static void throwError(const char* errorMessage);

    protected:
        // Protected Member Constants
        const std::string M_NEURONDATATYPE;
        const NeuronType M_NEURONTYPE;

    public:
        // Public Member Constructors
        NeuronBase(const NeuronType neuronType);

        // Public Member Destructor
        ~NeuronBase();

        // Public Member Functions
        //virtual std::unique_ptr<NeuronBase<T>> cloneLayerNeuron() const = 0; // Still working on code here...
        virtual void finalizeLayerNeuron() = 0; // Still working on code here...
        virtual void saveLayerNeuron(JsonWriter& writer) const; // Still working on code here...
        //virtual const T propagateForward(const std::vector<T>& inputVector) = 0; // Still working on code here...

    };

};

#endif // THESEUS88_NEURONBASE_HPP
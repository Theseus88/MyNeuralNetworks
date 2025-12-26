// NeuronBase.hpp
#ifndef THESEUS88_NEURONBASE_HPP
#define THESEUS88_NEURONBASE_HPP

#include "../NeuralNetworkCore.hpp"
#include "NeuronConnection.hpp"

#include "../Functions/RandomizeFunctions.hpp"
#include "../Functions/ActivationFunctions.hpp"
#include "../Functions/ErrorFunctions.hpp"
#include "../Functions/OptimizerFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class NeuronBase {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Static Functions
        static void throwError(const char* errorMessage);

        // Private Member Variables

        // Private Member Functions

    protected:
        // Protected Member Constants
        const std::string M_NEURONDATATYPE;
        const NeuronType M_NEURONTYPE;

        // Protected Member Function Variables
        std::function<void(std::vector<NeuronConnection<T>>&, NeuronConnection<T>&, const T, const T)> m_randomizeFunction;
        std::function<const T(const T)> m_activationFunction;
        std::function<const T(const T)> m_derivativeFunction;
        std::function<const T(NeuronBase<T>&, const T, const T)> m_errorFunction;
        std::function<void(NeuronBase<T>&)> m_optimizerFunction;

        // Protected Member Variables
        std::size_t m_connectionCount;
        std::vector<NeuronConnection<T>> m_neuronConnections;
        NeuronConnection<T> m_biasConnection;
        bool m_isFinalized;
        T m_weightedSum, m_output;

        // Protected Member Functions
        void updateNeuronConnections();
        void calculateWeightedSum(); // Still working on code here...
        void calculateOutput(); // Still working on code here...

    public:
        // Public Member Constructors
        NeuronBase(const NeuronType neuronType);

        // Public Member Destructor
        ~NeuronBase();

        // Public Member Function Mutators
        void setRandomizeFunction(const typename RandomizeFunctions<T>::Method randomizeMethod);
        void setActivationFunction(const typename ActivationFunctions<T>::Method activationMethod);
        void setDerivativeFunction(const typename ActivationFunctions<T>::Method derivativeMethod);
        void setErrorFunction(const typename ErrorFunctions<T>::Method errorMethod);
        void setOptimizerFunction(const typename OptimizerFunctions<T>::Method optimizerMethod);

        // Public Member Mutators
        void setConnectionCount(const std::size_t connectionCount);

        // Public Member Functions
        //virtual std::unique_ptr<NeuronBase<T>> cloneLayerNeuron() const = 0; // Still working on code here...
        virtual void finalizeLayerNeuron(const size_t inputVectorSize, const T randomizeParameterOne, const T randomizeParameterTwo) = 0; // Still working on code here...
        virtual void saveLayerNeuron(JsonWriter& writer) const; // Still working on code here...
        virtual const T propagateForward(const std::vector<T>& inputVector) = 0; // Still working on code here...

    };

};

#endif // THESEUS88_NEURONBASE_HPPx
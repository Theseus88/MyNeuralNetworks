// LayerDense.hpp
#ifndef THESEUS88_LAYERDENSE_HPP
#define THESEUS88_LAYERDENSE_HPP

#include "LayerBase.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class LayerDense : public LayerBase<T> {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Member Functions
        static void throwError(const char* errorMessage);

        // ADD COMMENT HERE LATER
        T m_randomizeParameterOne, m_randomizeParameterTwo;
        typename RandomizeFunctions<T>::Method m_randomizeMethod;
        typename ActivationFunctions<T>::Method m_activationMethod;
        typename ActivationFunctions<T>::Method m_derivativeMethod;
        typename ErrorFunctions<T>::Method m_errorMethod;
        typename OptimizerFunctions<T>::Method m_optimizerMethod;

    public:
        // ADD COMMENT HERE LATER
        LayerDense() = delete;
        LayerDense(const int neuronCount, const NeuronType neuronType = NeuronType::Feedforward);
        LayerDense(const size_t neuronCount, const NeuronType neuronType = NeuronType::Feedforward);

        // ADD COMMENT HERE LATER
        ~LayerDense();

        // Public Member Mutators
        void setRandomizeParameterOne(const T randomizeParameterOne);
        void setRandomizeParameterTwo(const T randomizeParameterTwo);
        void setRandomizeMethod(const typename RandomizeFunctions<T>::Method randomizeMethod);
        void setActivationMethod(const typename ActivationFunctions<T>::Method activationMethod);
        void setDerivativeMethod(const typename ActivationFunctions<T>::Method derivativeMethod);
        void setErrorMethod(const typename ErrorFunctions<T>::Method errorMethod);
        void setOptimizerMethod(const typename OptimizerFunctions<T>::Method optimizerMethod);

        // Public Member Accessors
        const T getRandomizeParameterOne() const;
        const T getRandomizeParameterTwo() const;
        const typename RandomizeFunctions<T>::Method getRandomizeMethod() const;
        const typename ActivationFunctions<T>::Method getActivationMethod() const;
        const typename ActivationFunctions<T>::Method getDerivativeMethod() const;
        const typename ErrorFunctions<T>::Method getErrorMethod() const;
        const typename OptimizerFunctions<T>::Method getOptimizerMethod() const;

        // Public Member Functions
        const size_t finalizeNetworkLayer(const size_t inputVectorSize) override; // Still working on code here...
        void saveNetworkLayer(JsonWriter& writer, const bool includeNeurons = true) const override; // Still working on code here...
        const std::vector<T>& propagateForward(const std::vector<T>& inputVector) override; // Still working on code here...

    };

};

#endif // THESEUS88_LAYERDENSE_HPP
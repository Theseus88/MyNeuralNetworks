// LayerBase.hpp
#ifndef THESEUS88_LAYERBASE_HPP
#define THESEUS88_LAYERBASE_HPP

#include "../NeuralNetworkCore.hpp"

#include "../Factories/FactoryNeuron.hpp"

#include "../Functions/RandomizeFunctions.hpp"
#include "../Functions/ActivationFunctions.hpp"
#include "../Functions/ErrorFunctions.hpp"
#include "../Functions/OptimizerFunctions.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class LayerBase {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Static Variables
        static std::size_t s_nextUniqueLayerId;

        // Private Static Functions
        static void throwError(const char* errorMessage);
    
    protected:
        // Protected Member Constants
        const std::string M_LAYERDATATYPE;
        const LayerType M_LAYERTYPE;
        const std::size_t M_UNIQUELAYERID;

        // Protected Member Variables
        std::size_t m_inputVectorSize;
        NeuronType m_neuronType;
        T m_randomizeParameterOne, m_randomizeParameterTwo;
        RandomizeMethod m_randomizeMethod;
        ActivationMethod m_activationMethod;
        ActivationMethod m_derivativeMethod;
        ErrorMethod m_errorMethod;
        OptimizerMethod m_optimizerMethod;
        std::size_t m_neuronCount;
        std::vector<std::unique_ptr<NeuronBase<T>>> m_layerNeurons;
        const std::vector<T>* m_inputVectorPtr;
        std::vector<T> m_outputVector;
        std::vector<T> m_errorVector;
        bool m_isFinalized;

        // Protected Member Functions
        void updateLayerNeurons();

    public:
        // Public Member Constructors
        LayerBase(const LayerType layerType, const NeuronType neuronType, const size_t neuronCount, const std::size_t uniqueLayerId = s_nextUniqueLayerId++);

        // Public Member Destructor
        ~LayerBase();

        // Public Static Mutators
        static void setNextUniqueLayerId(const std::size_t nextUniqueLayerId);

        // Public Member Mutators
        void setInputVectorSize(const std::size_t inputVectorSize);
        void setNeuronType(const NeuronType neuronType);
        void setRandomizeParameterOne(const T randomizeParameterOne);
        void setRandomizeParameterTwo(const T randomizeParameterTwo);
        void setRandomizeMethod(const RandomizeMethod randomizeMethod);
        void setActivationMethod(const ActivationMethod activationMethod);
        void setDerivativeMethod(const ActivationMethod derivativeMethod);
        void setErrorMethod(const ErrorMethod errorMethod);
        void setOptimizerMethod(const OptimizerMethod optimizerMethod);
        void setNeuronCount(const std::size_t neuronCount);
        void setLayerNeuronsCapacity(const std::size_t neuronCapacity);
        void setLearningRate(const T learningRate);
        void setMomentum(const T momentum);

        // Public Static Accessors
        static const std::size_t getNextUniqueLayerId();

        // Public Member Accessors
        const std::string getLayerDataType() const;
        const LayerType getLayerType() const;
        const std::size_t getUniqueLayerId() const;
        const std::size_t getInputVectorSize() const;
        const std::size_t getOutputVectorSize() const;
        const NeuronType getNeuronType() const;
        const T getRandomizeParameterOne() const;
        const T getRandomizeParameterTwo() const;
        const RandomizeMethod getRandomizeMethod() const;
        const ActivationMethod getActivationMethod() const;
        const ActivationMethod getDerivativeMethod() const;
        const ErrorMethod getErrorMethod() const;
        const OptimizerMethod getOptimizerMethod() const;
        const std::size_t getNeuronCount() const;
        const std::size_t getLayerNeuronsCapacity() const;
        const std::size_t getLayerNeuronsSize() const;
        const std::vector<T>& getInputVector() const;
        const std::vector<T>& getOutputVector() const;
        const bool getIsFinalized() const;
        const std::size_t getMaxNeuronId() const;

        // Public Member Functions
        //virtual std::unique_ptr<LayerBase<T>> cloneNetworkLayer() const = 0; // Still working on code here...
        virtual const size_t finalizeNetworkLayer(const size_t inputVectorSize); // Still working on code here...
        virtual void loadNetworkLayer(JsonReader& reader) = 0;
        virtual void saveNetworkLayer(JsonWriter& writer) const; // Still working on code here...
        virtual const std::vector<T>& propagateForward(const std::vector<T>& inputVector) = 0; // Still working on code here...
        virtual const std::vector<T>& propagateBackward(const std::vector<T>& targetOutputVector) = 0; // Still working on code here...

    };

};

#endif // THESEUS88_LAYERBASE_HPP
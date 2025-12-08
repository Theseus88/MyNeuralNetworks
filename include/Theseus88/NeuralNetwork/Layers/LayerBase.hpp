// LayerBase.hpp
#ifndef THESEUS88_LAYERBASE_HPP
#define THESEUS88_LAYERBASE_HPP

#include "../NeuralNetworkCore.hpp"
#include "../Factories/FactoryNeuron.hpp"

// ADD COMMENT HERE LATER
namespace Theseus88 {

    // ADD COMMENT HERE LATER
    template <typename T> class LayerBase {
    private:
        // Private Friends
        //friend class NeuralNetwork<T>;

        // Private Static Functions
        static void throwError(const char* errorMessage);
    
    protected:
        // Protected Member Constants
        const std::string M_LAYERDATATYPE;
        const LayerType M_LAYERTYPE;

        // Protected Member Variables
        std::size_t m_inputVectorSize;
        NeuronType m_neuronType;
        std::size_t m_neuronCount;
        std::vector<std::unique_ptr<NeuronBase<T>>> m_layerNeurons;
        const std::vector<T>* m_inputVectorPtr;
        std::vector<T> m_outputVector;
        bool m_isFinalized;

        // Protected Member Functions
        void updateLayerNeurons();

    public:
        // Public Member Constructors
        LayerBase(const LayerType layerType, const NeuronType neuronType, const size_t neuronCount);

        // Public Member Destructor
        ~LayerBase();

        // Public Member Mutators
        void setInputVectorSize(const std::size_t inputVectorSize);
        void setNeuronType(const NeuronType neuronType);
        void setNeuronCount(const std::size_t neuronCount);
        void setLayerNeuronsCapacity(const std::size_t neuronCapacity);

        // Public Member Accessors
        const std::string getLayerDataType() const;
        const LayerType getLayerType() const;
        const std::size_t getInputVectorSize() const;
        const std::size_t getOutputVectorSize() const;
        const NeuronType getNeuronType() const;
        const std::size_t getNeuronCount() const;
        const std::size_t getLayerNeuronsCapacity() const;
        const std::size_t getLayerNeuronsSize() const;
        const std::vector<T>& getInputVector() const;
        const std::vector<T>& getOutputVector() const;
        const bool getIsFinalized() const;

        // Public Member Functions
        //virtual std::unique_ptr<LayerBase<T>> cloneNetworkLayer() const = 0; // Still working on code here...
        virtual const size_t finalizeNetworkLayer(const size_t inputVectorSize) = 0; // Still working on code here...
        virtual void saveNetworkLayer(JsonWriter& writer) const; // Still working on code here...
        virtual const std::vector<T>& propagateForward(const std::vector<T>& inputVector) = 0; // Still working on code here...

    };

};

#endif // THESEUS88_LAYERBASE_HPP
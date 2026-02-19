// source/MyNeuralNetworks.cpp
#include "../include/Theseus88/NeuralNetwork/NeuralNetwork.hpp"

#include "../include/Theseus88/EMNIST/EMNIST.hpp"

using namespace Theseus88;

void testOne() {
    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", 1, 5);

    // ADD COMMENT HERE LATER
    std::size_t layerIndex = 0;
    layerIndex = myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
    myNeuralNetwork.getNetworkLayer(layerIndex).setRandomizeMethod(RandomizeMethod::Normal);
    myNeuralNetwork.getNetworkLayer(layerIndex).setActivationMethod(ActivationMethod::Relu);
    myNeuralNetwork.getNetworkLayer(layerIndex).setDerivativeMethod(ActivationMethod::ReluDerivative);
    myNeuralNetwork.getNetworkLayer(layerIndex).setErrorMethod(ErrorMethod::MeanAbsoluteError);
    myNeuralNetwork.getNetworkLayer(layerIndex).setOptimizerMethod(OptimizerMethod::StochasticGradientDescentWithNesterovMomentum);

    // ADD COMMENT HERE LATER
    myNeuralNetwork.addNetworkLayer<LayerType::Dense>(4);

    // ADD COMMENT HERE LATER
    myNeuralNetwork.insertNetworkLayer<LayerType::Dense>(2, 3);

    // ADD COMMENT HERE LATER
    myNeuralNetwork.finalizeNeuralNetwork();

    // ADD COMMENT HERE LATER
    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestOneData.json");

};

void testTwo() {
    // ADD COMMENT HERE LATER
    auto myNeuralNetwork = INeuralNetwork::newNeuralNetwork("float", "Buddy", 1, 5);
    auto* concreteNet = dynamic_cast<NeuralNetwork<float>*>(myNeuralNetwork.get());
    if (!concreteNet) throw std::runtime_error("ADD ERROR MESSAGE HERE LATER.\n");

    // ADD COMMENT HERE LATER
    std::size_t layerIndex = 0;
    layerIndex = concreteNet->addNetworkLayer<LayerType::Dense>(2);
    concreteNet->getNetworkLayer(layerIndex).setRandomizeMethod(RandomizeMethod::Normal);
    concreteNet->getNetworkLayer(layerIndex).setActivationMethod(ActivationMethod::Relu);
    concreteNet->getNetworkLayer(layerIndex).setDerivativeMethod(ActivationMethod::ReluDerivative);
    concreteNet->getNetworkLayer(layerIndex).setErrorMethod(ErrorMethod::MeanAbsoluteError);
    concreteNet->getNetworkLayer(layerIndex).setOptimizerMethod(OptimizerMethod::StochasticGradientDescentWithNesterovMomentum);

    // ADD COMMENT HERE LATER
    concreteNet->addNetworkLayer<LayerType::Dense>(4);

    // ADD COMMENT HERE LATER
    concreteNet->insertNetworkLayer<LayerType::Dense>(2, 3);

    // ADD COMMENT HERE LATER
    concreteNet->finalizeNeuralNetwork();

    // ADD COMMENT HERE LATER
    concreteNet->saveNeuralNetwork("../build/debug/TestTwoData.json");

};

void testThree() {
    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", 28*28, 10);
    for (int i = 0; i < 8; i++) myNeuralNetwork.addNetworkLayer<LayerType::Dense>(10);
    myNeuralNetwork.finalizeNeuralNetwork();
    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestThreeData.json");
};

void testFour() {
    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", 4, 4);
    std::vector<float> inputVector = {1, 2, 3, 4}, outputVector = {0, 0, 0, 0};

    // Still working on code here...
    for (int i = 0; i < 3; i++) myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
    myNeuralNetwork.finalizeNeuralNetwork();
    outputVector = myNeuralNetwork.propagateForward(inputVector);

    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestFourData.json");
};

void testFive() {
    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", 4, 4);
    std::vector<float> inputVector = {1, 2, 3, 4}, outputVector = {0, 0, 0, 0}, targetOutputVector = {1, 0, 0, 0};

    // Still working on code here...
    for (int i = 0; i < 3; i++) {
        std::size_t layerIndex = myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
        myNeuralNetwork.getNetworkLayer(layerIndex).setOptimizerMethod(OptimizerMethod::StochasticGradientDescent);
    };
    myNeuralNetwork.addNetworkLayer<LayerType::Output>(4);
    myNeuralNetwork.getNetworkLayer(myNeuralNetwork.getNetworkLayersSize() - 1).setOptimizerMethod(OptimizerMethod::StochasticGradientDescent);
    myNeuralNetwork.finalizeNeuralNetwork();
    
    char input = 0;
    do {
        outputVector = myNeuralNetwork.propagateForward(inputVector);
        myNeuralNetwork.propagateBackward(targetOutputVector); // Still working on code here...

        std::cout << "Output: ";
        for (const auto& val : outputVector) std::cout << val << " ";
        std::cout << "\nPress Enter to continue, or type 'x' then Enter to exit: ";
        std::cin.get(input);
        if (input != '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input != 'x');

    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestFiveData.json");
};

void testSix() {
    // Local Constant Variables
    const std::size_t inputLayerVectorSize = 28*28, denseLayerVectorSize = 16, outputLayerVectorSize = 10;

    // ADD COMMENT HERE LATER
    EMNIST::downloadAndUnzip("assets");

    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", inputLayerVectorSize, outputLayerVectorSize);
    myNeuralNetwork.addNetworkLayer<LayerType::Dense>(denseLayerVectorSize);
    myNeuralNetwork.addNetworkLayer<LayerType::Dense>(denseLayerVectorSize);
    myNeuralNetwork.addNetworkLayer<LayerType::Output>(outputLayerVectorSize);
    myNeuralNetwork.finalizeNeuralNetwork();

    // ADD COMMENT HERE LATER
    myNeuralNetwork.saveNeuralNetwork("TestSixData.json");

    // ADD COMMENT HERE LATER
    auto myLoadedNeuralNetwork = INeuralNetwork::loadNeuralNetwork("TestSixData.json");
    auto* concreteNet = dynamic_cast<NeuralNetwork<float>*>(myLoadedNeuralNetwork.get());


};

int main() {
    //testOne();
    //testTwo();
    //testThree();
    //testFour();
    //testFive();
    testSix();

    return 0;
};
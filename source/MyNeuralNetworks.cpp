// source/MyNeuralNetworks.cpp
#include "../include/Theseus88/NeuralNetwork/NeuralNetwork.hpp"
#include <chrono>
#include <iostream>
#include <limits>

using namespace Theseus88;

void testOne() {
    // ADD COMMENT HERE LATER
    NeuralNetwork<float> myNeuralNetwork("Buddy", 1, 5);

    // ADD COMMENT HERE LATER
    std::size_t layerIndex = 0;
    layerIndex = myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
    myNeuralNetwork.getNetworkLayer(layerIndex).setRandomizeMethod(RandomizeFunctions<float>::Method::Normal);
    myNeuralNetwork.getNetworkLayer(layerIndex).setActivationMethod(ActivationFunctions<float>::Method::Relu);
    myNeuralNetwork.getNetworkLayer(layerIndex).setDerivativeMethod(ActivationFunctions<float>::Method::ReluDerivative);
    myNeuralNetwork.getNetworkLayer(layerIndex).setErrorMethod(ErrorFunctions<float>::Method::MeanAbsoluteError);
    myNeuralNetwork.getNetworkLayer(layerIndex).setOptimizerMethod(OptimizerFunctions<float>::Method::StochasticGradientDescentWithNesterovMomentum);

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
    concreteNet->getNetworkLayer(layerIndex).setRandomizeMethod(RandomizeFunctions<float>::Method::Normal);
    concreteNet->getNetworkLayer(layerIndex).setActivationMethod(ActivationFunctions<float>::Method::Relu);
    concreteNet->getNetworkLayer(layerIndex).setDerivativeMethod(ActivationFunctions<float>::Method::ReluDerivative);
    concreteNet->getNetworkLayer(layerIndex).setErrorMethod(ErrorFunctions<float>::Method::MeanAbsoluteError);
    concreteNet->getNetworkLayer(layerIndex).setOptimizerMethod(OptimizerFunctions<float>::Method::StochasticGradientDescentWithNesterovMomentum);

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
    NeuralNetwork<float> myNeuralNetwork("Buddy", 24*24, 10);
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
    for (int i = 0; i < 3; i++) myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
    myNeuralNetwork.finalizeNeuralNetwork();
    
    char input = 0;
    do {
        outputVector = myNeuralNetwork.propagateForward(inputVector);
        myNeuralNetwork.propagateBackward(targetOutputVector); // Still working on code here...

        std::cout << "Output: ";
        for (const auto& val : outputVector) std::cout << val << " ";
        std::cout << "\nPress Enter to continue, or type 'x' (or Escape) and Enter to exit: ";
        std::cin.get(input);
        if (input != '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input != 'x' && input != 27);

    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestFiveData.json");
};

int main() {
    //testOne();
    //testTwo();
    //testThree();
    //testFour();
    testFive();

    return 0;
};
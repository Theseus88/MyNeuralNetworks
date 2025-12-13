// source/MyNeuralNetworks.cpp
#include "../include/Theseus88/NeuralNetwork/NeuralNetwork.hpp"

using namespace Theseus88;

void testOne() {
    NeuralNetwork<float> myNeuralNetwork("Buddy", 1, 5);
    myNeuralNetwork.addNetworkLayer<LayerType::Dense>(2);
    myNeuralNetwork.addNetworkLayer<LayerType::Dense>(4);
    myNeuralNetwork.insertNetworkLayer<LayerType::Dense>(2, 3);
    myNeuralNetwork.finalizeNeuralNetwork();
    myNeuralNetwork.saveNeuralNetwork("../build/debug/TestOneData.json");
};
void testTwo() {
    auto myNeuralNetwork = INeuralNetwork::newNeuralNetwork("float", "Buddy", 1, 5);
    auto* concreteNet = dynamic_cast<NeuralNetwork<float>*>(myNeuralNetwork.get());
    if (!concreteNet) throw std::runtime_error("ADD ERROR MESSAGE HERE LATER.\n");
    concreteNet->addNetworkLayer<LayerType::Dense>(2);
    concreteNet->addNetworkLayer<LayerType::Dense>(4);
    concreteNet->insertNetworkLayer<LayerType::Dense>(2, 3);
    concreteNet->finalizeNeuralNetwork();
    concreteNet->saveNeuralNetwork("../build/debug/TestTwoData.json");
};
void testThree() {

};

int main() {
    testOne();
    testTwo();
    //testThree();
    return 0;
};
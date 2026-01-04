# MyNeuralNetworks

**MyNeuralNetworks** is a high-performance, object-oriented neural network library written entirely from scratch in C++20. Designed with modularity, extensibility, and modern C++ practices in mind, it provides a flexible framework for deep learning without relying on external machine learning frameworks.

## Project Overview

This project demonstrates a deep understanding of both Neural Network architecture and advanced C++ software engineering. It features a custom-built engine for forward propagation, backpropagation, and network serialization.

### Key Features

*   **Pure C++ Implementation**: No external ML libraries (like PyTorch or TensorFlow). All math, logic, and data structures are implemented from the ground up.
*   **Templated Precision**: The entire architecture is templated, allowing networks to be instantiated with `float`, `double`, or `long double` precision depending on performance and accuracy requirements.
*   **Object-Oriented Architecture**:
    *   **Polymorphic Layers**: Distinct implementations for `LayerInput`, `LayerDense`, and `LayerOutput` inheriting from a robust `LayerBase`.
    *   **Factory Pattern**: Utilizes `FactoryLayer` and `FactoryNeuron` for dynamic and extensible component creation.
*   **Advanced C++20 Features**:
    *   Utilizes modern standard library features including `<ranges>` and `<filesystem>`.
    *   **Parallel Execution**: conditional support for `std::execution::par` (Parallel STL) to accelerate computations on heavy layers.
*   **Custom Serialization**: Includes a bespoke `JsonUtilities` library (Reader/Writer) to save and load network states to JSON, implemented without third-party JSON parsers.

## Design Philosophy & Technical Decisions

### 1. Zero-Dependency & Custom Serialization
A core constraint of this project is to avoid external dependencies. This necessitated the creation of **`JsonUtilities`**, a bespoke JSON parser and writer.
*   **Why?** To maintain full control over the serialization format and to implement high-performance, stream-based parsing tailored specifically for large arrays of weights and biases.
*   **Tech Stack**: It utilizes `std::charconv` for fast numerical conversions and manages its own stream buffers to minimize I/O overhead.

### 2. Object-Oriented vs. Data-Oriented
While many ML libraries are purely Data-Oriented (relying on large tensor operations), **MyNeuralNetworks** adopts a hybrid Object-Oriented approach.
*   **Structure**: The network is composed of `Layer` objects, which contain `Neuron` objects.
*   **Benefit**: This makes the code highly readable and extensible. Adding a new type of Neuron or Layer involves creating a new class that inherits from `NeuronBase` or `LayerBase`, rather than rewriting matrix kernels.
*   **Performance**: To mitigate the overhead of OOP, heavy computations (like dense layer propagation) are parallelized using C++20 parallel algorithms (`std::execution::par`).

### 3. Modern C++ Standards (C++20)
The codebase leverages modern language features to ensure safety and expressiveness:
*   **`std::views`**: Used in backpropagation to elegantly iterate layers in reverse without manual index manipulation.
*   **Templates & Type Safety**: The engine is fully templated (`float`, `double`, `long double`), allowing for precise control over numerical accuracy.
*   **Smart Pointers**: `std::unique_ptr` is used extensively for ownership management of layers and neurons, ensuring no memory leaks occur during network restructuring.

## Architecture

The codebase is organized under the `Theseus88` namespace.

*   **`NeuralNetwork<T>`**: The primary interface. It manages the lifecycle of layers, handles the input/output vectors, and orchestrates propagation.
*   **`LayerBase<T>`**: The abstract base class defining the contract for all network layers.
*   **`NeuronBase<T>`**: Represents individual processing units, managing connections, weights, biases, and activation states.
*   **Math & Optimization**:
    *   **Activations**: Sigmoid, ReLU, Tanh, Linear (and their derivatives).
    *   **Optimizers**: Stochastic Gradient Descent (SGD), Momentum, Nesterov, Adam, RMSProp.
    *   **Error Functions**: MSE, CrossEntropy, etc.

## Build Requirements

*   **Environment**: **MSYS2** on Windows (UCRT64 environment).
*   **Compiler**: **G++** (MinGW-w64) with C++20 support.
    *   The build tasks are configured for `C:\msys64\ucrt64\bin\g++.exe`.
*   **Dependencies**:
    *   Standard C++ Library.
    *   **Intel TBB** (Threading Building Blocks): Required for parallel execution policies (`<execution>`) if building with GCC/MinGW (linked as `-ltbb12`).

## Usage Example

```cpp
#include "Theseus88/NeuralNetwork/NeuralNetwork.hpp"

using namespace Theseus88;

int main() {
    // Initialize a network with double precision
    // Name: "DemoNet", Input Size: 2, Output Size: 1
    NeuralNetwork<double> nn("DemoNet", 2, 1);

    // Add a hidden dense layer with 3 neurons
    // The Input and Output layers are handled automatically or can be explicitly defined
    nn.addNetworkLayer<LayerType::Dense>(3);

    // Configure hyperparameters
    nn.setLearningRate(0.05);
    nn.setMomentum(0.9);

    // Finalize the network structure (links layers and allocates memory)
    nn.finalizeNeuralNetwork();

    // Forward Propagation
    std::vector<double> inputs = { 1.0, 0.0 };
    const auto& results = nn.propagateForward(inputs);

    // Backpropagation (Training)
    std::vector<double> targets = { 1.0 };
    nn.propagateBackward(targets);

    // Save the network state to JSON
    nn.saveNeuralNetwork("network_state.json");

    return 0;
}
```

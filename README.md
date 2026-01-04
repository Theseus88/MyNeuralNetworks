# MyNeuralNetworks

[![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++ CI Build](https://github.com/Theseus88/MyNeuralNetworks/actions/workflows/build.yml/badge.svg)](https://github.com/Theseus88/MyNeuralNetworks/actions/workflows/build.yml)

**MyNeuralNetworks** is a high-performance, object-oriented neural network library written entirely from scratch in C++20. Designed with modularity, extensibility, and modern C++ practices in mind, it provides a flexible framework for deep learning without relying on external machine learning frameworks.

## Table of Contents

- [Key Features](#key-features)
- [Quick Start](#quick-start)
- [Setup and Build Instructions](#setup-and-build-instructions)
  - [Prerequisites](#prerequisites)
  - [Windows Setup (MinGW)](#windows-setup-mingw)
  - [Linux Setup (Guidance)](#linux-setup-guidance)
  - [Building the Project](#building-the-project)
- [Architecture Deep Dive](#architecture-deep-dive)
- [Contributing](#contributing)
- [License](#license)

## Key Features

*   **Pure C++20 Implementation**: Built entirely from scratch without external ML libraries (like PyTorch or TensorFlow).
*   **Templated Precision**: Supports `float`, `double`, or `long double` to precisely control numerical accuracy and performance.
*   **Hybrid Architecture**:
    *   **Object-Oriented**: Composed of polymorphic `Layer` and `Neuron` objects (managed via `std::unique_ptr` and Factory patterns) for readability and extensibility.
    *   **Parallelized**: Heavy computations utilize C++20 parallel algorithms (`std::execution::par`) to mitigate OOP overhead.
*   **Modern C++ Features**: Leverages `<ranges>`, `std::views` (for reverse iteration during backpropagation), and `<filesystem>`.
*   **Custom Serialization (`JsonUtilities`)**: A bespoke, zero-dependency JSON parser/writer designed for high-performance serialization of network states, using `std::to_chars` for fast, locale-independent numerical formatting.

## Quick Start

Here is a brief example of how to define, train, and save a network.

```cpp
#include "Theseus88/NeuralNetwork/NeuralNetwork.hpp"

using namespace Theseus88;

int main() {
    // 1. Initialize a network with double precision
    // Name: "DemoNet", Input Size: 2, Output Size: 1
    NeuralNetwork<double> nn("DemoNet", 2, 1);

    // 2. Add a hidden dense layer with 3 neurons
    // The Input and Output layers are handled automatically
    nn.addNetworkLayer<LayerType::Dense>(3);

    // 3. Configure hyperparameters
    nn.setLearningRate(0.05);
    nn.setMomentum(0.9);

    // 4. Finalize the network structure (links layers and allocates memory)
    nn.finalizeNeuralNetwork();

    // 5. Propagate forward with some input
    std::vector<double> inputs = { 1.0, 0.0 };
    const auto& results = nn.propagateForward(inputs);

    // 6. Train the network by propagating backward with target values
    std::vector<double> targets = { 1.0 };
    nn.propagateBackward(targets);

    // 7. Save the trained network state to a JSON file
    nn.saveNeuralNetwork("network_state.json");

    return 0;
}
```

## Setup and Build Instructions

### Prerequisites

- **Visual Studio Code**: With the following Microsoft extensions:
  - `C/C++`
  - `C/C++ Extension Pack`
- **A C++20 Compliant Compiler**: (e.g., GCC 10+, Clang 12+, MSVC v19.29+).
- **Intel TBB (Threading Building Blocks)**: Required for parallel execution support with GCC/MinGW.

### Windows Setup (MinGW)

The recommended toolchain on Windows is MinGW-w64 installed via MSYS2.

1.  **Install MSYS2 and Toolchain**:
    - Download and run the installer from the **[MSYS2 website](https://www.msys2.org/)**.
    - After installation, an MSYS2 terminal will open. Install the toolchain and TBB with `pacman`:
      ```sh
      # Installs g++, gdb, and other development tools
      pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
      # Installs the TBB library for parallel execution
      pacman -S mingw-w64-ucrt-x86_64-tbb
      ```

2.  **Update Windows PATH**:
    - Add the MinGW-w64 `bin` folder to your Windows `PATH` environment variable. The default location is `C:\msys64\ucrt64\bin`.

3.  **Verify Installation**:
    - Open a **new** Command Prompt and run `g++ --version` and `gdb --version` to confirm they are accessible.

> For a complete video walkthrough, see the official VS Code guide: **[Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)**.

### Linux Setup (Guidance)

For Debian-based systems (like Ubuntu), you can install the necessary tools with `apt`:
```sh
sudo apt update
sudo apt install build-essential gdb libtbb-dev
```
The provided VS Code build tasks are currently configured for Windows but can be adapted for Linux.

### Building the Project

This repository is configured with VS Code build tasks.
1.  Open the project folder in VS Code.
2.  Open the main file you wish to compile (e.g., a `main.cpp` that uses the library).
3.  Press `Ctrl+Shift+B` to run the default build task.
4.  Select from the available tasks:
    *   `C/C++: g++.exe build active file (Debug C++20)`
    *   `C/C++: g++.exe build active file (Release C++20)`

The executable will be placed in the `build/debug` or `build/release` directory.

## Architecture Deep Dive

The library is designed with a clear, object-oriented structure that prioritizes readability and extensibility.

-   **`NeuralNetwork<T>`**: The primary interface. It manages the lifecycle of layers, handles I/O, and orchestrates propagation.
-   **`LayerBase<T>`**: The abstract base class for all network layers (`LayerInput`, `LayerDense`, `LayerOutput`). This polymorphic design makes it easy to add new layer types.
-   **`NeuronBase<T>`**: Represents individual processing units, managing connections, weights, biases, and activation states.
-   **Factories**: `FactoryLayer` and `FactoryNeuron` are used for dynamic and extensible component creation, simplifying network construction from files.
-   **Math & Optimization**: A rich set of functions are provided for:
    *   **Activations**: Sigmoid, ReLU, Tanh, Linear (and their derivatives).
    *   **Optimizers**: SGD, Momentum, Nesterov, Adam, RMSProp.
    *   **Error Functions**: MSE, Cross-Entropy, etc.

## Contributing

Contributions are welcome! If you'd like to help improve the library, please feel free to fork the repository, make your changes, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

*(A more formal `CONTRIBUTING.md` guide is planned for the future.)*

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

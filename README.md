# MyNeuralNetworks

<p align="center">
  <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/Language-C%2B%2B20-blue.svg" alt="Language"></a>
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License: MIT"></a>
  <a href="https://codespaces.new/Theseus88/MyNeuralNetworks"><img src="https://img.shields.io/badge/Open%20in-GitHub%20Codespaces-blue?logo=github" alt="Open in GitHub Codespaces"></a>
  <a href="https://vscode.dev/github/Theseus88/MyNeuralNetworks"><img src="https://img.shields.io/badge/Open%20in-VS%20Code-blue?logo=visualstudiocode" alt="Open in VS Code"></a>
  <a href="https://github.com/Theseus88/MyNeuralNetworks/commits/main"><img src="https://img.shields.io/github/last-commit/Theseus88/MyNeuralNetworks" alt="Last Commit"></a>
  <a href="https://github.com/Theseus88/MyNeuralNetworks/actions/workflows/build.yml"><img src="https://github.com/Theseus88/MyNeuralNetworks/actions/workflows/build.yml/badge.svg" alt="C++ CI Build"></a>
</p>

**MyNeuralNetworks** is a high-performance, object-oriented neural network library written entirely from scratch in C++20. Designed with modularity, extensibility, and modern C++ practices in mind, it provides a flexible framework for deep learning without relying on external machine learning frameworks.

## Table of Contents

- [Key Features](#key-features)
- [Project Status & Roadmap](#project-status-&-roadmap)
- [Quick Start](#quick-start)
- [Setup and Build Instructions](#setup-and-build-instructions)
  - [Prerequisites](#prerequisites)
  - [Windows Setup (MinGW)](#windows-setup-mingw)
  - [Linux Setup (GCC)](#linux-setup-gcc)
  - [GitHub Codespaces](#github-codespaces)
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

## Project Status & Roadmap

**Note:** This project is currently a **Work in Progress**. While the core training and saving mechanisms are functional, several key features are actively being developed and are expected to be completed within the next few days.

*   **Serialization**:
    *   `saveNeuralNetwork` is implemented using a custom `JsonWriter`.
    *   `loadNeuralNetwork` is currently **pending implementation**.
    *   `JsonReader` requires a revamp to align with the architecture of `JsonWriter` to ensure seamless state restoration.
*   **Datasets**:
    *   Work is underway on an `EMNIST` class to automatically download datasets (gzip format) and generate test cases for benchmarking.

These components are interdependent, and full save/load functionality will be available once the JSON parsing logic is finalized.

## Quick Start

Here is a brief example of how to define, train, and save a network. This logic can be placed in your main entry point (e.g., `source/MyNeuralNetworks.cpp`).

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

> **Note**: The provided `tasks.json` and `launch.json` files assume the default MSYS2 installation path (`C:\msys64\ucrt64`). If you installed MSYS2 in a different location, you will need to update the paths in the `.vscode` configuration files.

> For a complete video walkthrough, see the official VS Code guide: **[Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)**.

### Linux Setup (GCC)

For Debian-based systems (like Ubuntu), you can install the necessary tools with `apt`:

```sh
sudo apt update
sudo apt install build-essential gdb libtbb-dev curl unzip
```

The provided VS Code build tasks and launch configurations are configured for both Windows and Linux support.

### GitHub Codespaces

This project is fully configured for **GitHub Codespaces**, allowing you to start coding immediately without local setup.

1.  Click the **Code** button on the GitHub repository page.
2.  Select the **Codespaces** tab.
3.  Click **Create codespace on main**.

The environment automatically provisions:
*   **Compiler**: GCC (C++20 compliant) with GDB.
*   **Dependencies**: Intel TBB, Curl, Unzip.
*   **VS Code**: Pre-installed C/C++ Extension Pack and configured build tasks.

### Building the Project

This repository is configured with VS Code build tasks that compile the entire project.
1.  Open the project folder in VS Code.
2.  Press `Ctrl+Shift+B` to run the default build task (Debug).
3.  Alternatively, go to **Terminal > Run Build Task...** and select:
    *   `Build (Debug)`: Compiles with debug symbols.
    *   `Build (Release)`: Compiles with `-O3` optimization.

The executable will be placed in the `build/debug` or `build/release` directory.

### Running and Debugging

Launch configurations are provided to run and debug the application directly from VS Code:
1.  Open the **Run and Debug** view (`Ctrl+Shift+D`).
2.  Select `Debug MyNeuralNetworks` or `Release MyNeuralNetworks` from the dropdown.
3.  Press `F5` to build and run the application.

## Architecture Deep Dive

The library is designed with a clear, object-oriented structure that prioritizes readability and extensibility.

-   **`NeuralNetwork<T>` (The Orchestrator)**:
    -   Acts as the primary container and interface for the user.
    -   Manages the lifecycle of all layers using `std::unique_ptr` for RAII-compliant memory management.
    -   Orchestrates data flow (Forward Propagation) and error correction (Backpropagation) across the entire topology.

-   **`LayerBase<T>` (Polymorphic Abstraction)**:
    -   Defines a unified interface for all layer types (`LayerInput`, `LayerDense`, `LayerOutput`).
    -   Enables the network to iterate through heterogeneous layers generically.
    -   Encapsulates layer-specific logic, such as neuron management and error calculation.

-   **`NeuronBase<T>` (The Computational Unit)**:
    -   Stores individual weights, biases, and activation states.
    -   Designed to be lightweight while maintaining encapsulation of gradients and deltas.

-   **Factories & Serialization**:
    -   `FactoryLayer` and `FactoryNeuron` decouple object creation from implementation, facilitating dynamic network construction.
    -   This architecture supports the custom `JsonReader` (planned) to reconstruct complex topologies from disk without recompilation.

-   **Math & Optimization Modules**:
    -   **Activations**: Highly optimized implementations of Sigmoid, ReLU, Tanh, and Linear functions (plus derivatives).
    -   **Optimizers**: Modular implementations of SGD, Momentum, Nesterov, Adam, and RMSProp allow for flexible training strategies per layer.
    -   **Error Functions**: Pluggable loss functions like Mean Squared Error (MSE) and Cross-Entropy.

## Contributing

Contributions are welcome! If you'd like to help improve the library, please feel free to fork the repository, make your changes, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

*(A more formal `CONTRIBUTING.md` guide is planned for the future.)*

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

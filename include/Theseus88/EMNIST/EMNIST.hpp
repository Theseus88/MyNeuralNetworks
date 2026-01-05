// include/Theseus88/EMNIST/EMNIST.hpp
#ifndef THESEUS88_EMNIST_HPP
#define THESEUS88_EMNIST_HPP

#include <cstdlib>      // std::system
#include <filesystem>   // std::filesystem
#include <iostream>     // std::cout
#include <stdexcept>    // std::runtime_error
#include <string>       // std::string

// ADD COMMENT HERE LATER
namespace Theseus88 {
    // ADD COMMENT HERE LATER
    class EMNIST {
    public:
        // ADD COMMENT HERE LATER
        static void downloadAndUnzip(const std::filesystem::path& targetDirectory) {
            namespace fs = std::filesystem;

            // Ensure the target directory exists
            if (!fs::exists(targetDirectory)) fs::create_directories(targetDirectory);

            const fs::path zipPath = targetDirectory / "gzip.zip";
            // The EMNIST zip from NIST extracts into a 'gzip' subdirectory
            const fs::path extractedPath = targetDirectory / "gzip";

            // If the unzipped folder already exists, we don't need to download or unzip again
            if (fs::exists(extractedPath)) return;

            // 1. Download if the zip file does not exist
            if (!fs::exists(zipPath)) {
                std::cout << "[EMNIST] Target path: " << fs::absolute(zipPath) << std::endl;
                std::cout << "[EMNIST] Dataset archive not found. Downloading from NIST..." << std::endl;
                // Use generic_string() to ensure forward slashes, which works reliably with std::system on both Windows and Linux
                std::string command = "curl -f -L -s -S -o \"" + zipPath.generic_string() + "\" \"https://biometrics.nist.gov/cs_links/EMNIST/gzip.zip\"";
                int result = std::system(command.c_str());
                if (result != 0) throw std::runtime_error("Failed to download EMNIST dataset. Ensure 'curl' is installed.");
                std::cout << "[EMNIST] Download complete." << std::endl;
            };

            // 2. Unzip the dataset
            #ifdef _WIN32
            std::string command = "powershell -Command \"Expand-Archive -Path '" + zipPath.generic_string() + "' -DestinationPath '" + targetDirectory.generic_string() + "' -Force\"";
            #else
            std::string command = "unzip -o \"" + zipPath.generic_string() + "\" -d \"" + targetDirectory.generic_string() + "\"";
            #endif
            std::cout << "[EMNIST] Command: " << command << std::endl;
            std::cout << "[EMNIST] Unzipping dataset..." << std::endl;
            int result = std::system(command.c_str());
            if (result != 0) throw std::runtime_error("Failed to unzip EMNIST dataset. Exit code: " + std::to_string(result));
            std::cout << "[EMNIST] Unzip complete." << std::endl;

            // 3. Delete the zip file to save space
            fs::remove(zipPath);
        };
    };

};

#endif // THESEUS88_EMNIST_HPP
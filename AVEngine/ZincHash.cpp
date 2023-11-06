/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#include "ZincHash.h"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

std::string CalculateFileSHA256(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << endl;
        return "";
    }

    std::vector<unsigned char> fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return picosha2::hash256_hex_string(fileContent);
}

std::map<std::string, std::string> LoadRuleDatabase(const std::string& ruleDbFile) {
    std::map<std::string, std::string> ruleDatabase;
    std::ifstream file(ruleDbFile);

    if (!file.is_open()) {
        std::cerr << "Failed to open the rule database file." << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string hash, virusName;
        if (iss >> hash >> virusName) {
            ruleDatabase[hash] = virusName;
        }
    }

    file.close();
    return ruleDatabase;
}

void ScanFile(const std::map<std::string, std::string>& ruleDatabase, const std::filesystem::directory_entry& entry, std::string& result) {
    if (std::filesystem::is_regular_file(entry)) {
        std::ifstream file(entry.path(), std::ios::binary);
        if (file.is_open()) {
            // Calculate the SHA256 hash of the file
            // You need to implement this part using a SHA256 library
            std::string calculatedHash = CalculateFileSHA256(entry.path().string());

            // Check if the calculated hash exists in the rule database
            auto it = ruleDatabase.find(calculatedHash);
            if (it != ruleDatabase.end()) {
                result += it->second + " " + entry.path().string() + "\n";
            }
            file.close();
        }
    }
}

// Function to scan a file or folder for hashes and build a result string
std::string HashScan(const std::string ruleDbFile, const std::string path) {
    std::map<std::string, std::string> ruleDatabase = LoadRuleDatabase(ruleDbFile);
    std::string result;
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()) {
        // Calculate the SHA256 hash of the file
        // You need to implement this part using a SHA256 library
        std::string calculatedHash = CalculateFileSHA256(path);

        // Check if the calculated hash exists in the rule database
        auto it = ruleDatabase.find(calculatedHash);
        if (it != ruleDatabase.end()) {
            result += it->second + " " + path + "\n";
        }
        file.close();
    }
    else if (std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (std::filesystem::is_regular_file(entry)) {
                std::ifstream file(entry.path(), std::ios::binary);
                if (file.is_open()) {
                    // Calculate the SHA256 hash of the file
                    // You need to implement this part using a SHA256 library
                    std::string calculatedHash = CalculateFileSHA256(entry.path().string());

                    // Check if the calculated hash exists in the rule database
                    auto it = ruleDatabase.find(calculatedHash);
                    if (it != ruleDatabase.end()) {
                        result += it->second + " " + entry.path().string() + "\n";
                    }
                    file.close();
                }
            }
        }
    }
    return result;
}

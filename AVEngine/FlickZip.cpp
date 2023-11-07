#include "FlickZip.h"

std::string scanFlick(const fs::path& directoryPath) {
    std::string output;
    const std::string programPath = std::string(flickzfil);
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_directory(entry.path())) {
            // Recursively scan subdirectories
            output += scanFlick(entry.path());
        }
        else if (fs::is_regular_file(entry.path())) {
            // Process files
            std::string filePath = entry.path().string();
            std::string command = programPath + " " + filePath;

            std::string result = exec(command.c_str());

            for (const auto& entry : std::filesystem::recursive_directory_iterator(FZipPath)) {
                if (entry.is_regular_file()) {
                    const std::string jjjj = std::string(YaraFil) + " -r -p 32 -C " + std::string(rulesign) + " \"" + entry.path().string() + "\"";
                    const std::string yaraouta = exec(jjjj.c_str());
                    const std::string HashOut = HashScan(hashesfil, entry.path().string());
                    output += yaraouta + HashOut + "\n";
                }
            }
        }
    }
    return output;
}
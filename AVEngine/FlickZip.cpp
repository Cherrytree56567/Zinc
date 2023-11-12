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
                    std::string outputa;
                    outputa += yaraouta + HashOut + "\n";
                    const std::vector<std::string> splst = split_string(outputa, "\n");
                    std::string op;
                    size_t skk = 0;
                    while (true) {
                        if (skk > splst.size() - 1) break;
                        if (splst.size() == 0) break;
                        if (splst[skk] == "") continue;
                        const std::vector<std::string> splsst = split_string(splst[skk], " ");
                        size_t pos = splsst[1].find("PATH");
                        std::string result;
                        if (pos != std::string::npos) {
                            result = "/" + splsst[1].substr(pos + 4);
                        }
                        std::cout << "Infected." + splsst[0] + "/" + result + " " + filePath + "\n";
                        op += "Infected." + splsst[0] + "/" + result + " " + filePath + "\n";
                        skk++;
                    }
                    
                    output += op;
                }
            }
        }
    }
    return output;
}
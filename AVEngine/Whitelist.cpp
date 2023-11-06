/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#include "Whitelist.h"

std::vector<std::string> read_whitelist() {
    std::string allFile;
    std::ifstream file(WhitelistFile);
    copy(std::istream_iterator<char>{ file >> std::noskipws }, {}, back_inserter(allFile));
    file.close();
    return split_stringbyd(allFile, "\n");
}

void add_whitelist(std::string filepath) {
    std::ofstream outfile;

    outfile.open(WhitelistFile, std::ios_base::app); // append instead of overwrite
    outfile << "\n" + filepath;
    outfile.close();
}

void remove_whitelist(std::string filepath) {
    std::string allFile;
    std::ifstream file(WhitelistFile);
    copy(std::istream_iterator<char>{ file >> std::noskipws }, {}, back_inserter(allFile));
    file.close();
    std::vector<std::string> arrayfisl = split_stringbyd(allFile, "\n");
    int ijd = 0;
    while (true) {
        if (ijd > sizeof(arrayfisl) / sizeof(arrayfisl[0])) {
            break;
        }
        if (arrayfisl[ijd] == filepath) {
            arrayfisl.erase(arrayfisl.begin() + ijd);
            break;
        }
    }
    int dijd = 0;
    std::string comb = "";
    while (true) {
        if (dijd > sizeof(arrayfisl) / sizeof(arrayfisl[0])) {
            break;
        }
        comb += arrayfisl[dijd];
        comb += "\n";
    }
    std::ofstream outfiled;
    outfiled.open(WhitelistFile, std::ios::trunc);
    outfiled << comb;
    outfiled.close();
}

// Sample split_stringbyd function
std::vector<std::string> split_stringbyda(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

// Sample read_whitelist function
std::vector<std::string> read_whitelista() {
    std::string allFile;
    std::ifstream file(WhitelistFile);
    copy(std::istream_iterator<char>{file >> std::noskipws}, {}, back_inserter(allFile));
    file.close();
    return split_stringbyda(allFile, "\n");
}
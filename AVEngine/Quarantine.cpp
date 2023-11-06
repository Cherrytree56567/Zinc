/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#include "Quarantine.h"

void quarantine(const std::string path) {
    std::string str;
    std::ifstream file(path);
    copy(std::istream_iterator<char>{ file >> std::noskipws }, {}, std::back_inserter(str));
    file.close();
    std::string encoded = encode64(str);
    std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
    std::string fol;
    fol += quarantinefol;
    fol += (std::string)"/";
    fol += base_filename;
    std::ofstream MyFile(fol);

    // Write to the file
    MyFile << encoded;

    // Close the file
    MyFile.close();
    std::remove(path.c_str());
}

void Unquarantine(const std::string filename) {
    std::string fol;
    fol += quarantinefol;
    fol += (std::string)"/";
    fol += filename;
    std::string deskfol;
    deskfol += (std::string)(char*)desktop_directory();
    deskfol += (std::string)"\\Desktop\\";
    deskfol += filename;
    std::string str;
    std::ifstream file(fol);

    if (!file)
    {
        std::cout << "Error in opening file!!!" << std::endl;
    }

    while (true) {
        if (file.eof()) {
            break;
        }
        file >> std::noskipws >> str;
    }

    file.close();
    std::string decoded = decode64(str);
    std::ofstream MyFile(deskfol);

    // Write to the file
    MyFile << decoded;

    // Close the file
    MyFile.close();
    int result = std::remove(fol.c_str());

    std::cout << result;
}

std::vector<std::string> listquarantine() {
    std::vector<std::string> names;
    std::string search_path = (std::string)quarantinefol + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                names.push_back(fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#define _WIN32_WINNT    0x0500
#define _WIN32_IE       0x0500
#define CSIDL_MYMUSIC   0x000D
#define CSIDL_MYVIDEO   0x000E
#include "Base.h"
#include "Utilities.h"
#include "Quarantine.h"
#include "Whitelist.h"
#include "ZincHash.h"
#include <string>
#include <yara.h>

/*
* Error List
*
* 1   - Yara_Initialize Failed
* 2   - Yara_Finalize Failed
*
* Arguments
*
* -UQ - Unquarantine       [Path/file.txt]
* -Q  - Quarantine         [Path/file.txt]
* -AW - Add Whitelist      [Path/file.txt]
* -RW - Remove Whitelist   [Path/file.txt]
* -LQ - List Quarantine    []
* -LW - List Whitelist     []
* -S  - Scan File          [Path/file.txt]
*/

/*
* Functions
*/

#include <filesystem>

int main(int argc, char* argv[]) {
    /*
    * Main Code START 
    */
    std::cout << "Zinc Engine v2 By Ronit D'silva\n";
    if (argc == 1) {
        std::cout << "No Args Specified\n";
    }
    else if ((std::string)argv[1] == "-UQ") {
        if (argc == 3) {
            Unquarantine(argv[2]);
        }
    }
    else if ((std::string)argv[1] == "-Q") {
        if (argc == 3) {
            quarantine(argv[2]);
        }
    }
    else if ((std::string)argv[1] == "-AW") {
        if (argc == 3) {
            add_whitelist(argv[2]);
        }
    }
    else if ((std::string)argv[1] == "-RW") {
        if (argc == 3) {
            remove_whitelist(argv[2]);
        }
    }
    else if ((std::string)argv[1] == "-LQ") {
        std::vector<std::string> qu = listquarantine();
        if (0 == sizeof(qu) / sizeof(qu[0])) {
            std::cout << "0";
        }
        else if (0 > sizeof(qu) / sizeof(qu[0])) {
            std::cout << "0";
        }
        else {
            std::cout << qu[sizeof(qu) / sizeof(qu[0])];
        }
    }
    else if ((std::string)argv[1] == "-LW") {
        std::vector<std::string> filarr = read_whitelist();
        if (0 > sizeof(filarr) / sizeof(filarr[0])) {
            std::cout << "0";
        }
        else {
            for (int i = 0; i < filarr.size(); i++) {
                std::cout << filarr[i];
            }
        }
    }
    else if ((std::string)argv[1] == "-S") {
        if (argc == 3) {
            /*
            * Combine The argv[2] aka the file to scan and add double quotes around it.
            */
            char jjjj[290] = "yara64.exe -r -p 32 -C DB/rules.quad \"";
            strcat(jjjj, argv[2]);
            strcat(jjjj, "\"");
            //std::cout << jjjj << std::endl;
            /*
            * Here is where we execute the yara command
            */
            const std::string yaraouta = exec(jjjj);
            const std::string HashOut = HashScan("C:/Users/ronit/Desktop/AV~~/x64/Debug/DB/hashes.quad", argv[2]);
            const std::string yaraout = HashOut + yaraouta;
            /*
            * We need to split the string into vectors to get the threats recognised from the database
            */
            std::vector<std::string> splst = split_string(yaraout, "\n");
            //std::cout << yaraout;
            std::vector<std::string> filarr = read_whitelista();
            /*
            * Check weather the file is whitelisted or not before declaring it as a virus or quarantining it.
            */
            bool hasQuarantined = false;
            for (const std::string& entry : splst) {
                size_t spacePos = entry.find(' ');
                if (spacePos != std::string::npos) {
                    std::string threatStatus = entry.substr(0, spacePos);
                    std::string filePath = entry.substr(spacePos + 1);

                    bool isWhitelisted = false;
                    for (const std::string& whitelistPath : filarr) {
                        if (boost::filesystem::equivalent(boost::filesystem::path(filePath), boost::filesystem::path(whitelistPath))) {
                            isWhitelisted = true;
                            std::cout << "Whitelisted\n";
                            break;
                        }
                    }

                    if (!isWhitelisted) {
                        // File is not whitelisted, print threat status and file path
                        std::cout << filePath << " has been detected as " << threatStatus << std::endl;
                        //quarantine(filePath);
                        //hasQuarantined = true;
                        //break;
                    }
                }
            }

        }
        else {
            std::cout << "No File Specified\n";
        }
    }
    else {
        std::cout << "Incorrect Args\n";
    }
    /*
    * Main Code END
    */
    return 0;
}

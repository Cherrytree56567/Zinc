/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#pragma once
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <filesystem>
#include <string_view>
#include "SHA256.h"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <string.h>
#include <array>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>
#include <windows.h>
#include <shlobj.h>

const char rulesign[52] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/DB/rules.quad";
const char quarantinefol[49] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/Quarantine";
const char WhitelistFile[53] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/Whitelist.quad";
const char hashesfil[53] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/DB/hashes.quad";
const char flickzfil[51] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/FlickZip.exe";
const char YaraFil[49] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/yara64.exe";
const char FZipPath[43] = "C:/Users/ronit/Desktop/Zinc/x64/Debug/PATH";
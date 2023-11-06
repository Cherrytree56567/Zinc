/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include "sha256.h"
#include <nlohmann/json.hpp>
#include <thread>
#include <sstream>

std::string HashScan(const std::string ruleDatabaseFile, const std::string scanPath);
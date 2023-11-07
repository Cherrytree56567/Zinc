#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "Base.h"
#include "Utilities.h"
#include "ZincHash.h"

namespace fs = boost::filesystem;

std::string scanFlick(const fs::path& directoryPath);
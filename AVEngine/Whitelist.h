/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#pragma once
#include "Base.h"
#include "Utilities.h"

std::vector<std::string> read_whitelist();

void add_whitelist(std::string filepath);

void remove_whitelist(std::string filepath);

std::vector<std::string> read_whitelista();
/*
* Zinc © 2023 by Ronit D'silva is licensed under CC BY-NC-ND 4.0
*/
#pragma once
#include "Base.h"

char* desktop_directory();

std::string decode64(const std::string& val);

std::string encode64(const std::string& val);

std::string exec(const char* cmd);

std::vector<std::string> split_string(const std::string& str, const std::string& delimiter);

std::vector<std::string> split_string_once(const std::string& str, const std::string& delimiter);

std::string space2underscore(std::string text);

std::vector<std::string> split_stringbyd(const std::string& str, const std::string& delimiter);
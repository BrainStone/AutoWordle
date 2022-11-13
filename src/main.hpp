#pragma once

#include <filesystem>
#include <list>

#include "Word.hpp"

int main(int argc, char* argv[]);
std::list<Word> parseWordlist(const std::filesystem::path& path);

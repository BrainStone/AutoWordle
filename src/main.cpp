#include "main.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	// We accept 0 and 2 arguments
	if ((argc != 1) && (argc != 3)) {
		std::cerr << "Usage:\n\t" << argv[0]
		          << " [<allowed_words_file> <solution_words_file>]\n"
		             "\n"
		             "If <allowed_words_file> and <solution_words_file> are not specified the built in\n"
		             "lists are used."
		          << std::endl;
		return 1;
	}

	const bool use_builtins = (argc == 1);
	const std::list<Word> allowed_words = use_builtins ? std::list<Word>() : parseWordlist(argv[1]);
	const std::list<Word> solution_words = use_builtins ? std::list<Word>() : parseWordlist(argv[2]);

	for (const Word& word : allowed_words) {
		std::cout << word << std::endl;
	}

	return 0;
}

std::list<Word> parseWordlist(const std::filesystem::path& path) {
	std::ifstream file(path);
	std::string line;
	std::list<Word> output;

	line.reserve(Word::word_length);

	while (std::getline(file, line)) {
		// Skip all words not 5 chars long
		if (line.size() != Word::word_length) continue;

		output.emplace_back(line);
	}

	return output;
}

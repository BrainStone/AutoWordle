#include "main.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "builtin_lists.hpp"
#include "MatchStatus.hpp"

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
	const std::list<Word> allowed_words = use_builtins ? builtin_lists::allowed_words : parseWordlist(argv[1]);
	const std::list<Word> solution_words = use_builtins ? builtin_lists::solution_words : parseWordlist(argv[2]);

	for (const match& m : MatchStatus("tests", "ssstx").get_state()) {
		std::cout << m << std::endl;
	}

	return 0;
}

std::list<Word> parseWordlist(const std::filesystem::path& path) {
	std::error_code ec;

	if (!std::filesystem::is_regular_file(path, ec)) {
		if (ec) {
			throw std::filesystem::filesystem_error("cannot parse file", path, ec);
		} else {
			throw std::runtime_error("cannot parse file: not a file [" + path.string() + "]");
		}
	}

	std::ifstream file(path);
	std::string line;
	std::list<Word> output;

	line.reserve(Word::word_length);

	while (std::getline(file, line)) {
		// Skip all words not 5 chars long or lines that start with a # (those are comments)
		if ((line.size() != Word::word_length) || (line[0] == '#')) continue;

		output.emplace_back(line);
	}

	return output;
}

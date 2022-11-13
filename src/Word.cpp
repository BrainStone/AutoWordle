#include "Word.hpp"

#include "array_helper.hpp"

using array_helper::make_array;

Word::Word(const char* word) : Word(std::string_view{word}) {}

Word::Word(const std::string& word) : Word(make_array<word_length>(word)) {}

Word::Word(std::string_view word) : Word(make_array<word_length>(word)) {}

Word::Word(const word_t& word) : word(word) {}

bool Word::operator==(const Word& other) const {
	return word == other.word;
}

Word::operator std::string() const noexcept {
	std::string out{cbegin(), cend()};

	return out;
}

std::ostream& operator<<(std::ostream& os, const Word& word) {
	for (char letter : word.word) {
		os << letter;
	}

	return os;
}

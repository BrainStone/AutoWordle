#include "Word.hpp"

#include "array_helper.hpp"

using array_helper::make_array;

Word::Word(const char* word) : Word(std::string_view{word}) {}

Word::Word(const std::string& word) : Word(make_array<word_length>(word)) {}

Word::Word(std::string_view word) : Word(make_array<word_length>(word)) {}

Word::Word(const word_t& word) : word(word) {}

Word::operator std::string() const noexcept {
	std::string out{cbegin(), cend()};

	return out;
}

Word::mapping_t Word::character_mapping() const {
	std::multimap<char, std::size_t> mapping{};

	for (std::size_t i = 0; i < word_length; ++i) {
		mapping.insert({word[i], i});
	}

	return mapping;
}

std::ostream& operator<<(std::ostream& os, const Word& word) {
	for (char letter : word.word) {
		os << letter;
	}

	return os;
}

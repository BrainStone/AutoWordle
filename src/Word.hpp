#pragma once

#include <array>
#include <ostream>
#include <string>
#include <string_view>

class Word {
public:
	static constexpr std::size_t word_length = 5;
	using word_t = std::array<char, word_length>;

private:
	const word_t word;

public:
	explicit Word(const char* word);
	explicit Word(const std::string& word);
	explicit Word(std::string_view word);
	explicit Word(const word_t& word);
	Word(const Word&) = default;
	Word(Word&&) = default;

	Word& operator=(const Word&) = delete;
	Word& operator=(Word&&) = delete;

	~Word() = default;

	friend std::ostream& operator<<(std::ostream& os, const Word& word);
};

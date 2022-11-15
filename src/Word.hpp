#pragma once

#include <array>
#include <map>
#include <ostream>
#include <string>
#include <string_view>

class Word {
public:
	static constexpr std::size_t word_length = 5;
	using word_t = std::array<char, word_length>;
	using const_iterator = word_t::const_iterator;
	using const_reverse_iterator = word_t::const_reverse_iterator;
	using mapping_t = std::multimap<char, std::size_t>;

private:
	const word_t word;

public:
	Word(const char* word);         // NOLINT(google-explicit-constructor)
	Word(const std::string& word);  // NOLINT(google-explicit-constructor)
	Word(std::string_view word);    // NOLINT(google-explicit-constructor)
	explicit Word(const word_t& word);
	Word(const Word&) = default;
	Word(Word&&) = default;

	Word& operator=(const Word&) = delete;
	Word& operator=(Word&&) = delete;

	~Word() = default;

	bool operator==(const Word& other) const;
	bool operator!=(const Word& other) const = default;

	constexpr char operator[](std::size_t index) const {
		return word[index];
	}

	[[nodiscard]] constexpr const_iterator begin() const noexcept {
		return word.begin();
	}
	[[nodiscard]] constexpr const_iterator cbegin() const noexcept {
		return word.cbegin();
	}

	[[nodiscard]] constexpr const_iterator end() const noexcept {
		return word.end();
	}
	[[nodiscard]] constexpr const_iterator cend() const noexcept {
		return word.cend();
	}

	[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept {
		return word.rbegin();
	}
	[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept {
		return word.crbegin();
	}

	[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept {
		return word.rend();
	}
	[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept {
		return word.crend();
	}

	[[nodiscard]] constexpr std::size_t size() const noexcept {
		return word.size();
	}

	[[nodiscard]] constexpr std::size_t max_size() const noexcept {
		return word.max_size();
	}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return word.empty();
	}

	[[nodiscard]] mapping_t character_mapping() const;

	explicit operator std::string() const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Word& word);
};

#pragma once

#include <boost/integer.hpp>

#include "Word.hpp"

namespace helper {
constexpr std::size_t powi(std::size_t base, std::size_t exp) {
	std::size_t res = 1;

	while (exp) {
		if (exp & 1) res *= base;
		exp >>= 1;
		base *= base;
	}

	return res;
}
}  // namespace helper

class MatchStatus {
public:
	using state_t = boost::uint_value_t<helper::powi(3, Word::word_length)>::fast;

	enum class match : state_t {
		grey = 0,
		yellow = 1,
		green = 2,
	};

private:
	const state_t state;

public:
	MatchStatus(const Word& guess, const Word& solution);
	MatchStatus(const MatchStatus&) = default;
	MatchStatus(MatchStatus&&) = default;

	MatchStatus& operator=(const MatchStatus&) = delete;
	MatchStatus& operator=(MatchStatus&&) = delete;

	~MatchStatus() = default;

private:
	static state_t getState(const Word& guess, const Word& solution);
};

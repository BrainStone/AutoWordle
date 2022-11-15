#pragma once

#include "enum.hpp"
#include "Word.hpp"

// NOLINTNEXTLINE(misc-no-recursion,readability-const-return-type,google-explicit-constructor)
BETTER_ENUM(match, std::uint_fast8_t, grey = 0, yellow = 1, green = 2)

class MatchStatus {
public:
	using state_t = std::array<match, Word::word_length>;

private:
	const state_t state;

public:
	MatchStatus(const Word& guess, const Word& solution);
	MatchStatus(const MatchStatus&) = default;
	MatchStatus(MatchStatus&&) = default;

	MatchStatus& operator=(const MatchStatus&) = delete;
	MatchStatus& operator=(MatchStatus&&) = delete;

	[[nodiscard]] constexpr const state_t& get_state() const noexcept {
		return state;
	}

	~MatchStatus() = default;

private:
	static state_t generate_state(const Word& guess, const Word& solution);
};

#pragma once

#include <iostream>

#include "enum.hpp"
#include "Word.hpp"

// NOLINTNEXTLINE(misc-no-recursion,readability-const-return-type,google-explicit-constructor)
BETTER_ENUM(match, std::uint_fast8_t, grey = 0, yellow = 1, green = 2)

class MatchStatus {
public:
	using state_t = std::array<match, Word::word_length>;

private:
	state_t state;

public:
	MatchStatus() = default;
	MatchStatus(const Word& guess, const Word& solution);
	MatchStatus(const MatchStatus&) = default;
	MatchStatus(MatchStatus&&) = default;

	MatchStatus& operator=(const MatchStatus&) = default;
	MatchStatus& operator=(MatchStatus&&) = default;

	~MatchStatus() = default;

	constexpr std::strong_ordering operator<=>(const MatchStatus& other) const noexcept = default;

	constexpr bool operator==(const MatchStatus& other) const noexcept = default;
	constexpr bool operator!=(const MatchStatus& other) const noexcept = default;

	constexpr bool operator<(const MatchStatus& other) const noexcept = default;
	constexpr bool operator<=(const MatchStatus& other) const noexcept = default;
	constexpr bool operator>(const MatchStatus& other) const noexcept = default;
	constexpr bool operator>=(const MatchStatus& other) const noexcept = default;

	[[nodiscard]] constexpr const state_t& get_state() const noexcept {
		return state;
	}

	friend std::ostream& operator<<(std::ostream& os, const MatchStatus& matchStatus);
	friend std::istream& operator>>(std::istream& is, MatchStatus& matchStatus);

private:
	static state_t generate_state(const Word& guess, const Word& solution);
};

#include "MatchStatus.hpp"

#include <ranges>

MatchStatus::MatchStatus(const Word& guess, const Word& solution) : state(getState(guess, solution)) {}

MatchStatus::state_t MatchStatus::getState(const Word& guess, const Word& solution) {
	std::array<match, Word::word_length> states{};

	for (std::size_t i = 0; i < Word::word_length; ++i) {
		if (guess[i] == solution[i]) {
			states[i] = match::green;
		} else if (false /* TODO */) {
			states[i] = match::yellow;
		} else {
			states[i] = match::grey;
		}
	}

	state_t out = 0;

	for (match state : std::ranges::reverse_view(states)) {
		out = (out * 3) + static_cast<state_t>(state);
	}

	return out;
}

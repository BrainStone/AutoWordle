#include "MatchStatus.hpp"

#include <ranges>

MatchStatus::MatchStatus(const Word& guess, const Word& solution) : state(getState(guess, solution)) {}

MatchStatus::state_t MatchStatus::getState(const Word& guess, const Word& solution) {
	std::array<match, Word::word_length> states{};
	const Word::mapping_t mapping_guess = guess.character_mapping();
	Word::mapping_t mapping_solution = solution.character_mapping();

	std::pair<Word::mapping_t::iterator, Word::mapping_t::iterator> result;
	Word::mapping_t::iterator match_letter;

	for (const Word::mapping_t::value_type& letter : mapping_guess) {
		// Get all letters in the solution that match our current letter
		result = mapping_solution.equal_range(letter.first);

		if (result.first == result.second) {
			// No match
			states[letter.second] = match::grey;
		} else {
			// See if there's a letter in the same position in the solution word
			match_letter = std::find_if(result.first, result.second,
			                            [&letter](const Word::mapping_t::value_type& solution_letter) {
				                            return letter.second == solution_letter.second;
			                            });

			if (match_letter == result.second) {
				// No positional match, take the first letter match
				match_letter = result.first;

				states[letter.second] = match::yellow;
			} else {
				states[letter.second] = match::green;
			}

			// Remove the matched latter from the solution set, so we don't match it again
			mapping_solution.erase(match_letter);
		}
	}

	state_t out = 0;

	for (match state : std::ranges::reverse_view(states)) {
		out = (out * 3) + static_cast<state_t>(state);
	}

	return out;
}

#include "MatchStatus.hpp"

#include <ranges>

MatchStatus::MatchStatus(const Word& guess, const Word& solution) : state(generate_state(guess, solution)) {}

MatchStatus::state_t MatchStatus::generate_state(const Word& guess, const Word& solution) {
	std::array<match, Word::word_length> state{};
	const Word::mapping_t mapping_guess = guess.character_mapping();
	Word::mapping_t mapping_solution = solution.character_mapping();

	std::pair<Word::mapping_t::iterator, Word::mapping_t::iterator> result;
	Word::mapping_t::iterator match_letter;

	// Green matches first
	for (std::size_t i = 0; i < Word::word_length; ++i) {
		if (guess[i] == solution[i]) {
			state[i] = match::green;

			// Remove the letter from the solution_mapping
			result = mapping_solution.equal_range(guess[i]);
			mapping_solution.erase(std::find_if(
			    result.first, result.second,
			    [i](const Word::mapping_t::value_type& solution_letter) { return solution_letter.second == i; }));
		} else {
			// This is to ensure we have a proper value set
			state[i] = match::grey;
		}
	}

	for (const Word::mapping_t::value_type& letter : mapping_guess) {
		// Skip letter if it's green
		if (state[letter.second] == +match::green) {
			continue;
		}

		// Get all letters in the solution that match our current letter
		match_letter = mapping_solution.find(letter.first);

		if (match_letter != mapping_solution.end()) {
			// We found a letter
			state[letter.second] = match::yellow;

			// Remove the matched latter from the solution set, so we don't match it again
			mapping_solution.erase(match_letter);
		}
	}

	return state;
}

std::istream& operator>>(std::istream& is, MatchStatus& matchStatus) {
	MatchStatus temp{};
	char letter;

	for (std::size_t i = 0; is && i < Word::word_length; ++i) {
		letter = static_cast<char>(is.get());

		if ((letter > '2') || (letter < '0')) {
			is.exceptions(std::istream::failbit);

			return is;
		}

		temp.state[i] = match::_from_index_unchecked(letter - '0');
	}

	if (is) {
		matchStatus = temp;
	}

	return is;
}

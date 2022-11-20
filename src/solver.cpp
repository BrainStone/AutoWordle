#include "solver.hpp"

solver_tree generate_optimal_tree(const std::list<Word>& allowed_words, const std::list<Word>& solution_words,
                                  std::size_t depth) {
	std::map<MatchStatus, std::list<Word>> solution_words_grouped{};
	std::map<MatchStatus, std::list<Word>> best_solution_words_grouped{};
	Word* best_word = nullptr;
	std::size_t best_score = max_guesses + 1;

	for (const Word& guess : allowed_words) {
		solution_words_grouped.clear();

		for (const Word& potential_solution : solution_words) {
			solution_words_grouped[MatchStatus(guess, potential_solution)].push_back(potential_solution);
		}
	}

	solver_tree result{*best_word};

	for (const auto& xxx : best_solution_words_grouped) {
		result.add_subtree(xxx.first, generate_optimal_tree(allowed_words, xxx.second, depth + 1));
	}

	return result;
}

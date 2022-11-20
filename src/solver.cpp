#include "solver.hpp"

solver_tree generate_optimal_tree(const std::list<Word>& allowed_words, const std::list<Word>& solution_words) {
	return detail::generate_optimal_tree_with_depth(allowed_words, solution_words, 0).first;
}

namespace detail {
const std::pair<solver_tree, std::size_t> dead_end = {solver_tree{}, max_guesses + 1};

std::pair<solver_tree, std::size_t> generate_optimal_tree_with_depth(const std::list<Word>& allowed_words,
                                                                     const std::list<Word>& solution_words,
                                                                     std::size_t depth) {
	if (depth > max_guesses) {
		return dead_end;
	}

	if (solution_words.size() == 1) {
		return {solver_tree{solution_words.front()}, depth};
	}

	std::map<MatchStatus, std::list<Word>> solution_words_grouped{};
	solver_tree result{};
	solver_tree temp_tree;
	std::pair<solver_tree, std::size_t> temp_result;
	std::size_t worst_subscore = 0;
	std::size_t best_score = max_guesses + 1;

	for (const Word& guess : allowed_words) {
		solution_words_grouped.clear();
		temp_tree = solver_tree{guess};

		for (const Word& potential_solution : solution_words) {
			solution_words_grouped[MatchStatus(guess, potential_solution)].push_back(potential_solution);
		}

		if (solution_words_grouped.size() == 1) {
			continue;
		}

		for (const auto& group : solution_words_grouped) {
			temp_result = generate_optimal_tree_with_depth(allowed_words, group.second, depth + 1);

			if (temp_result.second > worst_subscore) [[likely]] {
				worst_subscore = temp_result.second;

				// We hit a dead end, no point in continuing
				if (worst_subscore >= best_score) [[likely]] {
					break;
				}
			}

			temp_tree.add_subtree(group.first, temp_result.first);
		}

		if (worst_subscore < best_score) {
			best_score = worst_subscore;
			result = temp_tree;
		}
	}

	return {result, best_score};
}

}  // namespace detail

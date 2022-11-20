#pragma once

#include <list>
#include <map>

#include "MatchStatus.hpp"
#include "Tree.hpp"
#include "Word.hpp"

constexpr std::size_t max_guesses = 6;
using solver_tree = Tree<MatchStatus, Word>;

solver_tree generate_optimal_tree(const std::list<Word>& allowed_words, const std::list<Word>& solution_words,
                                  std::size_t depth = 0);

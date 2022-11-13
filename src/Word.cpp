#include "Word.hpp"

#include "array_helper.hpp"

using array_helper::make_array;

Word::Word(const std::string& word) : Word(make_array<word_length>(word)) {}

Word::Word(const std::string_view& word) : Word(make_array<word_length>(word)) {}

Word::Word(const word_t& word) : word(word) {}

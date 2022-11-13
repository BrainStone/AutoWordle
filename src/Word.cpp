#include "Word.hpp"

#include "array_helper.hpp"

Word::Word(const std::string& word) : Word(make_array<word_length>(word.begin(), word.end())) {}

Word::Word(const std::string_view& word) : Word(make_array<word_length>(word.begin(), word.end())) {}

Word::Word(const word_t& word) : word(word) {}

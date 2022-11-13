#pragma once

#include <array>
#include <cassert>
#include <iterator>

namespace internal {

template <std::size_t... Indices>
struct indices {
	using next = indices<Indices..., sizeof...(Indices)>;
};

template <std::size_t N>
struct build_indices {
	using type = typename build_indices<N - 1>::type::next;
};

template <>
struct build_indices<0> {
	using type = indices<>;
};

// This ultimately creates a type that looks like this: indices<0, 1, 2, 3, ..., N - 2, N - 1>
template <std::size_t N>
using BuildIndices = typename build_indices<N>::type;

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <std::size_t... I, std::input_iterator InputIterator>
std::array<ValueType<InputIterator>, sizeof...(I)> make_array(InputIterator first, indices<I...>) {
	return std::array<ValueType<InputIterator>, sizeof...(I)>{{(void(I), *first++)...}};
}

}  // namespace internal

template <std::size_t N, std::input_iterator InputIterator>
std::array<internal::ValueType<InputIterator>, N> make_array(InputIterator first, InputIterator last) {
	assert(std::distance(first, last) == N);
	return internal::make_array(first, internal::BuildIndices<N>{});
}

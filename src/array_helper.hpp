#pragma once

#include <array>
#include <cassert>
#include <iterator>

namespace array_helper {
namespace _detail {

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

template <std::input_iterator Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <std::size_t... I, std::input_iterator InputIterator>
auto make_array(InputIterator first, indices<I...>) noexcept -> std::array<ValueType<InputIterator>, sizeof...(I)> {
	return std::array<ValueType<InputIterator>, sizeof...(I)>{{(void(I), *first++)...}};
}

template <class Container>
concept const_iterable = requires(Container container) {
	                         std::cbegin(container);
	                         std::cend(container);
                         };

template <class Container>
concept iterable = (!const_iterable<Container>) && requires(Container container) {
	                                                   std::begin(container);
	                                                   std::end(container);
                                                   };

}  // namespace _detail

template <std::size_t N, std::input_iterator InputIterator>
auto make_array(InputIterator first, InputIterator last) -> std::array<_detail::ValueType<InputIterator>, N> {
	const typename std::iterator_traits<InputIterator>::difference_type diff = std::distance(first, last);

	if (diff < 0) [[unlikely]] {
		throw std::out_of_range("The distance between the iterators is negative");
	} else if (static_cast<std::size_t>(diff) < N) [[unlikely]] {
		throw std::out_of_range("The distance between the iterators is " + std::to_string(diff) +
		                        " but needs to be at least " + std::to_string(N));
	}

	return _detail::make_array(first, _detail::BuildIndices<N>{});
}

template <std::size_t N, _detail::const_iterable Container>
auto make_array(const Container& container)
    -> std::array<_detail::ValueType<decltype(std::cbegin<Container>(std::declval<Container>()))>, N> {
	return make_array<N>(std::cbegin(container), std::cend(container));
}

template <std::size_t N, _detail::iterable Container>
auto make_array(const Container& container)
    -> std::array<_detail::ValueType<decltype(std::begin<Container>(std::declval<Container>()))>, N> {
	return make_array<N>(std::begin(container), std::end(container));
}

}  // namespace array_helper

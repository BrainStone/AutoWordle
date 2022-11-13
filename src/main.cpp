#include "main.hpp"

#include <iostream>
#include <list>

#include "array_helper.hpp"

int main(int argc [[maybe_unused]], char* argv [[maybe_unused]][]) {
	std::list<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	list.push_back(9);
	list.push_back(10);

	std::array<int, 10> dummy(array_helper::make_array<10>(list));

	for (int num : dummy) {
		std::cout << num << ' ';
	}

	return 0;
}

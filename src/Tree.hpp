#pragma once

#include <map>

template <class Key, class Value>
class Tree {
public:
	using key_type = Key;
	using value_type = Value;

private:
	std::map<Key, Tree<Key, Value>> children;
	const Value _value;

public:
	explicit Tree(const Value& value) = default;
	Tree(const Tree&) noexcept = default;
	Tree(Tree&&) noexcept = default;

	Tree& operator=(const Tree&) = delete;
	Tree& operator=(Tree&&) = delete;

	~Tree() = default;

	void add_child(const Key& key, const Value& value) {
		children.emplace(key, value);
	}

	void remove_child(const Key& key) {
		children.erase(key);
	}

	[[nodiscard]] bool has_children() const noexcept {
		return !children.empty();
	}

	[[nodiscard]] std::size_t count_children() const noexcept {
		return children.size();
	}

	const Value& get_value() const noexcept {
		return _value;
	}

	Tree& get_child(const Key& key) {
		return children.at(key);
	}

	const Tree& get_child(const Key& key) const {
		return children.at(key);
	}
};

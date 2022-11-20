#pragma once

#include <map>

template <class Key, class Value>
class Tree {
public:
	using map_type = std::map<Key, Tree<Key, Value>>;
	using key_type = Key;
	using value_type = Value;

private:
	Value _value;
	map_type children;

public:
	Tree() = default;
	explicit Tree(const Value& value) : _value(value){};
	Tree(const Tree<Key, Value>& tree) noexcept = default;
	Tree(Tree<Key, Value>&&) noexcept = default;

	Tree<Key, Value>& operator=(const Tree<Key, Value>&) noexcept = default;
	Tree<Key, Value>& operator=(Tree<Key, Value>&&) noexcept = default;

	~Tree() = default;

	void add_child(const Key& key, const Value& value) {
		children.emplace(key, value);
	}

	void add_subtree(const Key& key, const Tree<Key, Value>& subtree) {
		children.emplace(key, subtree);
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

	Tree<Key, Value>& get_child(const Key& key) {
		return children.at(key);
	}

	const Tree<Key, Value>& get_child(const Key& key) const {
		return children.at(key);
	}

	friend std::ostream& operator<<(std::ostream& os, const Tree<Key, Value>& tree) {
		os << "digraph tree {\n";
		tree.render_nodes(os);
		os << "}";

		return os;
	}

private:
	void render_nodes(std::ostream& os) const {
		bool has_children;

		for (const std::pair<const Key, Tree<Key, Value>>& child : children) {
			has_children = child.second.has_children();

			if (!has_children) {
				os << '_' << child.second._value << " [ label = \"" << child.second._value << "\", color = green ];\n";
			}

			os << _value << " -> ";
			if (!has_children) {
				os << '_';
			}
			os << child.second._value << " [ label = \"" << child.first << "\" ];\n";

			child.second.render_nodes(os);
		}
	}
};

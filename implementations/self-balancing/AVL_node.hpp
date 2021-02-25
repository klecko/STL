#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include <stddef.h>
#include <pair>

/*
	This defines a node for an AVL tree.
	The only difference with _regular_bintree_node is that
	this one saves the height.
*/

template<typename T> class _AVL_node {
private:
	typedef _AVL_node node;

	struct realnode {
		T tag;
		node parent;
		node left;
		node right;
		size_t height;

		realnode() {}
		realnode(const T& tag)
			: tag(tag)
		{}
	};

	realnode* data;

public:
	_AVL_node()
		: data(nullptr)
	{}

	_AVL_node(const T& tag) {
		data = new realnode(tag);
		data->height = 1;	// Default height is one.
	}

	_AVL_node(const node& other)
		: data(other.data)
	{}

	inline bool null() const {
		return (data == nullptr);
	}

	inline node parent() const {
		return data->parent;
	}

	inline void parent(node n) {
		data->parent = n;
	}

	inline node left() const {
		return data->left;
	}

	inline void left(node n) {
		data->left = n;
	}

	inline node right() const {
		return data->right;
	}

	inline void right(node n) {
		data->right = n;
	}

	inline size_t height() const {
		return data->height;
	}

	inline void height(size_t x) {
		data->height = x;
	}

	pair<size_t, size_t> recomputeHeight() {
		size_t left_height, right_height;
		left_height = right_height = 0;

		if(!left().null())
			left_height = left().height();
		if(!right().null())
			right_height = right().height();

		if(left_height > right_height)
			height(left_height + 1);
		else
			height(right_height + 1);

		return pair<size_t, size_t>(left_height, right_height);
	}

	inline void destroy() {
		delete data;
		data = nullptr;
	}

	inline T& operator*() {
		return data->tag;
	}

	inline const T& operator*() const {
		return data->tag;
	}

	inline node& operator=(const node& other) {
		data = other.data;
		return *this;
	}

	inline bool operator==(const node& other) const {
		return (data == other.data);
	}

	inline bool operator!=(const node& other) const {
		return (data != other.data);
	}
};

#endif

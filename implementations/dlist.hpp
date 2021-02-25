#ifndef DLIST_HPP
#define DLIST_HPP

#include <stddef.h>

/*
	This datatype has not been deeply tested and as a result might have bugs.
	Specially the 'insert' and 'remove' methods.
*/

template<typename T> class dlist {
private:
	struct node {
		T data;
		node* prev;
		node* next;
	};

	node* first;
	node* last;
	size_t sz;

public:
	dlist() : first(nullptr), last(nullptr), sz(0) {}

	inline dlist(const dlist& other) {
		*this = other;
	}

	dlist(dlist&& other) : first(other.first), last(other.last), sz(other.sz) {
		other.first = other.last = nullptr;
		other.sz = 0;
	}

	inline ~dlist() {
		clear();
	}

	inline size_t size() const {
		return sz;
	}

	inline bool empty() const {
		return sz == 0;
	}

	void clear() {
		node* current = first;
		while(current) {
			node* next = current->next;
			delete current;
			current = next;
		}

		first = last = nullptr;
	}

	// Back.
	void push_back(T e) {
		node* newnode = new node;
		newnode->data = e;
		newnode->next = nullptr;
		newnode->prev = last;

		if(last) last->next = newnode;
		last = newnode;
		if(!sz) first = last;
		++sz;
	}

	void pop_back() {
		node* aux = last;
		last = last->prev;
		last->next = nullptr;
		delete aux;
		--sz;
		if(!sz) first = last;
	}

	inline T& back() {
		return last->data;
	}

	inline const T& back() const {
		return last->data;
	}

	// Front.
	void push_front(T e) {
		node* newnode = new node;
		newnode->data = e;
		newnode->next = first;
		newnode->prev = nullptr;

		first = newnode;
		if(!sz) last = first;
		sz++;
	}

	void pop_front() {
		node* aux = first;
		first = first->next;
		delete aux;
		sz--;
		if(!sz) last = first;
	}

	inline T& front() {
		return first->data;
	}

	inline const T& front() const {
		return first->data;
	}

	// Operators.
	// CAREFUL WHEN NEEDED: THIS IS WRONG!
	/*dlist<T>& operator=(const dlist<T>& other) {
		if(this != &other) {
			node* current_other = other.first;
			node* current_this = nullptr;
			while(current_other) {
				node* old_this = current_this;
				current_this = new node;
				current_this->data = current_other->data;
				if(old_this)
					old_this->next = current_this;
				else
					first = current_this;
				current_other = current_other->next;
			}

			last = current_this;
			last->next = nullptr;
			sz = other.sz;
		}

		return *this;
	}*/

	dlist<T>& operator=(dlist<T>&& other) {
		if(this != &other) {
			first = other.first;
			last = other.last;
			sz = other.sz;
			other.first = other.last = nullptr;
			other.sz = 0;
		}

		return *this;
	}

	bool operator==(const dlist<T>& other) const {
		if(sz != other.sz) return false;
		node* current_other = other.first;
		node* current_this = first;
		while(current_this) {
			if(current_this->data != current_other->data) return false;
			current_this = current_this->next;
			current_other = current_other->next;
		}

		return true;
	}

	inline bool operator!=(const dlist<T>& other) const {
		return !(*this == other);
	}

	// Iterators.
	class iterator {
	private:
		node* current;
		iterator(node* current) : current(current) {}
		friend class dlist;

	public:
		iterator() {}

		iterator(const iterator& other) : current(other.current) {}

		inline iterator& operator=(const iterator& other) {
			current = other.current;
			return *this;
		}

		inline bool operator==(const iterator& other) const {
			return (current == other.current);
		}

		inline bool operator!=(const iterator& other) const {
			return (current != other.current);
		}

		inline iterator& operator++() {
			current = current->next;
			return *this;
		}

		inline iterator operator++(int) {
			iterator ret = *this;
			current = current->next;
			return ret;
		}

		inline iterator& operator--() {
			current = current->prev;
			return *this;
		}

		inline iterator operator--(int) {
			iterator ret = *this;
			current = current->prev;
			return ret;
		}

		inline T& operator*() {
			return current->data;
		}
	};

	class const_iterator {
	private:
		node* current;
		const_iterator(node* current) : current(current) {}
		friend class dlist;

	public:
		const_iterator() {}

		const_iterator(const const_iterator& other) : current(other.current) {}

		inline const_iterator& operator=(const const_iterator& other) {
			current = other.current;
		}

		inline bool operator==(const const_iterator& other) const {
			return (current == other.current);
		}

		inline bool operator!=(const const_iterator& other) const {
			return (current != other.current);
		}

		inline const_iterator& operator++() {
			current = current->next;
			return *this;
		}

		inline const_iterator operator++(int) {
			const_iterator ret = *this;
			current = current->next;
			return ret;
		}

		inline const_iterator& operator--() {
			if(current)
				current = current->prev;
			else
				current = last;
			return *this;
		}

		inline const_iterator operator--(int) {
			const_iterator ret = *this;
			if(current)
				current = current->prev;
			else
				current = last;
			return ret;
		}

		inline const T& operator*() const {
			return current->data;
		}
	};

	inline iterator begin() {
		return iterator(first);
	}

	inline iterator end() {
		return iterator(nullptr);
	}

	inline const_iterator begin() const {
		return const_iterator(first);
	}

	inline const_iterator end() const {
		return const_iterator(nullptr);
	}

	inline const_iterator cbegin() const {
		return const_iterator(first);
	}

	inline const_iterator cend() const {
		return const_iterator(nullptr);
	}

	iterator insert(iterator it, T e) {
		// In case there are no elements (begin() == end()), end takes preference.
		if(it == end()) {
			push_back(e);
			return iterator(last);
		} else if(it == begin()) {
			push_front(e);
			return begin();
		} else {
			node* newnode = new node;
			newnode->data = e;
			newnode->next = it.current;
			newnode->prev = it.current->prev;
			it.current->prev->next = newnode;
			it.current->prev = newnode;
			++sz;
			return iterator(newnode);
		}
	}

	iterator remove(iterator it) {
		if(it == begin()) {
			pop_front();
			return begin();
		} else if(it == end()) {
			pop_back();
			return end();
		} else {
			node* ret = it.current->next;
			it.current->prev->next = it.current->next;
			it.current->next->prev = it.current->prev;
			delete it.current;
			return iterator(ret);
		}
	}
};

#endif

#ifndef LIST_H
#define LIST_H

#include <stddef.h>

template<typename T> class list {
private:
	struct node {
		T data;
		node* next;
	};

	node* first;
	node* last;
	size_t sz;

public:
	list() : first(nullptr), last(nullptr), sz(0) {}

	list(const list& other) {
		*this = other;
	}

	list(list&& other) {
		first = other.first;
		last = other.last;
		sz = other.sz;

		other.first = other.last = nullptr;
		other.sz = 0;
	}

	~list() {
		node* current = first;
		while(current) {
			node* next = current->next;
			delete current;
			current = next;
		}

		first = last = nullptr;
	}

	inline size_t size() const {
		return sz;
	}

	inline bool empty() const {
		return sz == 0;
	}

	// Back.
	void push_back(T e) {
		node* newnode = new node;
		newnode->data = e;
		newnode->next = nullptr;

		if(last) last->next = newnode;
		last = newnode;
		if(!sz) first = last;
		sz++;
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
	list<T>& operator=(const list<T>& other) {
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

			if(!current_this) {
				// List is empty.
				first = last = nullptr;
				sz = 0;
			} else {
				// first is already set.
				last = current_this;
				last->next = nullptr;
				sz = other.sz;
			}
		}

		return *this;
	}

	list<T>& operator=(list<T>&& other) {
		if(this != &other) {
			first = other.first;
			last = other.last;
			sz = other.sz;
			other.first = other.last = nullptr;
			other.sz = 0;
		}

		return *this;
	}

	bool operator==(const list<T>& other) const {
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

	inline bool operator!=(const list<T>& other) const {
		return !(*this == other);
	}

	// Iterators.
	class iterator {
	private:
		node* current;
		iterator(node* current) : current(current) {}
		friend class list;

	public:
		iterator() : current(nullptr) {}

		iterator(const iterator& other) : current(other.current) {}

		inline iterator& operator=(const iterator& other) {
			current = other.current;
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

		inline T& operator*() {
			return current->data;
		}
	};

	class const_iterator {
	private:
		node* current;
		const_iterator(node* current) : current(current) {}
		friend class list;

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

		const T& operator*() const {
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
};

#endif

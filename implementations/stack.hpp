#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <list>

template<typename T> class stack {
protected:	// Protected for "iterable_stack".
	list<T> data;

public:
	inline size_t size() const {
		return data.size();
	}

	inline bool empty() const {
		return data.size() == 0;
	}

	inline void push(T e) {
		data.push_front(e);
	}

	inline T& top() {
		return data.front();
	}

	inline const T& top() const {
		return data.front();
	}

	inline void pop() {
		data.pop_front();
	}

	inline bool operator==(const stack<T>& other) const {
		return data == other.data;
	}

	inline bool operator!=(const stack<T>& other) const {
		return data != other.data;
	}
};

#endif

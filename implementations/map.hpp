#ifndef MAP_HPP
#define MAP_HPP

#include <pair>
#include <AVL>

template<typename T, typename Q, typename Compare=less<pair<T, Q>>> class map : public AVL<pair<T, Q>, Compare> {
private:
	typedef AVL<pair<T, Q>, Compare> inh;
public:
	using inh::AVL;

	inline Q& operator[](const T& t) {
		auto x = inh::_find(pair<T, Q>(t, Q()));
		if(x.f) {
			return (*(x.s)).s;
		} else {
			auto n = inh::_insert(pair<T, Q>(t, Q()));
			return (*n).s;
		}
	}

	inline bool count(const T& t) {
		return inh::_find(pair<T, Q>(t, Q())).f;
	}
};

#endif

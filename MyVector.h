// My Own Vector
// Class: 	my_vector
// Author: 	Myroslav Zyblikevych
// Date: 12/06/2018

#pragma once
#include <cstdlib>

template <class Ttype>
class my_vector {
	const float COEFF_CAPACITY = 1.5;
	Ttype* lbound_;
	Ttype* ubound_;
	Ttype* end_;
	//methods for alloc
	void copy_elements(const my_vector& source);
	void allocate(const size_t new_capacity);
	void deallocate();
	void default_reserve();
public:
	class my_iterator;
	my_vector();
	my_vector(const my_vector &vec);
	my_vector(size_t s, Ttype element = Ttype());
	Ttype at(const size_t pos) const;
	Ttype front() const;
	Ttype back() const;
	my_iterator begin();
	my_iterator end();
	size_t size() const;
	size_t capacity() const;
	void reserve(size_t num);
	void resize(size_t num);
	void shrink_to_fit();
	bool empty() const;
	void clear();
	my_iterator erase(my_iterator pos);
	my_iterator erase(my_iterator pos1, my_iterator pos2);
	my_iterator insert(my_iterator pos, Ttype element);
	my_iterator insert(my_iterator pos, my_iterator first, my_iterator last);
	void push_back(Ttype element);
	void swap(my_vector &vec);
	void pop_back();
	Ttype& operator[](const size_t i);
	my_vector& operator=(const my_vector &vec);
	bool operator ==(my_vector &vec);
	bool operator !=(my_vector &vec);
	bool operator >(my_vector &vec);
	bool operator <(my_vector &vec);
	bool operator >=(my_vector &vec);
	bool operator <=(my_vector &vec);
	~my_vector();
	class my_iterator
	{
		Ttype* ptr_;
	public:
		my_iterator(Ttype* ptr = nullptr) : ptr_(ptr) {}
		Ttype* operator++();
		Ttype* operator--();
		Ttype* operator+(size_t num);
		Ttype* operator-(size_t num);
		ptrdiff_t operator-(my_iterator rh_itr);
		Ttype& operator* ();
		bool operator==(my_iterator itr);
		bool operator!=(my_iterator itr);
		bool operator<(my_iterator itr);
	};
};

//Privat methods for alloc
template <class Ttype>
void my_vector<Ttype>::copy_elements(const my_vector &source) {
	for (size_t i = 0; i < source.size(); ++i) {
		lbound_[i] = source.lbound_[i];
	}
	ubound_ = lbound_ + source.size();
}

template <class Ttype>
void my_vector<Ttype>::allocate(const size_t new_capacity) {
	deallocate();
	lbound_ = ubound_ = new Ttype[new_capacity];
	end_ = lbound_ + new_capacity;
}

template <class Ttype>
void my_vector<Ttype>::deallocate() {
	if (lbound_) {
		delete[] lbound_;
		lbound_ = ubound_ = end_ = nullptr;
	}
}

template <class Ttype>
void my_vector<Ttype>::default_reserve() {
	if (capacity()) {
		my_vector tmp(*this);
		allocate(capacity() == 1 ? 2 : (size_t)(capacity() * COEFF_CAPACITY));
		copy_elements(tmp);
	}
	else {
		allocate(2);
	}
}

//Methods implementation
template <class Ttype>
my_vector<Ttype>::my_vector() {
	lbound_ = ubound_ = end_ = nullptr;
}

template <class Ttype>
my_vector<Ttype>::my_vector(const my_vector &vec) {
	allocate(vec.capacity());
	copy_elements(vec);
}

template <class Ttype>
my_vector<Ttype>::my_vector(size_t s, Ttype element) {
	if (s) {
		allocate((size_t)(s * COEFF_CAPACITY));
		ubound_ = lbound_ + s;
		for (size_t i = 0; i < size(); ++i) 		{
			lbound_[i] = element;
		}
	}
	else {
		lbound_ = ubound_ = end_ = nullptr;
	}
}

template <class Ttype>
Ttype my_vector<Ttype>::at(const size_t pos) const {
	if (pos > size()) {
		throw std::out_of_range("Out of Range!!!");
	}
	return lbound_[pos];
}

template<class Ttype>
inline Ttype my_vector<Ttype>::front() const {
	return lbound_ ? *lbound_ : 0;
}

template<class Ttype>
inline Ttype my_vector<Ttype>::back() const {
	return lbound_ ? lbound_[size() - 1] : 0;
}

template<class Ttype>
inline my_vector<Ttype>::template my_iterator my_vector<Ttype>::begin() {
	return lbound_;
}

template<class Ttype>
inline  my_vector<Ttype>::template my_iterator my_vector<Ttype>::end() {
	return ubound_;
}

template<class Ttype>
inline size_t my_vector<Ttype>::size() const {
	return ubound_ - lbound_;
}

template<class Ttype>
inline size_t my_vector<Ttype>::capacity() const {
	return end_ - lbound_;
}

template<class Ttype>
void my_vector<Ttype>::reserve(size_t num) {
	if (num > capacity()) {
		my_vector tmp(*this);
		allocate(num);
		copy_elements(tmp);
	}
}

template<class Ttype>
void my_vector<Ttype>::resize(size_t num) {
	if (num > size()) {
		for (size_t i = 0; i < num - size() + i; ++i) {
			PushBack(Ttype());
		}
	}
	else {
		ubound_ = lbound_ + num;
	}
}

template<class Ttype>
void my_vector<Ttype>::shrink_to_fit() {
	my_vector tmp(*this);
	allocate(size());
	copy_elements(tmp);
}

template<class Ttype>
inline bool my_vector<Ttype>::empty() const {
	return lbound_ == ubound_;
}

template<class Ttype>
inline void my_vector<Ttype>::clear() {
	ubound_ = lbound_;
}

template<class Ttype>
my_vector<Ttype>::template my_iterator my_vector<Ttype>::erase(my_iterator pos) {
	if (pos < end() && (my_iterator)(begin() - 1) < pos) {
		--ubound_;
		for (auto it = pos; it < end(); ++it) {
			*it = *(it + 1);
		}
	}
	else {
		throw std::out_of_range("Iterator Out of Range!!!");
	}
	return pos;
}

template<class Ttype>
my_vector<Ttype>::template my_iterator my_vector<Ttype>::erase(my_iterator pos1, my_iterator pos2)
{
	if (pos2 - pos1 <= (ptrdiff_t)size() && pos2 < end() + 1 && (my_iterator)(begin() - 1) < pos1) {
		ubound_ -= (pos2 - pos1);
		for (auto it = pos1; it < end(); ++it) {
			*it = *(it + (pos2 - pos1));
		}
	}
	else {
		throw std::out_of_range("Iterator Out of Range!!!");
	}
	return pos2;
}

template <class Ttype>
my_vector<Ttype>::template my_iterator my_vector<Ttype>::insert(my_iterator pos, Ttype element) {
	if ((pos < end() + 1 && (my_iterator)(begin() - 1) < pos) || !capacity()) {
		if (capacity() < (size() + 1)) {
			ptrdiff_t p = pos - begin();
			default_reserve();
			pos = begin() + p;
		}
		++ubound_;
		for (auto it = end() - 1; pos < it; --it) {
			*it = *(it - 1);
		}
		*pos = element;
	}
	else {
		throw std::out_of_range("Iterator Out of Range!!!");
	}
	return pos;
}

template<class Ttype>
my_vector<Ttype>::template my_iterator my_vector<Ttype>::insert(my_iterator pos, my_iterator first, my_iterator last) {
	if ((pos < end() + 1 && (my_iterator)(begin() - 1) < pos) || !capacity()) {
		if (capacity() < (size() + (last - first))) {
			ptrdiff_t p = pos - begin();
			reserve(size() + (last - first) + 1);
			pos = begin() + p;
		}

		ubound_ += (last - first);
		for (auto it = end() - 1; pos < it; --it) {
			*it = *(it - (last - first));
		}
		
		int count(0);
		for (auto it = pos; it < pos + (last - first); ++it, ++count) {
			*it = *(first + count);
		}
	}
	else {
		throw std::out_of_range("Iterator Out of Range!!!");
	}
	return pos;
}

template <class Ttype>
void my_vector<Ttype>::push_back(Ttype element) {
	if (ubound_ == end_) {
		default_reserve();
	}
	lbound_[size()] = element;
	ubound_ = lbound_ + size() + 1;
}

template<class Ttype>
void my_vector<Ttype>::swap(my_vector &vec){
	my_vector tmp(*this);
	*this = vec;
	vec = tmp;
}

template<class Ttype>
void my_vector<Ttype>::pop_back() {
	--ubound_;
}

template <class Ttype>
Ttype& my_vector<Ttype>::operator[](const size_t i) {
	return lbound_[i];
}

template <class Ttype>
my_vector<Ttype>& my_vector<Ttype>::operator=(const my_vector& rh_vec) {
	if (this == &rh_vec) return *this;
	if (capacity() < rh_vec.size()) {
		allocate((size_t)(rh_vec.size() * COEFF_CAPACITY));
	}
	copy_elements(rh_vec);
	return *this;
}

template <class Ttype>
bool my_vector<Ttype>::operator==(my_vector &vec) {
	if (size() != vec.size()) return false;
	for (int i = 0; i < size(); ++i) {
		if (lbound_[i] != vec[i]) return false;
	}
	return true;
}

template<class Ttype>
inline bool my_vector<Ttype>::operator!=(my_vector& vec) {
	return !(*this == vec);
}

template<class Ttype>
inline bool my_vector<Ttype>::operator>(my_vector& vec) {
	return size() > vec.size();
}

template<class Ttype>
inline bool my_vector<Ttype>::operator<(my_vector& vec) {
	return size() < vec.size();
}

template<class Ttype>
inline bool my_vector<Ttype>::operator>=(my_vector& vec) {
	return size() >= vec.size();
}

template<class Ttype>
inline bool my_vector<Ttype>::operator<=(my_vector& vec) {
	return size() <= vec.size();
}

template <class Ttype>
my_vector<Ttype>::~my_vector() {
	deallocate();
}

// Iterator methods
template<class Ttype>
inline Ttype * my_vector<Ttype>::my_iterator::operator++() {
	return ++ptr_;
}

template<class Ttype>
inline Ttype* my_vector<Ttype>::my_iterator::operator--() {
	return --ptr_;
}

template<class Ttype>
inline Ttype* my_vector<Ttype>::my_iterator::operator+(size_t num) {
	return ptr_ + num;
}

template<class Ttype>
inline Ttype* my_vector<Ttype>::my_iterator::operator-(size_t num) {
	return ptr_ - num;
}

template<class Ttype>
inline ptrdiff_t my_vector<Ttype>::my_iterator::operator-(my_iterator rh_itr) {
	return ptr_ - rh_itr.ptr_;
}

template<class Ttype>
inline Ttype& my_vector<Ttype>::my_iterator::operator*() {
	return *ptr_;
}

template<class Ttype>
inline bool my_vector<Ttype>::my_iterator::operator==(my_iterator itr) {
	return itr.ptr_ == ptr_;
}

template<class Ttype>
inline bool my_vector<Ttype>::my_iterator::operator!=(my_iterator itr) {
	return itr.ptr_ != ptr_;
}

template<class Ttype>
inline bool my_vector<Ttype>::my_iterator::operator<(my_iterator itr) {
	return ptr_ < itr.ptr_;
}


// additional function non-members
template <class Ttype>
void rand_int_init(my_vector<Ttype>& v, int rand_range) {
	for (int i = 0; i < v.size(); ++i) {
		v[i] = rand() % rand_range;
	}
}

template <class Ttype>
void rand_int_init(my_vector<Ttype>& v, int l_rand_range, int u_rand_range) {
	for (int i = 0; i < v.size(); ++i) {
		v[i] = rand() % (u_rand_range - l_rand_range) + l_rand_range;
	}
}
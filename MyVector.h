// My Own Vector
// Class: 	MyVector
// Author: 	Myroslav Zyblikevych
// Date: 12/06/2018

#pragma once
#include <cstdlib>

template <class Ttype>
class MyVector {
	const float COEFF_CAPACITY = 1.5;
	Ttype* lbound_;
	Ttype* ubound_;
	Ttype* end_;

	size_t size_;
	size_t capacity_;

	void CopyElements(const MyVector& source);
	void Allocate(const size_t new_capacity);
	void Deallocate();
	void DefaultReserve();
public:
	class MyIterator;
	MyVector();
	MyVector(const MyVector &vec);
	MyVector(size_t s, Ttype element = Ttype());
	Ttype At(const size_t pos) const;
	Ttype Front() const;
	Ttype Back() const;
	MyIterator begin() { return lbound_; }
	MyIterator end() { return ubound_; }
	void RandIntInit(int RandRange);
	void RandIntInit(int LRandRange, int URandRange);
	size_t Size() const;
	size_t Capacity() const;
	void Reserve(size_t num);
	void Resize(size_t num);
	void ShrinkToFit();
	bool Empty() const;
	void Clear();
	void Erase(size_t pos);
	void Erase(size_t pos1, size_t pos2);
	void Insert(size_t pos, Ttype element);
	void Insert(size_t pos, MyVector &vec);
	void PushBack(Ttype element);
	void PushBack(MyVector &vec);
	void Swap(MyVector &vec);
	void PopBack() { --size_; }
	Ttype& operator[](const size_t i);
	MyVector& operator=(const MyVector &vec);
	bool operator ==(MyVector &vec);
	bool operator !=(MyVector &vec) { return !(*this == vec); }
	bool operator >(MyVector &vec) { return size_ > vec.Size(); }
	bool operator <(MyVector &vec) { return size_ < vec.Size(); }
	bool operator >=(MyVector &vec) { return size_ >= vec.Size(); }
	bool operator <=(MyVector &vec) { return size_ <= vec.Size(); }
	~MyVector();
	class MyIterator
	{
		Ttype* ptr;
	public:
		MyIterator() { ptr = nullptr; }
		MyIterator(Ttype* num) : ptr(num) {}
		~MyIterator() { if (ptr != nullptr) delete[] ptr; }
		Ttype& operator ++() { return *(ptr++); }
		Ttype& operator --() { return *(ptr--); }
		Ttype& operator ++(int) { return *(++ptr); }
		Ttype& operator --(int) { return *(--ptr); }
		Ttype& operator +(int num) { return *ptr + num; }
		Ttype& operator -(int num) { return *ptr - num; }
		Ttype& operator *() { return *ptr; }
		bool operator ==(MyIterator itr) { return itr.ptr == ptr; }
		bool operator !=(MyIterator itr) { return itr.ptr != ptr; }
	};
};

template <class Ttype>
void MyVector<Ttype>::CopyElements(const MyVector &source) {
	for (size_t i = 0; i < source.Size(); ++i) {
		lbound_[i] = source.lbound_[i];
	}
	ubound_ = lbound_ + source.Size();
}

template <class Ttype>
void MyVector<Ttype>::Allocate(const size_t new_capacity) {
	Deallocate();
	lbound_ = new Ttype[new_capacity];
	end_ = lbound_ + new_capacity;
}

template <class Ttype>
void MyVector<Ttype>::Deallocate() {
	if (lbound_) {
		delete[] lbound_;
		lbound_ = ubound_ = end_ = nullptr;
	}
}

template <class Ttype>
void MyVector<Ttype>::DefaultReserve() {
	MyVector tmp(*this);
	Allocate((size_t)(Capacity() * COEFF_CAPACITY) <= 1 ? 2 : (size_t)(Capacity() * COEFF_CAPACITY));
	CopyElements(tmp);
}

//--------Methods-----------------------------

template <class Ttype>
MyVector<Ttype>::MyVector()
{
	lbound_ = ubound_ = end_ = nullptr;
}

template <class Ttype>
MyVector<Ttype>::MyVector(const MyVector &vec) {
	if (Capacity() < vec.Size()) {
		Allocate(vec.Capacity());
	}
	CopyElements(vec);
}

template <class Ttype>
MyVector<Ttype>::MyVector(size_t s, Ttype element) {
	if (s) {
		Allocate((size_t)(s * COEFF_CAPACITY));
		ubound_ = lbound_ + s;
		for (int i = 0; i < Size(); ++i)
		{
			lbound_[i] = element;
		}
	}
	else {
		lbound_ = ubound_ = end_ = nullptr;
	}
}

template <class Ttype>
Ttype MyVector<Ttype>::At(const size_t pos) const {
	if (pos > Size()) {
		throw std::out_of_range("Out of Range!!!");
	}
	return lbound_[pos];
}

template<class Ttype>
inline Ttype MyVector<Ttype>::Front() const {
	return lbound_ ? *lbound_ : 0;
}

template<class Ttype>
inline Ttype MyVector<Ttype>::Back() const {
	return lbound_ ? lbound_[Size() - 1] : 0;
}

template <class Ttype>
void MyVector<Ttype>::RandIntInit(int RandRange) {
	for (int i = 0; i < Size(); ++i) {
		lbound_[i] = rand() % RandRange;
	}
}

template <class Ttype>
void MyVector<Ttype>::RandIntInit(int LRandRange, int URandRange) {
	for (int i = 0; i < Size(); ++i) {
		lbound_[i] = rand() % (URandRange - LRandRange) + LRandRange;
	}
}

template<class Ttype>
inline size_t MyVector<Ttype>::Size() const {
	return ubound_ - lbound_;
}

template<class Ttype>
inline size_t MyVector<Ttype>::Capacity() const {
	return end_ - lbound_;
}

template<class Ttype>
void MyVector<Ttype>::Reserve(size_t num) {
	if (num > Capacity()) {
		MyVector tmp(*this);
		Allocate(num);
		CopyElements(tmp);
	}
}

template<class Ttype>
void MyVector<Ttype>::Resize(size_t num) {
	if (num > Size()) {
		for (size_t i = 0; i < num - Size() + i; ++i) {
			PushBack(Ttype());
		}
	}
	else {
		ubound_ = lbound_ + num;
	}
}

template<class Ttype>
void MyVector<Ttype>::ShrinkToFit() {
	MyVector tmp(*this);
	Allocate(Size());
	CopyElements(tmp);
}

template<class Ttype>
inline bool MyVector<Ttype>::Empty() const {
	return lbound_ == ubound_;
}

template<class Ttype>
inline void MyVector<Ttype>::Clear() {
	ubound_ = lbound_;
}

template <class Ttype>
void MyVector<Ttype>::Erase(size_t pos) {
	if (pos < Size()) {
		--ubound_;
		for (int i = pos; i < Size(); ++i) {
			lbound_[i] = lbound_[i + 1];
		}
	}
}

template<class Ttype>
void MyVector<Ttype>::Erase(size_t pos1, size_t pos2) {
	if (pos1 > pos2) {
		throw std::exception("pos2 must be >= pos1!!!");
	}
	if (pos1 == pos2) {
		Erase(pos1);
	}
	else if (pos2 <= Size()) {
		ubound_ -= (pos2 - pos1);
		for (int i = pos1; i < Size(); ++i) {
			lbound_[i] = lbound_[i + pos2 - pos1];
		}
	}
}

template <class Ttype>
void MyVector<Ttype>::Insert(size_t pos, Ttype element)
{
	if (pos < size_ + 1)
	{
		if (capacity_ < (size_ + 1))
		{
			DefaultReserve();
			++size_;
			for (int i = (size_ - 1); i > pos; --i)
			{
				lbound_[i] = lbound_[i - 1];
			}
			lbound_[pos] = element;
		}
		else
		{
			++size_;
			for (int i = (size_ - 1); i > pos; --i)
			{
				lbound_[i] = lbound_[i - 1];
			}
			lbound_[pos] = element;
		}
	}
}

template<class Ttype>
void MyVector<Ttype>::Insert(size_t pos, MyVector &vec)
{
	if (pos < size_ + 1)
	{
		if (capacity_ < (size_ + vec.Size()))
		{
			Reserve(vec.Size());
			size_ += vec.Size();
			for (int i = (size_ - 1); i > pos; --i)
			{
				lbound_[i] = lbound_[i - vec.Size()];
			}
			for (int i = pos; i < pos + vec.Size(); ++i)
			{
				lbound_[i] = vec[i - pos];
			}
		}
		else
		{
			size_ += vec.Size();
			for (int i = (size_ - 1); i > pos; --i)
			{
				lbound_[i] = lbound_[i - vec.Size()];
			}
			for (int i = pos; i < pos + vec.Size(); ++i)
			{
				lbound_[i] = vec[i - pos];
			}
		}
	}
}

template <class Ttype>
void MyVector<Ttype>::PushBack(Ttype element) {
	if (ubound_ == end_) {
		DefaultReserve();
	}
	lbound_[Size()] = element;
	ubound_ = lbound_ + Size() + 1;
}

template <class Ttype>
void MyVector<Ttype>::PushBack(MyVector &vec)
{
	Insert(size_, vec);
}

template<class Ttype>
void MyVector<Ttype>::Swap(MyVector &vec)
{
	MyVector tmp(*this);
	*this = vec;
	vec = tmp;
}

template <class Ttype>
Ttype& MyVector<Ttype>::operator[](const size_t i) {
	return lbound_[i];
}

template <class Ttype>
MyVector<Ttype>& MyVector<Ttype>::operator=(const MyVector& rh_vec) {
	if (this == &rh_vec) return *this;
	if (Capacity() < rh_vec.Size()) {
		Allocate((size_t)(rh_vec.Size() * COEFF_CAPACITY));
	}
	CopyElements(rh_vec);
	return *this;
}

template <class Ttype>
bool MyVector<Ttype>::operator==(MyVector &vec) {
	if (Size() != vec.Size()) return false;
	for (int i = 0; i < Size(); ++i) {
		if (lbound_[i] != vec[i]) return false;
	}
	return true;
}

template <class Ttype>
MyVector<Ttype>::~MyVector() {
	Deallocate();
}

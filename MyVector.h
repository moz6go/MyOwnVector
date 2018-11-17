// My Own Vector
// Class: 	MyVector
// Aythor: 	Myroslav Zyblikevych
// Date: 12/06/2018


#pragma once
#include <cstdlib>

namespace MyVectorNameSpace
{
	template <class Ttype>
	class MyVector
	{
		const float COEFF_CAPACITY = 1.5;
		Ttype* arr;
		size_t size;
		size_t capacity;
		void CopyVector(MyVector &vec1, MyVector &vec2);
		void DeleteMem();
		void NewMem(MyVector &vec);
		void DefaultReserve(MyVector &vec);
	public:
		class MyIterator;
		MyVector();
		MyVector(MyVector &vec);
		MyVector(size_t s, Ttype element = 0);
		Ttype At(size_t pos);
		Ttype Front() { return arr[0]; }
		Ttype Back() { return arr[size - 1]; }
		MyIterator begin() { return arr; }
		MyIterator begin(MyVector &vec) { return vec.arr; }
		MyIterator end() { return arr + size; }
		MyIterator end(MyVector &vec) { return vec.arr + vec.size; }
		void RandInit(int RandRange);
		void RandInit(int LRandRange, int URandRange);
		size_t Size() { return size; }
		size_t Capacity() { return capacity; }
		void Reserve(size_t num);
		void Resize(size_t num);
		void ShrinkToFit();
		bool Empty() { return size == 0; }
		void Clear() { size = 0; }
		void Erase(size_t pos);
		void Erase(size_t pos1, size_t pos2);
		void Insert(size_t pos, Ttype element);
		void Insert(size_t pos, MyVector &vec);
		void PushBack(Ttype element);
		void PushBack(MyVector &vec);
		void Swap(MyVector &vec);
		void PopBack() { --size; }
		Ttype& operator[](size_t i);
		MyVector& operator=(MyVector &vec);
		bool operator ==(MyVector &vec);
		bool operator !=(MyVector &vec) { return !(*this == vec); }
		bool operator >(MyVector &vec) { return size > vec.size; }
		bool operator <(MyVector &vec) { return size < vec.size; }
		bool operator >=(MyVector &vec) { return size >= vec.size; }
		bool operator <=(MyVector &vec) { return size <= vec.size; }
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
	void MyVector<Ttype>::CopyVector(MyVector &vec1, MyVector &vec2)
	{
		for (int i = 0; i < vec2.size; ++i)
		{
			vec1.arr[i] = vec2.arr[i];
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::DeleteMem()
	{
		if (arr)
		{
			delete[] arr;
			arr = nullptr;
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::NewMem(MyVector &vec)
	{
		DeleteMem();
		arr = new Ttype[capacity = vec.capacity];
	}

	template <class Ttype>
	void MyVector<Ttype>::DefaultReserve(MyVector &vec)
	{
		MyVector tmp(vec);
		if (vec.capacity > 0)
		{
			tmp.capacity = vec.capacity *= COEFF_CAPACITY;
		}
		else
		{
			tmp.capacity = vec.capacity = 2;
		}
		NewMem(vec);
		vec = tmp;
	}

	//--------Methods-----------------------------

	template <class Ttype>
	MyVector<Ttype>::MyVector()
	{
		arr = nullptr;
		size = 0;
		capacity = 0;
	}

	template <class Ttype>
	MyVector<Ttype>::MyVector(MyVector &vec)
	{
		size = vec.size;
		if (capacity < size)
			NewMem(vec);
		CopyVector(*this, vec);
	}

	template <class Ttype>
	MyVector<Ttype>::MyVector(size_t s, Ttype element)
	{
		size = s;
		capacity = s * COEFF_CAPACITY;
		arr = new Ttype[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = element;
		}
	}

	template <class Ttype>
	Ttype MyVector<Ttype>::At(size_t pos)
	{
		if (size <= pos)
		{
			throw std::out_of_range("Out of Range!!!");
		}
		return arr[pos];
	}

	template <class Ttype>
	void MyVector<Ttype>::RandInit(int RandRange)
	{
		for (int i = 0; i < size; ++i)
		{
			arr[i] = rand() % RandRange;
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::RandInit(int LRandRange, int URandRange)
	{
		for (int i = 0; i < size; ++i)
		{
			arr[i] = rand() % (URandRange - LRandRange) + LRandRange;
		}
	}

	template<class Ttype>
	void MyVector<Ttype>::Reserve(size_t num)
	{
		MyVector tmp(*this);
		tmp.capacity = capacity += num;
		NewMem(*this);
		*this = tmp;
	}

	template<class Ttype>
	void MyVector<Ttype>::Resize(size_t num)
	{
		for (int i = 0; i < num; ++i)
			PushBack(Ttype());
	}

	template<class Ttype>
	void MyVector<Ttype>::ShrinkToFit()
	{
		MyVector tmp(*this);
		capacity = size;
		NewMem(*this);
		*this = tmp;
	}

	template <class Ttype>
	void MyVector<Ttype>::Erase(size_t pos)
	{
		if (pos < size)
		{
			--size;
			for (int i = pos; i < size; ++i)
			{
				arr[i] = arr[i + 1];
			}
		}
	}

	template<class Ttype>
	void MyVector<Ttype>::Erase(size_t pos1, size_t pos2)
	{
		if (pos1 > pos2)
		{
			throw std::exception("pos2 must be >= pos1!!!");
		}
		if (pos1 == pos2)
		{
			Erase(pos1);
		}
		else if (pos2 <= size)
		{
			size -= (pos2 - pos1);
			for (int i = pos1; i < size; ++i)
			{
				arr[i] = arr[i + pos2 - pos1];
			}
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::Insert(size_t pos, Ttype element)
	{
		if (pos < size + 1)
		{
			if (capacity < (size + 1))
			{
				DefaultReserve(*this);
				++size;
				for (int i = (size - 1); i > pos; --i)
				{
					arr[i] = arr[i - 1];
				}
				arr[pos] = element;
			}
			else
			{
				++size;
				for (int i = (size - 1); i > pos; --i)
				{
					arr[i] = arr[i - 1];
				}
				arr[pos] = element;
			}
		}
	}

	template<class Ttype>
	void MyVector<Ttype>::Insert(size_t pos, MyVector &vec)
	{
		if (pos < size + 1)
		{
			if (capacity < (size + vec.size))
			{
				Reserve(vec.size);
				size += vec.size;
				for (int i = (size - 1); i > pos; --i)
				{
					arr[i] = arr[i - vec.size];
				}
				for (int i = pos; i < pos + vec.size; ++i)
				{
					arr[i] = vec.arr[i - pos];
				}
			}
			else
			{
				size += vec.size;
				for (int i = (size - 1); i > pos; --i)
				{
					arr[i] = arr[i - vec.size];
				}
				for (int i = pos; i < pos + vec.size; ++i)
				{
					arr[i] = vec.arr[i - pos];
				}
			}
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::PushBack(Ttype element)
	{
		if (capacity < (size + 1))
		{
			DefaultReserve(*this);
			arr[size++] = element;
		}
		else
		{
			arr[size++] = element;
		}
	}

	template <class Ttype>
	void MyVector<Ttype>::PushBack(MyVector &vec)
	{
		Insert(size, vec);
	}

	template<class Ttype>
	void MyVector<Ttype>::Swap(MyVector &vec)
	{
		MyVector tmp(*this);
		*this = vec;
		vec = tmp;
	}

	template <class Ttype>
	Ttype& MyVector<Ttype>::operator[](size_t i)
	{
		return arr[i];
	}

	template <class Ttype>
	MyVector<Ttype>& MyVector<Ttype>::operator=(MyVector &vec)
	{
		if (this == &vec) return *this;
		size = vec.size;
		if (capacity < size)
			NewMem(vec);
		CopyVector(*this, vec);
		return *this;
	}

	template <class Ttype>
	bool MyVector<Ttype>::operator==(MyVector &vec)
	{
		if (size != vec.size) return false;
		for (int i = 0; i < size; ++i)
		{
			if (arr[i] != vec.arr[i]) return false;
		}
		return true;
	}

	template <class Ttype>
	MyVector<Ttype>::~MyVector()
	{
		DeleteMem();
	}
}

#ifndef _MY_ARRAY_H_
#define _MY_ARRAY_H_
#include <cassert>

template<class T>
class MyArray
{
public:
	MyArray(int sz = 50);
	MyArray(const MyArray<T>& a);
	~MyArray();
	MyArray<T>& operator=(const MyArray<T>&rhs);
	T& operator[](int i);
	const T& operator[](int i)const;
	operator T* ();
	operator const T* () const;
	int getSize() const;
	void resize(int sz);

private:
	T* list;
	int size;
};

template<class T>
MyArray<T>::MyArray(int sz)
{
	assert(sz >= 0);
	size = sz;
	list = new T[size];

}

template<class T>
MyArray<T>::~MyArray()
{
	delete[] list;
}

template<class T>
MyArray<T>::MyArray(const MyArray<T>& a)
{
	size = a.size;
	list = new T[size];
	for (int i = 0; i < size; i++)
	{
		list[i] = a.list[i];
	}

}

template<class T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T>& rhs)
{
	if (&rhs != this)
	{
		if (size != rhs.getSize())
		{
			delete[] list;
			size = rhs.getSize();
			list = new T[size];
		}
		for (int i = 0; i < size; i++)
		{
			list[i] = rhs.list[i];
		}

	}
	return *this;

}

template<class T>
T& MyArray<T>::operator[](int n)
{
	assert(n >= 0 && n < size);
	return list[n];
}

template<class T>
const T& MyArray<T>::operator[](int n)const
{
	assert(n >= 0 && n < size);
	return list[n];
}

template<class T>
MyArray<T>::operator T* ()
{
	return list;
}

template<class T>
MyArray<T>::operator const T* ()const
{
	return list;
}

template<class T>
int MyArray<T>::getSize() const
{
	return size;
}

template<class T>
void MyArray<T>::resize(int sz)
{
	assert(sz >= 0);
	if (sz==size)
	{
		return;
	}
	T* newList = new T[sz];
	int n = (sz < size) ? sz : size;
	for (int i = 0; i < n; i++)
	{
		newList[i] = list[i];
	}
	delete[] list;
	list = newList;
	size = sz;
}


#endif // !_MY_ARRAY_H_


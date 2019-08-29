// Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "malloc.h"
#include <iostream>
#include <new>


template<typename T>
T* helper_array_alloc(int size)
{
	int x = sizeof(T);
	void* vptr = malloc(x * size);
	T* tptr = reinterpret_cast<T*>(vptr);
	if (tptr)
		for (int i = 0; i < size; ++i){
			//tptr = NULL;
			new(tptr + i) T;

		}
			
	return tptr;
}

int main()
{
	int a; 
	int *ptr = helper_array_alloc<int>(10);

	std::cout << *ptr;
    return 0;
}


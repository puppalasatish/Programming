// find_in_2d_array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int arr[][3] = {1,21,34,46,59,62,71,84,90};

bool find(int ele) {
	int ro = 3, co = 3, size = ro * co;
	int l = 0, r = size-1;
	
	while (r - l >= 0) {	
	int mid = (l + r) / 2;
	if (ele == arr[mid/3][mid%3]) return true;
	else if (ele < arr[mid / ro][mid % co]) r = mid - 1;
	else if (ele > arr[mid / ro][mid % co]) l = mid + 1;
	}

	return false;
}


int main()
{
	int x;
	std::cout << "Enter X   .... ";
	std::cin >> x;
	if (find(x)) std::cout << "found ........\n";
	else std::cout << "**** not found ........\n";
    return 0;
}


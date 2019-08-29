// dupinarray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "set"
#include <cmath>

using namespace std;

int arr[] = { 1,21,34,46,59,900,71,84,90 };

bool contindup() {
	set <int> myset;
	std::set<int>::iterator it;
	std::pair<std::set<int>::iterator, bool> ret;
	for (int i = 0; i < 9; i++)
	{
		ret = myset.insert(arr[i]);
		if (ret.second == false) return false;
	}
	return true;
}

int arr1[] = { 9,2,3,4,5,6,7,8,9 };


bool contindup1() {
	 
	for (int i = 0; i < 9; i++) {
		int temp = abs(arr1[i]);
		if (arr1[temp] < 0) return false;
		else arr1[temp] *= -1;
	}
	return true;
}
int main()
{
	
	if (!contindup1()) 
		cout << "found \n";
	else cout << "not found \n";
	
    return 0;
}


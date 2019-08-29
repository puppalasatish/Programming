// twosum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "set"
#include <cmath>

using namespace std;

int arr[] = { 1,21,34,46,59,62,71,84,90};

bool find2sum1(int sum) {
	int l = 0, r = 8;

	while (r - l > 0) {
		int mysum = arr[l] + arr[r];
		if (mysum == sum) return true;
		else if (mysum > sum) r--;
		else l++;
	}

	return false;
}


bool find2sum(int sum) {
	set<int> myset;
	set<int>::iterator it;
	pair <set<int>::iterator, bool> ret;
	myset.insert(arr[0]);
	for (int i = 1; i < 9; i++) {
		it = myset.find(sum - arr[i]);
		if (it == myset.end()) myset.insert(arr[i]);
		else return true;
	}
	return false;
 }

int main()
{
	cout << "sum isss --> " << find2sum1(96)  << endl;
    return 0;
}


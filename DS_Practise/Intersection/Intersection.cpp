// Intersection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "set"
#include <cmath>

using namespace std;

int A1[] = { 1,5,3,6,2,7 }; int l1 = 6;
int A2[] = { 9,4,3,5,7 };   int l2 = 5;

std::set<int> intersection() {
	set <int> myset;
	set <int> mysetret;
	set <int> ::iterator it;
	pair<set <int> ::iterator, bool> ret;

	for (int i = 0; i < l1; i++) myset.insert(A1[i]);

	for (int j = 0; j < l2; j++)
	{
		ret = myset.insert(A2[j]);
		if (ret.second == false) mysetret.insert(A2[j]);
	}

	return mysetret;
}

int main()
{
	set <int> myset = intersection();

	set<int>::iterator it = myset.begin();

	while (it != myset.end())
	{
		cout << "\n -->" << *it;
		it++;
	}

	cout << endl;

    return 0;
}


// Adhoc_countzeros.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "set"
#include <cmath>

using namespace std;
int len = 17;
int arr[] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int countzeros() {
	int i;
	for (i = 0; i < len ; i++)
		if (arr[i] == 1) 
			 break;
		
	return i;
}


int countzeros1() {
	int l = 0 , r = len, m; 
	while (r-l > 0) {
		m = (l+r) / 2;
		if (arr[m] == 0)
			l = m + 1;
		else
			r = m;
	}
	return l;
}

int main()
{
	cout << "Zeros are ... : " << countzeros1() << endl;
    return 0;
}


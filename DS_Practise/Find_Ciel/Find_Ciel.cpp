// Find_Ciel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int arr[] = { 22,25,48,64,75,89,90,103 };

//Ciel of 48 is 64 . ciell of 34 is 48
 
int find_ciel(int find_n) {
	for (int i = 0; i < 8; i++) {
		if (find_n > arr[i])
			i++;
		else if (find_n < arr[i]) return arr[i];
		else return arr[i+1];
	}

	return 0;

}

int find_ciel2(int find_n) {
	int li = 0,  ri = 7 ;
	int mi;
	while (ri - li > 0) {
		mi = li + (ri - li) / 2;
		if (find_n > arr[mi])
			li = mi + 1;
		else if (find_n <= arr[mi])
			ri = mi;
	}	

	std::cout << li << "   " << ri  << "   "<< mi << "  " << std::endl;
	if (li == 7 && find_n > arr[li]) return 0;
	else if (find_n == arr[li]) return arr[li + 1];
	else return arr[li];

	return 0;

}

int main()
{
	int num;
	std::cout << "Enter any number ";
	std::cin >> num;
	int res = 0;
	res = find_ciel2(num);

	if (!res) std::cout << "not found" << std::endl;
	else std::cout << "ciel --> " << res << std::endl; 
	
    return 0;
}


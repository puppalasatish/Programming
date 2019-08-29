// Recursion_sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void print(int n, bool flag,bool exit=false) {

	if (exit) return;

	if (flag == false)
	{
		std::cout << n << " ";
		if (n == 0)
			print(n + 5, true);
		else
			print(n - 5, false);
	}

	if (flag == true) {
		std::cout << n << " ";
		if(n == 15)
		print(n, true,true);
		else 
		print(n+5, true);
	}

	
}

int fib(int n) {
	if (n == 0) return n;
	if (n == 1) return 1;
	return fib(n - 1) + fib(n - 2);
}


int fib2(int n,int a,int b) {
	if (n == 0) return a;
	if (n == 1) return b;
	return fib2(n-1,b,a+b);
}
void print1(int n) {
	if (n == 1) return;

	std::cout << n << " ";

	print1(n-1);
}

void print2(int n) {
	if (n == 1) return;

	

	print2(n - 1);

	std::cout << n << " ";
}
int main()
{
//	print2(15);
	std::cout << "\n " << fib2(45,0,01);
//	std::cout << "\n " << fib(45);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// Stack_Custom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include <vector>
#include <iostream>
#include <string>

using namespace std;


/*
* Complete the function below.
*/

class mystack {
	stack <int> customstack;
	vector <pair<int, int>> customstack1;
public:
	void push(int input);
	void pop();
	void incr(int numofele, int incrby);
	void display();
};
void mystack::push(int ele) {
	customstack.push(ele);
	std::pair<int, int> myPair;
	myPair.first = ele;
	myPair.second = 0;
	customstack1.push_back(myPair);
	display();
}
void mystack::pop() {
	customstack.pop();
	customstack1.pop_back();
	display();
}

void mystack::incr(int numofele, int incrby) {
	int j = 0;
	int size = customstack1.size();
	while (size > 0) {
		size--;
		j++;
		customstack1[size].second += incrby;		
		if (j > numofele)
			break;
	}
	display();
}

void mystack::display() {
	if (customstack.empty())
		std::cout << "EMPTY" << std::endl;
	else {
		pair <int, int> myoai = customstack1.back();
		cout << myoai.first + myoai.second << endl;
	}
}

void superStack(vector <string> operations) {
	mystack testStack;
	for (auto i = operations.begin(); i < operations.end(); i++)
	{
		string tempString = *i;
		if (tempString.find("push") != tempString.npos)
		{
			auto itr = tempString.find(" ");
			int ele = stoi(tempString.substr(itr + 1, tempString.npos));
			testStack.push(ele);

		}
		else if (tempString.find("pop") != tempString.npos)
		{
			testStack.pop();

		}
		else
		{
			auto itr = tempString.find(" ");
			string str1 = tempString.substr(itr + 1, tempString.npos);
			auto itr2 = str1.find(" ");
			int numofele = stoi(str1.substr(0, itr2));
			int incrby = stoi(str1.substr(itr2 + 1, str1.npos));
			testStack.incr(numofele, incrby);
		}
	}
}
int main()
{
	vector <string> myv;// ("push 1", "pop", "push 2", "push 4", "incr 2 1", "incr 3 2", "pop");

	myv.push_back("push 1");
	myv.push_back("pop");
	myv.push_back("push 2");
	myv.push_back("incr 1 10");
	myv.push_back("incr 1 20");
	myv.push_back("push 4");
	myv.push_back("incr 2 1");
	myv.push_back("incr 3 2");
	myv.push_back("pop");

	superStack(myv);

}


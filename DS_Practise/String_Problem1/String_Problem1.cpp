// String_Problem1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stack>
#include<stdlib.h> 
using namespace std;

class Solution {
public:
	string decodeString(string s) {		
		string substrng;
		string &out = substrng;
		return auxdecodeString(s,out);
	}

	string auxdecodeString(string s, string out) {
		string s1;
		
		if (s.find("[") != s.npos) {
			auto pos = s.find("[");
			string temp = s.substr(0, pos);
			cout << temp << endl;
			auto pos2 = s.find("]");
			string temp1 = s.substr(pos + 1, pos2 - 1 - pos);
			cout << temp1 << endl;
			s1 = generatestring(stoi(temp), temp1);
			s = s.substr(pos2 + 1, s.npos);
			cout << s << "   send recursive " << s1 <<endl;
			cout << out << endl;
			return out + auxdecodeString(s,s1);
		}
			return out;

	}
	string generatestring(int x, string ch) {
		string s;
		int i,k = 0;
		for (i = 0; i < x; i++) 
			s.append(ch);
		return s;
	}

	string decodeString2(string s) {
		string op;
		stack<string> sstack;
		for (int itr = s.length() - 1; itr >= 0;  itr--) {
			char ch = s.at(itr);
			if (ch != '[')
			{
				string tmp(1, ch);
				sstack.push(tmp);
			}
			else {
				int tmpe =  --itr;
				int c = 0;
				int i = 0;
		  		while(isdigit(itr--) !=0);
				int tmps = itr;
				while (tmps <= tmpe) {
					i = i * 10 + (s.at(tmps) - '0');
					tmps++;
				}
				string ns;
				while (sstack.top() != "]") {
					ns.append(sstack.top());
					sstack.pop();
				}
				sstack.pop();
				string mystr = generatestring(i, ns);
				cout << mystr << endl;
				sstack.push(mystr);	
		}
		
		}
		while (!sstack.empty()) {
			cout << sstack.top() << " "; 
			op.append(sstack.top());
			sstack.pop();
		}
	return op;
	}

	string decodeString4(string s) {
		string op;
		stack<string> sstack;
		for (int itr = s.length() - 1; itr >= 0; itr--) {
			char ch = s.at(itr);
			if (ch != '[')
			{
				string tmp(1, ch);
				sstack.push(tmp);
			}
			else {
				itr--;
				char ch = s.at(itr);
				int i = ch - '0';
				string ns;
				while (sstack.top() != "]") {
					ns.append(sstack.top());
					sstack.pop();
				}
				sstack.pop();
				string mystr = generatestring(i, ns);
				//cout << mystr << endl;
				sstack.push(mystr);
			}

		}
		while (!sstack.empty()) {
			//cout << sstack.top() << " "; 
			op.append(sstack.top());
			sstack.pop();
		}
		return op;



		//	string substrng;
	//	string &out = substrng;

	  //  return "abcd";
		//return auxdecodeString(s,out);
	}


};

int main()
{

	Solution s;

	string test1 = "3[z]2[2[y]pq4[2[jk]e1[f]]]ef";
	string test = "leetcode";

	std::cout << test1  << endl;

	string dc = s.decodeString2(test1);
	cout << "op  --> " << dc << endl;;

   
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

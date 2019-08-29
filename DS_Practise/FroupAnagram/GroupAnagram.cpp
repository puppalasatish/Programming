// FroupAnagram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "map"
#include <vector>
#include <cmath>
#include <algorithm> 
#include <iostream>
#include "GroupAnagram.h"

using namespace std;

string str[] = { "ram", "sam" , "mam" , "mas" , "mar" , "asm" };
string::iterator it;
void printgroupanagrams() {

	map <string, vector<string>> mymap;
	map <string, vector<string>>::iterator it;

	
	for (int i = 0 ; i < 6; i++) {
		std::string s = str[i];
		std::sort(s.begin(),s.end());

		it = mymap.find(s);
		vector <string> v;
		if (it == mymap.end()) {			
			v.push_back(str[i]);
			mymap[s] = v;
		}
		else
		{
			v = mymap.find(s)->second;
			v.push_back(str[i]);
			mymap[s] = v;
		}
	}

	it = mymap.begin();
	while(it != mymap.end()){
		vector<string> g1 = it->second;

		for (std::vector<std::string>::iterator it1 = g1.begin(); it1 != g1.end(); it1++)
			cout << *it1 << " ";
		cout << endl;
		it++;
	}


}

int main()
{
	printgroupanagrams();
    return 0;
}


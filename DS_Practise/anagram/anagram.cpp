// anagram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <map>

char* strsort(char str[]) {
	int l = strlen(str);
	for (int i = 0; i < l ; i++)
		for (int j = i+1; j < l ; j++ )
			if (str[i] > str[j]) {
				char tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
	return str;
}

using namespace std;
bool isAnagram(char s1[],char s2[]) {
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	if (l1 != l2) return false;
	if (!strcmp(strsort(s1),strsort(s2))) return true;

	return false;
	
}

bool isAnagram1(char s1[], char s2[]) {
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	if (l1 != l2) return false;
	int arr[26] = { 0 };

	for (int i = 0; i < l1; i++)
		++arr[s1[i] - 'a'];

	for (int j = 0 ;j < l2; j++)
	{
		if (arr[s2[j] - 'a'] == 0) return false;
		else
			--arr[s2[j] - 'a'];
	}
	return true;
}

bool isAnagram2(char s1[], char s2[]) {
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	if (l1 != l2) return false;
	std::map<char, int> mymap;
	std::map<char, int>::iterator it;

	for (int i = 0; i < l1; i++) {
		it = mymap.find(s1[i]);
		if (it == mymap.end())
			mymap[s1[i]] = 1;
		else
			mymap[s1[i]] = ++mymap.find(s1[i])->second;
	}

	for (int i = 0; i < l2; i++) {
		it = mymap.find(s2[i]);
		if (it == mymap.end())
			return false;
		else
		{
			mymap[s2[i]] = --mymap.find(s2[i])->second;
			if(mymap.find(s2[i])->second == 0) mymap.erase(s2[i]);
		}		
	}
	return true;
}


int main()
{
	char s[] = "dsajjklfjlkadjfahfhkjhkdjjhlfadfjhadjhfkjahdkfhkajhskfjhakjhdsk";
	char s1[] = "dsajjklfjlkadjfahfhkjhkdjjhlmadfjhadjhfkjahdkfhkajhskfjhakjhdsk";

	if (isAnagram2(s,s1)) 
		cout << "anagrams ... " << endl;
	else
		cout << "not anagrams ... " << endl;
    return 0;
}


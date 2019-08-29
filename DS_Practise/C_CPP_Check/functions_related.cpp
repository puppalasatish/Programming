#include "stdafx.h"
#include "functions_related.h"

void sample() {

}


//void sample(int a) {
//
//	cout << a << endl;
//}

void sample(int &a) {
	cout << a << endl;
}

const int& sample(const int &a) {
	int x = 99;
	int &b = x;
	cout << a << endl;

	return b;
}






void man1() {
	int a = 10;
	int b = 20;
	int &aa = a;
	int c = 30;
	const int &aaa = 40;
	//drtgsyy
	const int &aaaa = c;

	cout << aaaa << endl;

	c++;

	cout << aaaa << endl;

	//const int d = 50;

	//int const &ab = d;
	//sample(a);
	//int &x = sample(ab);
	//cout << x << endl;
	//sample(a);
	//sample(aaa);
//	sample(10);

}

class A {

	int var = 99;
public:
	void setvar() const{
		//var = 0;

		cout << "Set var called \n";
	}
	
	int sam() {
		return ++var;
	}

	int sam() const {
		int c = var;
		return ++c;
	}
};


//
//class Collision
//{
//public:
//	Collision(void);
//	~Collision(void);
//	static bool IsCollision(Player &player, Platform& platform);
//};

class Player;
class Platform;


void man() {
	A a;
	const A aa;
	a.setvar();
	aa.setvar();
	cout << a.sam() << endl;
	cout << aa.sam() << endl;

}
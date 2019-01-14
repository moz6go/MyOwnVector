#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "MyVector.h"
using namespace std;

template <class Ttype>
void rand_int_init(vector<Ttype>& v, int rand_range) {
	for (int i = 0; i < v.size(); ++i) {
		v[i] = rand() % rand_range;
	}
}

template <class Ttype>
void rand_int_init(vector<Ttype>& v, int l_rand_range, int u_rand_range) {
	for (int i = 0; i < v.size(); ++i) {
		v[i] = rand() % (u_rand_range - l_rand_range) + l_rand_range;
	}
}

template <class Conteiner>
void print(Conteiner& c) {
	for (const auto& el : c) {
		cout << el << ' ';
	}
	cout << endl;
}


int main() {
	system("pause");
	return 0;
}




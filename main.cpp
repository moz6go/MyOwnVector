#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
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
	
	cout << "My vector push_back time test:" << endl;
	for (int c = 0; c < 5; ++c) {
		unsigned s = clock();
		my_vector<int> v;
		v.reserve(600000000);
		for (int i = 0; i < 600000000; ++i) {
			v.push_back(i);
		}
		unsigned f = clock();
		cout << (double)(f - s) / 1000 << endl;
	}

	cout << "STL vector push_back time test:" << endl;
	for (int c = 0; c < 5; ++c) {
		unsigned s = clock();
		vector<int> v;
		v.reserve(600000000);
		for (int i = 0; i < 600000000; ++i) {
			v.push_back(i);
		}
		unsigned f = clock();
		cout << (double)(f - s) / 1000 << endl;
	}
	system("pause");
	return 0;
}




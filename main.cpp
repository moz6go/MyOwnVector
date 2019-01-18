#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "MyVector.h"
using namespace std;

template <class Conteiner>
void rand_int_init(Conteiner& c, int rand_range) {
    for (auto& el : c) {
        el = rand() % rand_range;
	}
}

template <class Conteiner>
void rand_int_init(Conteiner& c, int l_rand_range, int u_rand_range) {
    for (auto& el : c) {
        el = rand() % (u_rand_range - l_rand_range) + l_rand_range;
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

    return 0;
}




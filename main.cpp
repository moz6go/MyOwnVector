#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "MyVector.h"

using namespace std;

int main()
{
	/*vector<int> v(3);
	cout << "capacity - " << v.capacity() << "\tsize - " << v.size() << endl;

	v.reserve(100);
	v.reserve(101);
	cout << "capacity - " << v.capacity() << "\tsize - " << v.size() << endl;

	vector<int> f(15, 1);
	cout << "Before assignment:" << endl;
	cout << "capacity - " << f.capacity() << "\tsize - " << f.size() << endl;

	for (int i = 0; i < f.size(); ++i) {
		cout << f.at(i) << endl;
	}

	f = v;
	cout << "After assignment:" << endl;
	cout << "capacity - " << f.capacity() << "\tsize - " << f.size() << endl;
	for (int i = 0; i < f.size(); ++i) {
		cout << f.at(i) << endl;
	}*/
	
	MyVector<int> vv;
	cout << "size - " << vv.Size() << "\tcapacity - " << vv.Capacity() << endl;
	cout << "push back:" << endl;
	for (int i = 0; i < 10; ++i) {
		vv.PushBack(i);
		cout << "size - " << vv.Size() << "\tcapacity - " << vv.Capacity() << endl;
	}
	vv[1] = 2;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;
	vv.Resize(15);
	cout << "After resize1:" << endl;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;

	vv.Resize(5);
	cout << "After resize2:" << endl;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;

	vv.PushBack(12);
	cout << "After PushBack:" << endl;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;
	cout << "size - " << vv.Size() << "\tcapacity - " << vv.Capacity() << endl;

	vv.ShrinkToFit();
	cout << "After ShrinkToFit:" << endl;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;
	cout << "size - " << vv.Size() << "\tcapacity - " << vv.Capacity() << endl;

	vv.Erase(4, 7);
	cout << "After Erase:" << endl;
	for (int i = 0; i < vv.Size(); ++i) {
		cout << vv[i] << ", ";
	}
	cout << endl;
	cout << "size - " << vv.Size() << "\tcapacity - " << vv.Capacity() << endl;
	system("pause");
	return 0;
}

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;
	// Remove the odd integers from li.
	// It is acceptable if the order of the remaining even integers is not
	// the same as in the original list.

void removeOdds1(list<int>& li)
{
	for (list<int>::iterator p=li.begin(); p != li.end(); p++) {
		if (*p % 2 == 1) {
			li.erase(p); // p will not disappear, p++ will be the next position
            
            // print the remaining list
            for (list<int>::iterator q=li.begin(); q!=li.end(); q++) {
                cout << *q << " ";
            }
            cout << endl;
        }
	}
}

void test1()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds1(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

void removeOdds2(list<int>& li)
{
    list<int>::iterator q;

    for (list<int>::iterator p=li.begin(); p != li.end(); p++) {
        if (*p % 2 == 1) {
            li.erase(p);
            cout << "*p == " << *p << " && ";
            cout << "*(p+1) == " << *(++p--) << endl;
        }
    }
}

void test2()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds2(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

int main()
{
    test1();
    test2();
    cout << "Passed" << endl;
}

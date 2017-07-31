#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;
	  // Remove the odd integers from v.
	  // It is acceptable if the order of the remaining even integers is not
	  // the same as in the original vector.
void removeOdds(vector<int>& v)
{
	vector<int>::iterator tmp = v.begin()-1;
	cout << "tmp == " << *tmp << endl;


	for (vector<int>::iterator p=v.begin(); p != v.end(); ) {
		if (*p % 2 == 1) {
			p = v.erase(p); // delete p, and the new p will be the next pos
            
            for (vector<int>::iterator q=v.begin(); q!=v.end(); q++) {
                cout << *q << " ";
            }
            cout << endl;
        }
        else
        	p++;
	}

}

// q = insert(p, 40) 在p之前 插入一个大小为40的节点 并返回这个节点
// q = erase(p) 删除p节点 返回p后面的第一个节点
void test()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
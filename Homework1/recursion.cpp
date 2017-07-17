#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int mult(unsigned int m, unsigned int n) {
	if (m == 0) return 0;
    return mult(m-1, n) + n;
}

int countDigit(int num, int digit) {
	if (num < 0) return countDigit(-num, digit);
	if (0 <= num && num <=9) return num == digit;
    return countDigit(num/10, digit) + ((num%10)==digit);
}

string pairPlus(string n) {
    if (n.size()==1) return n;
    return n.substr(0, 1)+ (n[0]==n[1] ? "++" :"") +pairPlus(n.substr(1));
}

string subParen(string str) {
    if (str[0] != '(') return subParen(str.substr(1));
    if (str[str.size()-1] !=')') return subParen(str.substr(0, str.size()-1));
    return str;
}

bool sumCombination(const int a[], int size, int target) {
	if (target == 0) return true;
	if (size == 0) return false;
	return sumCombination(a+1, size-1, target-a[0]) || sumCombination(a+1, size-1, target);
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (maze[sr][sc] != '.') return false;
	maze[sr][sc] = 'X';
	if (sr == er && sc == ec) return true;

	return pathExists(maze, nRows, nCols, sr+1, sc, er, ec)
	|| pathExists(maze, nRows, nCols, sr-1, sc, er, ec)
	|| pathExists(maze, nRows, nCols, sr, sc+1, er, ec)
	|| pathExists(maze, nRows, nCols, sr, sc-1, er, ec);
}

int main() {
    return 0;
}
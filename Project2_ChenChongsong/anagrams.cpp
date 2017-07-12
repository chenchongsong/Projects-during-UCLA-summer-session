#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int countChar(char ch, string s, int pos, const int size);
bool isPermute(string s1, string s2, int pos, const int size);
int readDictionary(istream &dictfile, string dict[]);
int recursivePermute(string word, const string dict[], int size, string results[]);
void recurPrint(const string results[], int size);


int countChar(char ch, string s, int pos, const int size) {
    // count how many times a char appears in a string 
    
    if (pos == size) return 0; // already checked every character in string s
    return countChar(ch, s, pos+1, size) + (ch == s[pos]); // count it if (ch == s[pos])
}

bool isPermute(string s1, string s2, int pos, const int size) {
    // Main idea:
    // for every character in s1, ie s1[pos], count the number it appears in s1 & s2
    
    if (pos == size) return true; // already checked every character in s1

    int tmp_char = s1[pos];

    if (countChar(tmp_char, s1, 0, size) == countChar(tmp_char, s2, 0, size))
        return isPermute(s1, s2, pos+1, size);
    else
        // tmp_char appears different times in s1 / s2
        return false;
}

int readDictionary(istream &dictfile, string dict[]) {
    if (!getline(dictfile, dict[0])) return 0; // read to the end of the dictfile
    return readDictionary(dictfile, dict+1) + 1;
}

int recursivePermute(string word, const string dict[], int size, string results[]) {
    if (size == 0) return 0;
    
    if (word.size() == dict[0].size() && isPermute(word, dict[0], 0, word.size())) {
        // word matches an anagram
        results[0] = dict[0];

        // check next string in dict[]
        return recursivePermute(word, dict+1, size-1, results+1) + 1;
    }
    else
        // check next string in dict[]
        return recursivePermute(word, dict+1, size-1, results);
}

void recurPrint(const string results[], int size) {
    if (size == 0) return;
    cout << "Matching word " << results[0] << endl;
    recurPrint(results + 1, size - 1);
}



int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = readDictionary(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = recursivePermute(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        recurPrint(results, numMatches);

    /*
    cout << dict[0] << endl;
    cout << dict[1] << endl;
    cout << dict[2] << endl;
    cout << dict[10000] << endl;
    cout << dict[25142] << endl;
    cout << dict[25143] << endl; // dict[25143] == ""
    */
    return 0;
}
#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

wstring vowels;

int has_double_letter(wstring s) {
	int d = 0;
	for (int i=0; i<s.size()-1; i++) {
		if (s[i] == s[i+1]) d++;
	}
	return d;
}

int main() {

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../difficult_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	int s1 = 0;
	double d_double = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict,s);) {
		d_double += has_double_letter(s);
		s1++;
	}

	fdict.close();

	std::wifstream fdict2("../easy_words.txt", std::ifstream::in);	
	fdict2.imbue (loc);

	int s2 = 0;
	double e_double = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict2,s);) {
		e_double += has_double_letter(s);
		s2++;
	}

	fdict2.close();

	cout <<  "Number of difficult words having double letter: " << d_double/s1 << endl;
	cout <<  "Number of easy words having double letter: " << e_double/s2 << endl;
}

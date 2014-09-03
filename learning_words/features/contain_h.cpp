#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

int has_h(wstring s) {
	for (int i=0; i<s.size(); i++) {
		if (s[i] == 'h') return 1;
	}
	return 0;
}

int main() {

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../difficult_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	int s1 = 0;
	double d_with_h = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict,s);) {
		d_with_h += has_h(s);
		s1++;
	}

	fdict.close();

	std::wifstream fdict2("../easy_words.txt", std::ifstream::in);	
	fdict2.imbue (loc);

	int s2 = 0;
	double e_with_h = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict2,s);) {
		e_with_h += has_h(s);
		s2++;
	}

	fdict2.close();

	cout <<  "Number of difficult words containing h: " << d_with_h/s1 << endl;
	cout <<  "Number of easy words containing h: " << e_with_h/s2 << endl;
}

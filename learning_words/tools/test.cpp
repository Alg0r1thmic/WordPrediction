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

	std::wifstream fdict("../difficult_words_test.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	// read and insert the dictionary   
	for(wstring s; getline(fdict,s);) {
		wcout << s.size() << L"\n";		
		//wcout << s.substr(0,s.size()-1) << L"\n";
	}

	fdict.close();
}

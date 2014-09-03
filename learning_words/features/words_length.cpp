#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

int main() {
	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../easy_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	double easy_size = 0;
	int s1 = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict,s); s1++) {
		easy_size += s.size();
	}

	fdict.close();

	double difficult_size = 0;
	int s2 = 0;

	std::wifstream fdict2("../difficult_words.txt", std::ifstream::in);	
	fdict2.imbue (loc);

	// read and insert the dictionary   
	for(wstring s; getline(fdict2,s);) {
		difficult_size += s.size();
		s2++;	
	}

	fdict2.close();

	cout << "Difficult words average size: " << difficult_size/s2 << endl;
	cout << "Easy words average size: " << easy_size/s1 << endl;

	
}

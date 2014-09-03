//genera dos fitxers. Un training set i un test set partint de sets ja creats.
#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

wstring vowels_list;

string process(wstring s) {
	string r;
	for (int i=0; i<s.size(); i++) {
		if (s[i] == vowels_list[0]) r.push_back('a');
		else if (s[i] == vowels_list[1]) r.push_back('e');
		else if (s[i] == vowels_list[2]) r.push_back('i');
		else if (s[i] == vowels_list[3]) r.push_back('o');
		else if (s[i] == vowels_list[4]) r.push_back('u');
		else if (s[i] == vowels_list[5]) r.push_back('n');
		else if (s[i] == vowels_list[6]) r.push_back('a');
		else if (s[i] == vowels_list[7]) r.push_back('e');
		else if (s[i] == vowels_list[8]) r.push_back('i');
		else if (s[i] == vowels_list[9]) r.push_back('o');
		else if (s[i] == vowels_list[10]) r.push_back('u');
		else if (s[i] == vowels_list[11]) r.push_back('c');
		else if (s[i] == vowels_list[12]) r.push_back('e');
		else if (s[i] == vowels_list[13]) r.push_back('a');
		else if (s[i] == vowels_list[14]) r.push_back('e');
		else if (s[i] == vowels_list[15]) r.push_back('i');
		else if (s[i] == vowels_list[16]) r.push_back('o');
		else if (s[i] == vowels_list[17]) r.push_back('u');
		else r.push_back(char(s[i]));
	}
	return r;
}

int main() {
	vowels_list = L"áéíóúñäëïöüçêàèìòù";
	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	//std::wifstream fdict("../../BK-tree/words-lemas_processed_unique.txt", std::ifstream::in);
	std::wifstream fdict("../sets/all_words_unique.txt", std::ifstream::in);	
	//std::wifstream fdict("in.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	for(wstring s; getline(fdict,s);) {
		string r = process(s);
		cout << r << endl;
	}

	fdict.close();
}

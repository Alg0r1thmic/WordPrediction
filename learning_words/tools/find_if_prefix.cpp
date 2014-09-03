#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

bool prefix(wstring s, wstring t) {
	if (s.size() > t.size()) return false;
	for (int i=0; i<s.size(); i++) {
		if (s[i] != t[i]) return false;
	}
	return true;
}

int main() {

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../sets/difficult_words_unique.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	std::wifstream fdict2("../sets/easy_words.txt", std::ifstream::in);
	fdict2.imbue (loc);

	vector<wstring> diff;
	vector<wstring> easy;
	
	// read and insert the dictionary   
	for(wstring s; getline(fdict,s); ) {
		diff.push_back(s);
	}

	fdict.close();

	// read and insert the dictionary   
	for(wstring s; getline(fdict2,s); ) {
		easy.push_back(s);
	}

	wcout << L"Paraules dificils com a prefixos de facils: \n";

	for (int i=0; i<diff.size(); i++) {
		for (int j=0; j<easy.size(); j++) {
			if (prefix(diff[i],easy[j])) {
				wcout << diff[i] << L" és prefix de " << easy[j] << L"\n"; 
			}
		}
	}

	wcout << L"\n";
	wcout << L"Paraules facils com a prefixos de dificils: \n";

	for (int i=0; i<easy.size(); i++) {
		for (int j=0; j<diff.size(); j++) {
			if (prefix(easy[i],diff[j])) {
				wcout << easy[i] << L" és prefix de " << diff[j] << L"\n"; 
			}
		}
	}
}

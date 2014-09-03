#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
#include <sstream>
using namespace std;

int main() {

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../sets/easy_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	set<wstring> con;
	set<wstring> repeated;
	
	// read and insert the dictionary   
	for(wstring s; getline(fdict,s); ) {
		wstringstream ss(s);
		wstring aux;
		ss >> aux;
		wcout << aux.substr(1,aux.size()-3) << L"\n";
	}

	fdict.close();
}

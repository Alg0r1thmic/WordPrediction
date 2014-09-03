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

	std::wifstream fdict("../sets/easy_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	set<wstring> con;
	set<wstring> repeated;
	
	// read and insert the dictionary   
	for(wstring s; fdict >> s; ) {
		if (con.count(s)>0) repeated.insert(s);
		con.insert(s);
	}

	fdict.close();
	set<wstring>::iterator it = repeated.begin();
	while (it!=repeated.end()) {
		wcout << (*it) << L"\n";
		it++;
	}
	//cout << con.size() << endl;
}

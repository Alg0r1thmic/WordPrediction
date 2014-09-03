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

	std::wifstream fdict("../difficult_words.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	set<wstring> con;

	
	bool paritat = true;

	// read and insert the dictionary   
	for(wstring s; fdict >> s; paritat = !paritat ) {
		if (!paritat) continue;
		con.insert(s);
	}

	fdict.close();

	std::wifstream fdict2("../easy_words_non_correct.txt", std::ifstream::in);	
	fdict2.imbue (loc);


	// read and insert the dictionary   
	for(wstring s; fdict2 >> s;) {
		if (con.count(s) > 0) wcout << s << endl;
	}

	fdict2.close();
}

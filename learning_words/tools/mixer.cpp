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

	std::wifstream fdict("easy.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	set<wstring> con;
	int s1,s2;
	s1 = s2 = 0;

	// read and insert the dictionary   
	for(wstring s; fdict >> s; s1++ )
		con.insert(s);

	fdict.close();

	std::wifstream fdict2("easy2.txt", std::ifstream::in);	
	fdict2.imbue (loc);

	// read and insert the dictionary   
	for(wstring s; fdict2 >> s; s2++ )
		con.insert(s);

	fdict2.close();

	/*cout << "Paraules totals a easy.txt: " << s1 << endl;
	cout << "Paraules totals a easy2.txt: " << s2 << endl;
	cout << "Paraules totals a en els dos documents: " << s1+s2 << endl;
	cout << "Paraules totals no repetides: " << con.size() << endl;*/

	set<wstring>::iterator it = con.begin();
	while (it!=con.end()) {
		wcout << (*it) << endl;
		it++;
	}
}

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

int main() {

	/* initialize random seed: */
  	srand (time(NULL));

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::wifstream fdict("../sets/words_full_set_p3_artificially_balanced.arff", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	std::wifstream fdict2("../sets/test_easy_luz.arff", std::ifstream::in);
	fdict2.imbue (loc);

	std::wofstream fdict3("../sets/train_set5.arff", std::ofstream::out);
	fdict3.imbue (loc);

	std::wofstream fdict4("../sets/test_set5.arff", std::ofstream::out);
	fdict4.imbue (loc);
 
	int i=1;
	set<int> v;
	int j = 0;
	while (j<30) {
		int r = 18+rand()%(int)(1354-18+1);
		if (v.count(r) == 0) {
			v.insert(r);
			j++;
		}
	}
	for(wstring s; getline(fdict,s);i++) {
		if (i<=17) {
			fdict3 << s << L"\n";
			fdict4 << s << L"\n";
		}
		else {
			if (v.count(i)>0) fdict4 << s << L"\n";
			else fdict3 << s << L"\n";
		}
	}
	i = 1;
	for(wstring s; getline(fdict2,s);i++) {
		if (i>=18) fdict4 << s << L"\n";
	}

	fdict.close();
	fdict2.close();
	fdict3.close();
	fdict4.close();
}

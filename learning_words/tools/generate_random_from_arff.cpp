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

	std::wifstream fdict("../sets/full_difficult_unique_easy_p10_words.arff", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	std::wofstream fdict2("../sets/full_difficult_unique_easy_p10_words_down10.arff", std::ifstream::out);
	fdict2.imbue (loc);

 
	int i=1;
	set<int> v;
	int j = 0;
	while (j<329) {
		int r = 22+rand()%(int)(687-22+1);
		if (v.count(r) == 0) {
			v.insert(r);
			j++;
		}
	}
	for(wstring s; getline(fdict,s);i++) {
		if (i<=21 or i>=688) {
			fdict2 << s << L"\n";
		}
		else {
			if (v.count(i)>0) fdict2 << s << L"\n";
		}
	}

	fdict.close();
	fdict2.close();
}

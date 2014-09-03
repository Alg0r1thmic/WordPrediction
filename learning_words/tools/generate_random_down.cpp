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

	std::wifstream fdict("../sets/difficult_words_unique.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	std::wofstream fdict4("../sets/difficult_words_unique_artificially_balanced_down4.txt", std::ofstream::out);
	fdict4.imbue (loc);
 
	for(wstring s; getline(fdict,s);) {
		int r = rand()%4;
		if (r == 3) fdict4 << s << L"\n";
	}

	fdict.close();
	fdict4.close();
}

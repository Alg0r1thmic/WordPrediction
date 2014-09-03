#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include "myers.h"
using namespace std;

int main() {
	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);
	std::fstream fdict("10k-words.txt", std::fstream::in);
	cout << "lala" << endl;
	string p = "prova";	
	
	// read and insert the dictionary   
	for(string s; fdict >> s; ) {
		int score, pos;
		myersCalcEditDistance(p, p.size(), s, s.size(), 25, -1, MYERS_MODE_NW, &score, &pos);
		cout << s << ' ' << score << endl;
	}
}

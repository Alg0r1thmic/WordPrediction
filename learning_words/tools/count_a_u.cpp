#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

bool has_u(wstring s) {
	wchar_t ua = 'ú';
	int u = 0;
	for (int i=0; i<s.size(); i++)
		if (s[i] == 'u' or s[i] == 'ú') u++;
	return u>0;
}

bool has_a(wstring s) {
	wchar_t oa = 'á';
	int a = 0;
	for (int i=0; i<s.size(); i++)
		if (s[i] == 'a' or s[i] == 'á') a++;
	return a>0;
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

	int count_a = 0;
	int count_u = 0;
	int total = 0;
	int both = 0;
	
	// read and insert the dictionary   
	for(wstring s; getline(fdict,s); total++) {
		if (has_u(s)) count_u++;
		if (has_a(s)) count_a++;
		if (has_a(s) and has_u(s)) both++;
	}

	wcout << "Out of " << total << " difficult words, " << count_u << " have u's. Percentage: " << double(count_u)/total << L"\n"; 
	wcout << "Out of " << total << " difficult words, " << count_a << " have a's. Percentage: " << double(count_a)/total << L"\n"; 
	wcout << "Out of " << total << " difficult words, " << both << " have a's and u's. Percentage: " << double(both)/total << L"\n"; 


	fdict.close();
	
	count_a = count_u = total = both = 0;

	// read and insert the dictionary   
	for(wstring s; getline(fdict2,s); total++) {
		if (has_u(s)) count_u++;
		if (has_a(s)) count_a++;
		if (has_a(s) and has_u(s)) both++;
	}
	
	wcout << "Out of " << total << " easy words, " << count_u << " have u's. Percentage: " << double(count_u)/total << L"\n"; 
	wcout << "Out of " << total << " easy words, " << count_a << " have a's. Percentage: " << double(count_a)/total << L"\n"; 
	wcout << "Out of " << total << " easy words, " << both << " have a's and u's. Percentage: " << double(both)/total << L"\n"; 

}

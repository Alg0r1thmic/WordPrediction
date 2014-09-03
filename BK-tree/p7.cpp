//p5.cpp amb webhits
#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include "bk_tree.cc"
using namespace std;

typedef vector<vector<int> > Matrix;

wstring vowels_list;
vector<vector<wstring> > classes_list;

struct info_word {
	wstring word;
	int d1;
	int d2;
	int vowels;
	bool has_accent;
	vector<int> classes;
	int length;
	bool has_h;
	bool has_double_letter;
	double percentage_vowels;
	bool three_consonants;
	bool two_vowels;
	bool has_x;
	bool alternada;
	long long web;
	bool has_o_and_u;
	bool has_ua;
	bool difficult;
};

int min(int a, int b) {
	if (a<b) return a;
	return b;
}

int minim(int a, int b, int c) {
	return min(min(a,b),min(a,c));
}

int dist(const wstring& a, const wstring& b) {
	Matrix m(a.size()+1,vector<int> (b.size()+1));
	int cost;
	m[0][0] = 0;
	for (int i=1; i<=a.size(); i++) m[i][0] = i;
	for (int j=1; j<=b.size(); j++) m[0][j] = j;
	for (int i=1; i<=a.size(); i++)
		for (int j=1; j<=b.size(); j++) {
			if (a[i-1] == b[j-1]) cost = 0;
			else cost = 1;
		
			m[i][j] = minim(m[i-1][j-1]+cost,m[i-1][j]+1,m[i][j-1]+1); //substitution, deletion and insertion
			if (i>1 and j>1 and a[i-1] == b[j-2] and a[i-2] == b[j-1])//transposition
				m[i][j] = min(m[i][j],m[i-2][j-2]+cost);			
		}
	return m[a.size()][b.size()];		
}

bool is_vowel(wchar_t c) {
	for (int i=0; i<vowels_list.size(); i++) {
		if (c == vowels_list[i]) return true;
	}
	return false;
}

int num_vowels(wstring s) {
	int nvowels = 0;
	for (int i=0; i<s.size(); i++) {
		if (is_vowel(s[i])) nvowels++;
	}			
	return nvowels;
}

bool has_accent(wstring s) {
	for (int i=0; i<s.size(); i++)
		for (int j=5; j<vowels_list.size(); j++) 
			if (s[i] == vowels_list[j]) return true;
		
	return false;
}

bool has_h(wstring s) {
	for (int i=0; i<s.size(); i++) {
		if (s[i] == 'h') return true;
	}
	return false;
}

bool has_double_letter(wstring s) {
	for (int i=0; i<s.size()-1; i++) {
		if (s[i] == s[i+1]) return true;
	}
	return false;
}

int length(wstring s) {
	return s.size();
}

bool three_consonants(wstring s) {
	if (s.size() < 3) return false;
	for (int i=0; i<s.size()-2; i++) {
		if (!is_vowel(s[i]) and s[i] != ' ' and !is_vowel(s[i+1]) and s[i+1] != ' ' and !is_vowel(s[i+2]) and s[i+2] != ' ') return true;
	}
	return false;
}

bool two_vowels(wstring s) {
	for (int i=0; i<s.size()-1; i++) {
		if (is_vowel(s[i]) and is_vowel(s[i+1])) return true;
	}
	return false;
}

bool has_x(wstring s) {
	for (int i=0; i<s.size(); i++) {
		if (s[i] == 'x') return true;
	}
	return false;
}

bool alternada(wstring s) {
	bool vowel = is_vowel(s[0]);
	for (int i=1; i<s.size(); i++) {
		vowel = !vowel;
		if (vowel != is_vowel(s[i])) return false;
	}
	return true;
}

bool has_o_and_u(wstring s) {
	bool o,u;
	o = u = false;
	for (int i=0; i<s.size(); i++) {
		if (s[i] == 'o' or s[i] == 'ó') o = true;
		if (s[i] == 'u' or s[i] == 'ú') u = true;
	}
	return o and u;
}

bool has_ua(wstring s) {
	for (int i=0; i<s.size()-1; i++) {
		if ((s[i] == 'u' or s[i] == 'ú') and (s[i+1] == 'a' or s[i+1] == 'á')) return true;
	}
	return false;
}



vector<int> get_classes(wstring s) {
	wstring b_string = L"b";
	wstring s_string = L"s";
	vector<int> w(classes_list.size());
	for (int k=0; k<s.size(); k++) {
		bool b = false;
		for (int i=0; not b and i<classes_list.size(); i++) {
			for (int j=0; not b and j<classes_list[i].size(); j++) {
				if (classes_list[i][j].size() == 1) {
					if (s[k] == classes_list[i][j][0]) {
						w[i]++;
						b = true;
					}
				}
				else if(classes_list[i][j].size() == 2) {
					if (k<s.size()-1 and s[k] == classes_list[i][j][0] and s[k+1] == classes_list[i][j][1]) {
						w[i]++;
						b = true;
					}
				}
				else {
					if (k<s.size()-2 and s[k] == classes_list[i][j][0] and s[k+1] == classes_list[i][j][1] and s[k+2] == classes_list[i][j][2]) {
						w[i]++;
						b = true;
					}
				}
			}
		}
	}
	return w;
}

void process_diff(const bk_tree<wstring>& bk, vector<info_word>& v, wstring s) {
	info_word info;
	info.word = s;
	info.vowels = num_vowels(s);
	info.has_accent = has_accent(s);
	info.classes = get_classes(s);
	info.d1 = bk.count_within_distance(s,1);
	info.d2 = bk.count_within_distance(s,2);
	info.length = length(s);
	info.has_h = has_h(s);
	info.has_double_letter = has_double_letter(s);
	info.percentage_vowels = double(info.vowels)/info.length;
	info.three_consonants = three_consonants(s);
	info.two_vowels = two_vowels(s);
	info.has_x = has_x(s);
	info.alternada = alternada(s);
	info.has_o_and_u = has_o_and_u(s);
	info.has_ua = has_ua(s);
	info.difficult = true;
	v.push_back(info);
}

void process_easy(const bk_tree<wstring>& bk, vector<info_word>& v, wstring s) {
	info_word info;
	info.word = s;
	info.vowels = num_vowels(s);
	info.has_accent = has_accent(s);
	info.classes = get_classes(s);
	info.d1 = bk.count_within_distance(s,1);
	info.d2 = bk.count_within_distance(s,2);
	info.length = length(s);
	info.has_h = has_h(s);
	info.has_double_letter = has_double_letter(s);	
	info.percentage_vowels = double(info.vowels)/info.length;
	info.three_consonants = three_consonants(s);
	info.two_vowels = two_vowels(s);
	info.has_x = has_x(s);
	info.alternada = alternada(s);
	info.has_o_and_u = has_o_and_u(s);
	info.has_ua = has_ua(s);
	info.difficult = false;
	v.push_back(info);
}

void init_classes_list() {
	vector<wstring> v1;
	v1.push_back(L"b");
	v1.push_back(L"v");
	classes_list.push_back(v1);
	vector<wstring> v2;
	v2.push_back(L"j");
	classes_list.push_back(v2);
	vector<wstring> v3;
	v3.push_back(L"h");
	classes_list.push_back(v3);
	vector<wstring> v5;
	v5.push_back(L"y");
	classes_list.push_back(v5);
	vector<wstring> v8;
	v8.push_back(L"cu");
	v8.push_back(L"q");
	v8.push_back(L"k");
	classes_list.push_back(v8);
	vector<wstring> v12;
	v12.push_back(L"rr");
	classes_list.push_back(v12);
}

void print(const vector<info_word>& v) {
	for (int i=0; i<v.size(); i++) {
		info_word info = v[i];
		wcout << info.word << L"\n";
		wcout << L"#distance 1: " << info.d1 << L"\n";
		wcout << L"#distance 2: " << info.d2 << L"\n";
		wcout << L"#vowels: " << info.vowels << L"\n";
		if (info.has_accent)	wcout << L"accent: yes\n";
		else wcout << L"accent: no\n";
		for (int j=0; j<info.classes.size(); j++) {
			if (j == 0) wcout << L"#[b.v]: ";
			else if (j == 1) wcout << L"  #[g,j]: ";
			else if (j == 2) wcout << L"  #[h]: ";
			else if (j == 3) wcout << L"  #[s,z,ce,ci,x]: ";
			else if (j == 4) wcout << L"  #[y]: ";
			else if (j == 5) wcout << L"  #[r,s,l]: ";
			else if (j == 6) wcout << L"  #[m,n,ñ]: ";
			else if (j == 7) wcout << L"  #[cu,q,k]: ";
			else if (j == 8) wcout << L"  #[b,d]: ";
			wcout << info.classes[j] << L";";
		}
		wcout << L"\n" << L"###########################################################################################################################" << L"\n\n";
	}	
}

void print_csv(const vector<info_word>& v) {
	//print the labels
	wcout << L"word, #distance 1, #distance 2, #vowels, has_accent?, #[b,v], #[g,j], #[h], #[s,z,ce,ci,x], #[y], #[r,s,l], #[m,n,ñ], #[cu,q,k], #[b,d]\n";
	for (int i=0; i<v.size(); i++) {
		info_word info = v[i];
		wcout << info.word;
		wcout << L", " << info.d1;
		wcout << L", " << info.d2;
		wcout << L", " << info.vowels;
		if (info.has_accent)	wcout << L", " << L"yes";
		else wcout << L", " << L"no";
		for (int j=0; j<info.classes.size(); j++)
			wcout << L", " << info.classes[j];
		
		wcout << L"\n";
	}	
}

void print_arff(const vector<info_word>& v) {
	wcout << "%We don't separate training for testing here since we use fold evaluation 10 levels. Generated by p5.cpp" << L"\n";
	wcout << "@relation whole_set_p6" << L"\n";
	wcout << "@attribute word string" << L"\n";
	wcout << "@attribute d1 integer" << L"\n";
	wcout << "@attribute c1 {yes,no}" << L"\n";
	wcout << "@attribute c2 {yes,no}" << L"\n";
	wcout << "@attribute c3 {yes,no}" << L"\n";
	wcout << "@attribute c5 {yes,no}" << L"\n";
	wcout << "@attribute c8 {yes,no}" << L"\n";
	wcout << "@attribute c12 {yes,no}" << L"\n";
	wcout << "@attribute w_length integer" << L"\n";
	wcout << "@attribute three_consonants {yes,no}" << L"\n";
	wcout << "@attribute has_x {yes,no}" << L"\n";
	wcout << "@attribute alternada {yes,no}" << L"\n";
	wcout << "@attribute has_h {yes,no}" << L"\n";
	wcout << "@attribute has_o_and_u {yes,no}" << L"\n";
	wcout << "@attribute has_ua {yes,no}" << L"\n";
	wcout << "@attribute difficult {yes,no}" << L"\n";
	wcout << "@data" << L"\n";
	wcout << L"\n";
	//print the labels
	for (int i=0; i<v.size(); i++) {
		info_word info = v[i];

		wcout << L"\"" << info.word << L"\", ";

		wcout << info.d1;

		//if (info.has_accent)	wcout << L", " << L"yes";
		//else wcout << L", " << L"no";
		if (info.classes[0] > 1) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.classes[1] > 0) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.classes[2] > 0) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.classes[3] > 0) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.classes[4] > 0) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.classes[5] > 0) wcout << L", " << L"yes";
		else wcout << L", " << L"no";
		
		wcout << L", " << info.length;

		if (info.three_consonants) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.has_x) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.alternada) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.has_h) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.has_o_and_u) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.has_ua) wcout << L", " << L"yes";
		else wcout << L", " << L"no";

		if (info.difficult) wcout << L", " << L"yes";//classification label meaning "difficult word"
		else wcout << L", " << L"no";

		wcout << L"\n";
	}	
}

int main()
{
	

	// open the stream
	std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	//init parameters	
	vowels_list = L"aeiouáéíóú";
	init_classes_list();

	//create the BK-tree
	bk_tree<wstring> bk = bk_tree<wstring>(dist);

	// read and insert the dictionary   
	for(wstring s; fdict >> s; )
		bk.insert(s);
	
	//close this stream
	fdict.close();

	//open the new stream with the difficult words
	std::wifstream fin("../learning_words/sets/difficult_words_unique.txt", std::ifstream::in);	
	fin.imbue (loc);

	//process the difficult words
	vector<info_word> v;
	for(wstring s; getline(fin,s); ) {
		process_diff(bk,v,s);
	}

	//open the new stream with the easy words
	std::wifstream fin2("../learning_words/sets/easy_words.txt", std::ifstream::in);	
	fin2.imbue (loc);
	
	//process the easy words
	for(wstring s; getline(fin2,s); ) {
		process_easy(bk,v,s);
	}

	//close this stream
	fin.close();
	fin2.close();
	print_arff(v);	
}

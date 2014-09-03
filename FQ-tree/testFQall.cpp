#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>
#include <clocale>
#include <vector>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "fq_tree.cc"
using namespace std;
using namespace std;

typedef vector<vector<int> > Matrix;

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
		}
	return m[a.size()][b.size()];		
}

int dist2(const wstring& a, const wstring& b) {
	Matrix m(a.size()+1,vector<int> (b.size()+1));
	int cost;
	m[0][0] = 0;
	for (int i=1; i<=a.size(); i++) m[i][0] = i;
	for (int j=1; j<=b.size(); j++) m[0][j] = j;
	for (int i=1; i<=a.size(); i++)
		for (int j=1; j<=b.size(); j++) {
			if (a[i-1] == b[j-1]) cost = 0;
			else cost = 1;
		
			m[i][j] = (m[i-1][j-1]+cost); //substitution			
		}
	return m[a.size()][b.size()];		
}

int dist3(const wstring& a, const wstring& b, long long& comp) {
	comp++;
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
		}
	return m[a.size()][b.size()];		
}

int main() {

	//  Start the building timer
	std::clock_t start_build;
    start_build = std::clock();

	std::srand ( unsigned ( std::time(0) ) );
	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);
	std::wifstream fdict("randomBig.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);

	long long comp = 0;
		
	vector<wstring> levels,words;
	for(wstring s; getline(fdict,s); ) {
		words.push_back(s);
		levels.push_back(s);
	}
	
	random_shuffle(levels.begin(),levels.end());

	//create the FQ-tree
	fq_tree fq = fq_tree(dist3,2,levels);

	Node* root = fq.getRoot();

	// read and insert the dictionary   
	for(int i=0; i<words.size(); i++) {
		wstring s = words[i];
		//wcout << s << L"\n";
		fq.insert(root,s,comp);
		//cout << "peto6" << endl;
	}

	// output of the building timer
    std::cerr << "Building structure time: " << (std::clock() - start_build) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    std::cerr << "Building comparisons: " << comp << std::endl;
    comp = 0;

	//close this stream
	fdict.close();

	//  Start the process timer
	std::clock_t start_process;
    start_process = std::clock();

	std::wifstream fin("easy_words.txt", std::ifstream::in);	
	fin.imbue (loc);

	for(wstring s; getline(fin,s); ) {
		//wcout << s << L"\n";
		wcout << fq.count_within_distance(s,2,comp) << L"\n";
	}

	// output of the process timer
	std::cerr << "Process time: " << (std::clock() - start_process) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	std::cerr << "Processing comparisons: " << comp << std::endl;
	
	//close this stream
	fin.close();	
}

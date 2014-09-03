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

int main() {
	std::srand ( unsigned ( std::time(0) ) );
	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);
	std::wifstream fdict("difficult_words_unique.txt", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
		
	vector<wstring> levels,words;
	for(wstring s; getline(fdict,s); ) {
		words.push_back(s);
		levels.push_back(s);
	}
	
	random_shuffle(levels.begin(),levels.end());

	//create the FQ-tree
	fq_tree fq = fq_tree(dist,2,levels);

	Node* root = fq.getRoot();

	// read and insert the dictionary   
	for(int i=0; i<words.size(); i++) {
		wstring s = words[i];
		fq.insert(root,s);
		//cout << "peto6" << endl;
	}

	wcout << L"Fi d'insercions\n";
	vector<wstring> v;
	wcout << fq.get_within_distance(L"amable", 2, &v) << L"\n";
	for (int i=0; i<v.size(); i++) wcout << v[i] << L"\n";
	
	//close this stream
	fdict.close();
	
}

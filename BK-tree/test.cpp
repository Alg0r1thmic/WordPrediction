#include <iostream>
#include <string>
#include <vector>
#include "bk_tree.cc"
using namespace std;

typedef vector<vector<int> > Matrix;

int min(int a, int b) {
	if (a<b) return a;
	return b;
}

int minim(int a, int b, int c) {
	return min(min(a,b),min(a,c));
}

int dist(const string& a, const string& b) {
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

int main() {
	string a;
	bk_tree<string> bk = bk_tree<string>(dist);
	cin >> a;
	while (a != "prou") {
		bk.insert(a);
		cin >> a;
	}
	cout << "Now the retrieved string and the distance" << endl;
	vector<string> v;
	int r;
	cin >> a;
	cin >> r;
	cout << bk.get_within_distance(a, r, &v) << endl;
	for (int i=0; i<v.size(); i++) cout << v[i] << endl;
}

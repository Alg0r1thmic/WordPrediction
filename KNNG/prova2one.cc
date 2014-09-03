#include "knng.cc"
using namespace std;

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

int main() {
	knng kn = knng(dist,"utf8.dat",16);
	//open the new stream with the difficult words
	vector<wstring> v;
	cout << kn.get_within_distance(L"ha", 2, &v) << endl;
	for (int i=0; i<v.size(); i++) wcout << v[i] << L"\n";
}

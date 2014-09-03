#include "knng.cc"
#include <ctime>
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
	//  Start the building timer
	std::clock_t start_build;
     	start_build = std::clock();
	
	knng kn = knng(dist,"10k-words.txt",4);
	
	// output of the building timer
     	std::cerr << "Building structure time: " << (std::clock() - start_build) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	//open the new stream with the difficult words
	std::wifstream fin("utf8.dat", std::ifstream::in);	
	std::locale loc ("");
        std::locale::global (loc);   
        fin.imbue (loc);

	//  Start the process timer
	std::clock_t start_process;
     	start_process = std::clock();

	//process the difficult words
	for(wstring s; fin >> s; )
		cout << kn.count_within_distance(s, 0) << endl;

	// output of the process timer
	std::cerr << "Process time: " << (std::clock() - start_process) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	//close this stream
	fin.close();	
}

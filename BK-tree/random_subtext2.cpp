#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <cmath>
#include <fstream>
#include <locale>
#include <clocale>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <set>
#include <unordered_set>
using namespace std;
using namespace std;

int main() {

	srand(time(NULL));

	// open the stream
	//std::wifstream fdict("words-lemas_processed.txt", std::ifstream::in);	

	std::fstream fdict("words-lemas_processed_unique_desacentuado.txt", std::ifstream::in);
	
	vector<string> v;

	// read and insert the dictionary   
	for(string s; fdict >> s; )
		v.push_back(s);
	
	//close this stream
	fdict.close();

	unordered_set<int> con;
	int n = 10000;
	
	for (int i=0; i<n; i++) {
		int r = rand()%v.size();
		while (con.count(r)>0) r = rand()%v.size();
		con.insert(r);
	}
	
	unordered_set<int>::iterator it = con.begin();
	while (it!=con.end()) {
		cout << v[(*it)] << endl;
		it++;
	}		
}

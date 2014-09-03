#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <fstream>
#include <locale>
#include <clocale>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#define inf 9999999;

typedef vector<vector<int> > Matrix;

class knng {
    
    public:
        knng(int (*d)(const wstring& x, const wstring& y), string path, int k) {
            distance = d; 
            completed = load_data(path,k);
            int n = completed.size();
            int ln = log(n);
            Pn = Matrix(ln,vector<int>(n));

            // initialize random seed:
            srand (time(NULL));

            //generate the random pivots and initialize the matrix Pn
            for (int i=1; i<ln; i++) pivots.insert(rand()%n);
	    /*OJU DEBUGGIN A LA LINIA DE DALT I A LA DE BAIX!!!*/
	    pivots.insert(1081244);
            set<int>::iterator it = pivots.begin();
            int j = 0;
            while (it != pivots.end()) {
                for (int i=0; i<n; i++) {
                    int dist = distance(completed[*it].value,completed[i].value);
                    Pn[j][i] = dist;
                    update(i,*it,dist);
                }
                it++;
                j++;
            }           
        }

	void print_test_pivots() {
		cout << log(completed.size()) << " pivots.";
		set<int>::iterator it = pivots.begin();
		int cas = 0;
		while (it != pivots.end()) {
			Node n = completed[*it];			
			cout << cas << ": ";
			wcout << n.value << L"\n";
			set<pair<int,Node*> >::iterator it2 = n.NAH.begin();
			while (it2 != n.NAH.end()) {
				wcout << L"   " << ((*it2).second)->value << " " << (*it2).first << L"\n";
				it2++; 
			}
			it++;
		}
	}

        void generate();
            
        //~bk_tree() { if (root != NULL) delete root; }


        
    private:

        class Node {
            public:
                int id;
                wstring value;
                int max_size;
                set<pair<int,Node*> > NAH; //pair (distance,toNode)
                set<int> contained;
                int curCovR;
                
                Node(int i, wstring s, int k) {
                    this->id = i;
                    this->value = s;
                    this->max_size = k;
                    //inicialitzar set?? Crec que no cal pq es tipus std
                    curCovR = inf;
                }
                
                /*~Node() {
                    for (map<int, void*>::iterator it = edge.begin(); it != edge.end(); ++it) 
                        delete ((Node*)(it->second));
                }*/

                bool operator < (const Node& n) const {
                    return this->curCovR < n.curCovR;
                }

                void add(int i, Node* n, int dist) {
                    if (NAH.size() < max_size) {
                        if (contained.count(i) > 0); //Si ja el tenim passem
                        else {//sino l'afegim
                            contained.insert(i);
                            NAH.insert(make_pair(dist,n));
                        }
                    }
                    else {//Hem de fer fora l'últim si s'escau
                        set<pair<int,Node*> >::iterator it = NAH.end();
                        it--;
                        if ((*it).first > dist) {//borrem l'ultim i afegim el nou
                            //borrem
                            contained.erase((*it).second->id);
                            NAH.erase(it);
                            //afegim
                            contained.insert(i);
                            NAH.insert(make_pair(dist,n));
                        }
                    }
                }
        };

        vector<Node> completed;
        Matrix Pn;
	set<int> pivots;
        priority_queue<Node> COH;
        int (*distance)(const wstring& x, const wstring& y);

        vector<Node> load_data(string path, int k) {
            // open the stream
            std::wifstream fdict(path, std::ifstream::in);
            std::locale loc ("");
            std::locale::global (loc);   
            fdict.imbue (loc);

            vector<Node> v;
            int i = 0;

            // read and insert the dictionary   
            for(wstring s; fdict >> s; i++) {
                Node n(i,s,k);
                v.push_back(n);
            }                
            
            //close this stream
            fdict.close();
	    return v;
        }

        void update(int i, int j, int dist) {
	    if (j == 1081244) {
		wcout << L"before " << completed[j].value << L" and candidate for insertion " << completed[i].value << L"\n";
		set<pair<int,Node*> >::iterator it = completed[j].NAH.begin();
		while (it!= completed[j].NAH.end()) {
			wcout << L"   " << ((*it).second)->value << " " << (*it).first << L"\n";
			it++;
		}
	    }
            completed[i].add(j,&(completed[j]),dist);
            completed[j].add(i,&(completed[i]),dist);
	    if (j == 1081244) {
		wcout << L"after " << completed[j].value << L"\n";
		set<pair<int,Node*> >::iterator it = completed[j].NAH.begin();
		while (it!= completed[j].NAH.end()) {
			wcout << L"   " << ((*it).second)->value << " " << (*it).first << L"\n";
			it++;
		}
	    }
        }       
};

void knng::generate() {
    cout << "hola" << endl;
}

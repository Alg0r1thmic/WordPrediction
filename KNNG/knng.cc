#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <list>
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

int abs(int a) {
	if (a<0) return -a;
	return a;
}

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
            for (int i=0; i<ln; i++) pivots.insert(rand()%n);
	    //pivots.insert(724136);
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
	    for (int u=0; u<n; u++) {
		if (pivots.count(u)) continue; //we want U-P
		priority_queue<pair<int,int> > SortDiff;
		bool valid = true;
		for (int v=0; v<n and valid; v++) {
			if (v == u or pivots.count(v) or in_NHA(u,v)) continue;
			int Diffv = -1;
			for (int k=0; k<Pn.size(); k++) {
				Diffv = max(Diffv,abs(Pn[k][v]-Pn[k][u]));
				if (Diffv >= completed[u].curCovR) {
					valid = false;
					break;
				}
			}
			if (valid) SortDiff.push(make_pair(Diffv,v));		
		}
		while (!SortDiff.empty()) {
			int v = SortDiff.top().second;
			SortDiff.pop();
			int dist = distance(completed[u].value,completed[v].value);
			if (dist < completed[u].curCovR) update(u,v,dist);
		}
	    }           
        }

	void print_test_pivots() {
		cout << (int)log(completed.size()) << " pivots." << endl;
		set<int>::iterator it = pivots.begin();
		while (it != pivots.end()) {
			Node n = completed[*it];			
			cout << n.curCovR << ": ";
			wcout << n.value << L"\n";
			list<pair<int,Node*> >::iterator it2 = n.NAH.begin();
			while (it2 != n.NAH.end()) {
				wcout << L"   " << ((*it2).second)->value << " " << (*it2).first << L"\n";
				it2++; 
			}
			it++;
		}
	}

	void print_test_pivots_and_more() {
		pivots.insert(0);
		pivots.insert(1);
		pivots.insert(2);
		cout << (int)log(completed.size()) << " pivots." << endl;
		set<int>::iterator it = pivots.begin();
		while (it != pivots.end()) {
			Node n = completed[*it];			
			cout << n.curCovR << ": ";
			wcout << n.value << L"\n";
			list<pair<int,Node*> >::iterator it2 = n.NAH.begin();
			while (it2 != n.NAH.end()) {
				wcout << L"   " << ((*it2).second)->value << " " << (*it2).first << L"\n";
				it2++; 
			}
			it++;
		}
	}
        
	/* BORRAR TOTS ELS PARCHES!! (COUTS I WCOUTS) EL PROBLEMA ES QUE UTF8.DAT TE REPETITS. PROVAR SI FILTRANT PRIMER EL UTF8.DAT PER ELIMINAR REPETITS DONA EL MATEIX RESULTAT QUE BK	 */
	int get_within_distance(wstring s, int dist, vector<wstring> *result) {
		int n = completed.size();
		vector<bool> visited(n,false);
		int i=0;
		queue<int> q;
		visited[i] = true;
		q.push(i);
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			int dqu = distance(s,completed[curr].value);
			if (dqu <= dist) {//si ens interessa checkegem els seus veins tb
				result->push_back(completed[curr].value);
				Node nd = completed[curr];
				//checking de veins..
				list<pair<int,Node*> >::iterator it = nd.NAH.begin();
				while (it != nd.NAH.end()) {
					if (not visited[(*it).second->id]) {
						visited[(*it).second->id] = true;
						q.push((*it).second->id);
					}
					it++; 
				}
			}
			else {
				Node nd = completed[curr];
				//checking de veins..
				list<pair<int,Node*> >::iterator it = nd.NAH.begin();
				while (it != nd.NAH.end()) {
					if (not visited[(*it).second->id] and ((*it).first) < dqu - dist) visited[(*it).second->id] = true; //discard
					it++; 
				}
			}

			while(q.empty() and i < n-1) {
				i++;
				if (not visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		return result->size();
	}

	int count_within_distance(wstring s, int dist) {
		int n = completed.size();
		int result = 0;
		vector<bool> visited(n,false);
		int i=0;
		queue<int> q;
		visited[i] = true;
		q.push(i);
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			int dqu = distance(s,completed[curr].value);
			if (dqu <= dist) {//si ens interessa checkegem els seus veins tb
				result++;
				Node nd = completed[curr];
				//checking de veins..
				list<pair<int,Node*> >::iterator it = nd.NAH.begin();
				while (it != nd.NAH.end()) {
					if (not visited[(*it).second->id]) {
						visited[(*it).second->id] = true;
						q.push((*it).second->id);
					}
					it++; 
				}
			}
			else {
				Node nd = completed[curr];
				//checking de veins..
				list<pair<int,Node*> >::iterator it = nd.NAH.begin();
				while (it != nd.NAH.end()) {
					if (not visited[(*it).second->id] and ((*it).first) < dqu - dist) visited[(*it).second->id] = true; //discard
					it++; 
				}
			}

			while(q.empty() and i < n-1) {
				i++;
				if (not visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		return result;
	}

	void load(string path) {

	}

	void save(string path) {

	}

        //~bk_tree() { if (root != NULL) delete root; }


        
    private:

        class Node {
            public:
                int id;
                wstring value;
                int max_size;
                list<pair<int,Node*> > NAH; //pair (distance,toNode)
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
                    	//mirem si ja hi és, si hi és passem
			for (list<pair<int,Node*> >::iterator it = NAH.begin(); it != NAH.end(); it++)
    				if ((*it).second->id == i) return;
			//sino l'afegim
			for (list<pair<int,Node*> >::iterator it = NAH.begin(); it != NAH.end(); it++)
    				if ((*it).first > dist) {
					NAH.insert(it,make_pair(dist,n));
					return;
				}
			//si no l'hem insertat abans es pq va al final
			NAH.push_back(make_pair(dist,n));
			curCovR = dist;               
                    }
                    else {//Hem de fer fora l'últim si s'escau
                        //mirem si ja hi és, si hi és passem
			for (list<pair<int,Node*> >::iterator it = NAH.begin(); it != NAH.end(); it++)
    				if ((*it).second->id == i) return;
			//sino l'afegim on toca i esborrem l'ultim
			bool insertat = false;
			for (list<pair<int,Node*> >::iterator it = NAH.begin(); it != NAH.end(); it++)
    				if ((*it).first > dist) {
					NAH.insert(it,make_pair(dist,n));
					insertat = true;
					break;
				}
			if (insertat) {//si n'hem afegit un esobrrem l'ultim (potser es el mateix que hem insertat)
				list<pair<int,Node*> >::iterator it = NAH.end();
				it--;
				NAH.erase(it);
				it--;
				curCovR = (*it).first;
			}
			//sino hem insertat es pq el nou que anavem a posar era pitjor que els que ja hi havia                     
                    }
                }

		bool in_NHA(int v) {
			for (list<pair<int,Node*> >::iterator it = NAH.begin(); it != NAH.end(); it++) {
				if ((*it).second->id == v) return true;
			}
			return false;				
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
	    /*std::wifstream fdict2(path2, std::ifstream::in);
            fdict2.imbue (loc);

            // read and insert the dictionary   
            for(wstring s; fdict2 >> s; i++) {
                Node n(i,s,k);
                v.push_back(n);
            }                
            
            //close this stream
            fdict2.close();*/	
	    return v;
        }

        void update(int i, int j, int dist) {
	    /*if (j == 1081244) {
		wcout << L"before " << completed[j].value << L" and candidate for insertion " << completed[i].value << L"\n";
		list<pair<int,Node*> >::iterator it = completed[j].NAH.begin();
		while (it!= completed[j].NAH.end()) {
			wcout << L"   " << ((*it).second)->value << " " << (*it).first << L"\n";
			it++;
		}
	    }*/
            completed[i].add(j,&(completed[j]),dist);
            completed[j].add(i,&(completed[i]),dist);
	    /*if (j == 1081244) {
		wcout << L"after " << completed[j].value << L"\n";
		list<pair<int,Node*> >::iterator it = completed[j].NAH.begin();
		while (it!= completed[j].NAH.end()) {
			wcout << L"   " << ((*it).second)->value << " " << (*it).first << L"\n";
			it++;
		}
	    }*/
        }

	bool in_NHA(int u, int v) {
		return completed[u].in_NHA(v);
	}     
};

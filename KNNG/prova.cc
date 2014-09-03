#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <set>
using namespace std;

#define inf 9999999;

class Node {
    public:
        int id;
        wstring value;
        int max_size;
        set<Node> NAH;
        int curCovR;
        
        Node(int i, wstring s, int k) {
            this->id = i;
            this->value = s;
            this->max_size = k;
            //inicialitzar set??
            curCovR = inf;
        }
        
        /*~Node() {
            for (map<int, void*>::iterator it = edge.begin(); it != edge.end(); ++it) 
                delete ((Node*)(it->second));
        }*/

        bool operator < (const Node& n) const {
            return this->curCovR < n.curCovR;
        }
};

class mycomparison
{
public:
  bool operator() (Node* lhs, Node* rhs) const
  {
  	return (lhs->curCovR > rhs->curCovR);
  }
};

int main() {
	
	vector<Node*> v;
	Node n(0,L"prova1",2);
	n.curCovR = 5;
	Node m(1,L"prova2",2);
	m.curCovR = 4;
	v.push_back(&n);
	v.push_back(&m);
	priority_queue<Node*,std::vector<Node*>,mycomparison> COH;
	COH.push(&n);
	COH.push(&m);
	cout << COH.top()->curCovR << endl;
	COH.pop();
	cout << COH.top()->curCovR << endl;
	COH.pop();
	cout << COH.top()->curCovR << endl;



}
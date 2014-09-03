#include <vector>
#include <queue>
#include "node.cc"
#include <iostream>
using namespace std;

class fq_tree {
    
    public:
        fq_tree(int (*d)(const wstring& x, const wstring& y, long long& comp), int b, vector<wstring>& v) { 
            root = NULL;
            bucket_size = b;
            elements = 0;
            distance = d;
            levels = v;
            root = new Node(0);
        }       
        
        ~fq_tree() { if (root != NULL) delete root; }

        //int get_within_distance(const wstring& q, int r, vector<wstring> *result) const;

        int count_within_distance(const wstring& q, int r, long long& comp) const;
        
        void insert(Node*p, const wstring& x, long long& comp);
        
        int size() const { return elements; }
  
        bool empty() const { return !elements; }

        Node* getRoot() {
            return root;
        }
        
    private:        
        
        Node *root;
        int (*distance)(const wstring& x, const wstring& y, long long& comp);
        vector<wstring> levels;
        int bucket_size;
        int elements;

        /*int get_bucket(Leaf* l, const wstring& q, int r, vector<wstring> *result) const {
            int qtt = 0;
            for (int i=0; i<l->v.size(); i++) {
                if (distance(q, l->v[i]) <= r) {
                    result->push_back(l->v[i]);
                    qtt++;
                }
            }
            return qtt;    
        }*/

        int count_bucket(Leaf* l, const wstring& q, int r, long long& comp) const {
            int qtt = 0;
            for (int i=0; i<l->v.size(); i++) {
                if (distance(q, l->v[i],comp) <= r) qtt++;            
            }
            return qtt;    
        }
};

/*int fq_tree::get_within_distance(const wstring& q, int r, vector<wstring> *result) const {
    if (!root) return 0;
    int qtt = 0;
    queue<Node*> Q;
    Q.push(root);
    while (not Q.empty()) {
        Node *p = Q.front(); Q.pop();
        int d = distance(q, levels[p->level]);
        map<int, Leaf*>::iterator it = p->leaves.upper_bound(d + r);
        if (it != p->leaves.begin()) {
            for (--it; it->first >= d - r; --it) {
                qtt += get_bucket(it->second,q,r,result);
                if (it == p->leaves.begin()) break;
            }
        }
        map<int, Node*>::iterator it2 = p->edge.upper_bound(d + r);
        if (it2 != p->edge.begin()) {
            for (--it2; it2->first >= d - r; --it2) {
                Q.push((Node*)(it2->second));
                if (it2 == p->edge.begin()) break;
            }
        }
    }
    return qtt;
}*/

int fq_tree::count_within_distance(const wstring& q, int r,long long& comp) const {
    if (!root) return 0;
    int qtt = 0;    
    vector<int> aux; //we use id to keep the comparisons with the key nodes
    queue<Node*> Q;
    Q.push(root);
    //wcout << "Counting " << q << L"\n";
    while (not Q.empty()) {
        Node *p = Q.front(); Q.pop();
        //wcout << p->level << L"\n";
        int d;
        if (p->level < aux.size()) d = aux[p->level];
        else {
            d = distance(q, levels[p->level],comp);
            aux.push_back(d);
        }
        map<int, Leaf*>::iterator it = p->leaves.upper_bound(d + r);
        if (it != p->leaves.begin()) {
            for (--it; it->first >= d - r; --it) {
                qtt += count_bucket(it->second,q,r,comp);
                if (it == p->leaves.begin()) break;
            }
        }
        map<int, Node*>::iterator it2 = p->edge.upper_bound(d + r);
        if (it2 != p->edge.begin()) {
            for (--it2; it2->first >= d - r; --it2) {
                Q.push((Node*)(it2->second));
                if (it2 == p->edge.begin()) break;
            }
        }
    }
    return qtt;
}

void fq_tree::insert(Node *p, const wstring& x, long long& comp) {
    //wcout << L"peto\n";
    int d = distance(x, levels[p->level],comp);
    //wcout << L"For the word " << x << L" at level " << p->level << L"(" << levels[p->level] << L") is at distance " << d << L"\n";
    //if (d == 0) return;
    if (p->leaves.count(d)) {//ya existe la hoja
        Leaf* z = p->leaves[d];
        if (z->v.size() < bucket_size) z->insert(x); //si cabe la insertamos
        else {
            vector<wstring> aux;//cogemos los elementos del bucket lleno
            for (int i=0; i<z->v.size(); i++) aux.push_back(z->v[i]);
            p->leaves.erase(d);
            delete(z);                   //eliminamos la hoja del bucket lleno

            p->edge[d] = new Node(p->level+1);//creamos nodo intermedio
            Node* q = (Node*)(p->edge[d]);
            for (int i=0; i<aux.size(); i++) {//insertamos todos los elementos del bucket anterior mas el nuevo
                insert(q,aux[i],comp);                
                //wcout << L"peto4\n";
            }
            insert(q,x,comp);
            //wcout << L"peto2\n";
        }                      
    }
    else if (p->edge.count(d)) {
         p = (Node*)(p->edge[d]);
         insert(p,x,comp);         
         //wcout << L"peto3\n";
    }
    else {//si no existe arista ni hoja, creamos hoja allí
        //wcout << L"Inserto fulla nova " << x << L"\n";
        p->leaves[d] = new Leaf();
        ((Leaf*)p->leaves[d])->insert(x);
        ++elements;
        //wcout << L"Fi inserció fulla nova " << x << L"\n";
    }
    //wcout << L"peto5\n"; 
}

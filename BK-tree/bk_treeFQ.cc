#include <vector>
#include <map>
#include <queue>
using namespace std;

template <class T>
class bk_tree {
    
    public:
        bk_tree(int (*d)(const T& x, const T& y, long long& comp)) { root = NULL; elements = 0; distance = d; }       
        
        ~bk_tree() { if (root != NULL) delete root; }
        
        //int get_within_distance(const T& q, int r, vector<T> *result) const;

	    int count_within_distance(const T& q, int r,long long& comp) const;
        
        void insert(const T& x, long long& comp);
        
        int size() const { return elements; }
  
        bool empty() const { return !elements; }

        //bool count(const T &q) const { return get_within_distance(q, 0); }
        
    private:
        class Node {
            public:
                T x;
                map<int, void*> edge;
                
                Node(const T& x) {
                    this->x = x;
                }
                
                ~Node() {
                    for (map<int, void*>::iterator it = edge.begin(); it != edge.end(); ++it) 
                        delete ((Node*)(it->second));
                }
        };
        
        Node *root;
        int (*distance)(const T& x, const T& y, long long& comp);
        int elements;
};

/*template <class T>
int bk_tree<T>::get_within_distance(const T& q, int r, vector<T> *result) const {
    if (!root) return 0;
    int qtt = 0;
    queue<Node*> Q;
    Q.push(root);
    while (not Q.empty()) {
        Node *p = Q.front(); Q.pop();
        int d = distance(q, p->x);
        if (d <= r) {
            ++qtt;
            if (result) result->push_back(p->x);
        }
        map<int, void*>::iterator it = p->edge.upper_bound(d + r);
        if (it != p->edge.begin()) {
            for (--it; it->first >= d - r; --it) {
                Q.push((Node*)(it->second));
                if (it == p->edge.begin()) break;
            }
        }
    }
    return qtt;
}*/

template <class T>
int bk_tree<T>::count_within_distance(const T& q, int r, long long& comp) const {
    if (!root) return 0;
    int qtt = 0;
    queue<Node*> Q;
    Q.push(root);
    while (not Q.empty()) {
        Node *p = Q.front(); Q.pop();
        int d = distance(q, p->x, comp);
        if (d <= r) {
            ++qtt;
        }
        map<int, void*>::iterator it = p->edge.upper_bound(d + r);
        if (it != p->edge.begin()) {
            for (--it; it->first >= d - r; --it) {
                Q.push((Node*)(it->second));
                if (it == p->edge.begin()) break;
            }
        }
    }
    return qtt;
}

template <class T>
void bk_tree<T>::insert(const T& x, long long& comp) {
    if (root) {
        Node *p = root;
        while (p) {
            int d = distance(x, p->x, comp);
            if (d == 0) return;
            if (p->edge.count(d)) p = (Node*)(p->edge[d]);
            else {
                p = ((Node*)(p->edge[d] = new Node(x)));
                ++elements;
            }
        }
    }
    else {
        root = new Node(x);
        ++elements;
    }
}

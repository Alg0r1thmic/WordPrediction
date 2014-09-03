#include <map>
#include "leaf.cc"
using namespace std;

class Node {
    public:
        int level;
        map<int, Node*> edge;
        map<int, Leaf*> leaves;
                
        Node(int l) {
            this->level = l;
        }
              
        ~Node() {
            for (map<int, Node*>::iterator it = edge.begin(); it != edge.end(); ++it) 
                delete (it->second);
            for (map<int, Leaf*>::iterator it = leaves.begin(); it != leaves.end(); ++it) 
                delete (it->second);
        }
};
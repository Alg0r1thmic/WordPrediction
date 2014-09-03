#include <vector>
using namespace std;

class Leaf {
    public:
        vector<wstring> v;

        void insert(const wstring& x) {v.push_back(x);}
};
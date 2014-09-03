#include <iostream>
#include <vector>
#include <typeinfo>
#include <map>
#include <type_traits>
using namespace std;

class test{
	public:
		test(vector<int>& w) {
			this->v=w;
		}
		void printv() {
			for (int i=0; i<v.size(); i++) cout << v[i] << ' ';
				cout << endl;
		}
		void insert(int a) {
			this->v.push_back(a);
		}
		int s() {
			cout << this->lala.size() << endl;
		}

		void t() {
			cout << typeid(this).name() << endl;
		}

	private:
		vector<int> v;
		vector<int> lala;
	
};

class poc{
	public:

		vector<int> v;
		poc(vector<int>& w) {
			this->v=w;
		}
		void printv() {
			for (int i=0; i<v.size(); i++) cout << v[i] << ' ';
				cout << endl;
		}
		void insert(int a) {
			this->v.push_back(a);
		}
		int s() {
			cout << this->lala.size() << endl;
		}

		void t() {
			cout << typeid(this).name() << endl;
		}

	private:
		vector<int> lala;
	
};

int main() {
  std::cout << std::boolalpha;
  std::cout << "is_trivially_destructible:" << std::endl;
  std::cout << "wstring: " << std::is_trivially_destructible<int>::value << std::endl;
  return 0;

}


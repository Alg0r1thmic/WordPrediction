#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
using namespace std;

#define DUMP(x) do { std::wcerr << #x ": " << x << "\n"; } while (0)

int main(){
    using namespace std;

    std::wifstream fdict("utf8.dat", std::ifstream::in);
	std::locale loc ("");
	std::locale::global (loc);   
	fdict.imbue (loc);
	
	wstring s;
    while (fdict >> s ){
    wcout << s << L"\n";
}
   

}

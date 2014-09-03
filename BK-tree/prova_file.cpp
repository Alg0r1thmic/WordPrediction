#include <fstream>
#include <iostream>
#include <locale>
#include <clocale>
using namespace std;

#define DUMP(x) do { std::wcerr << #x ": " << x << "\n"; } while (0)

int main()
{
    // open as a byte stream
    std::wifstream fin("words-lemas.txt", std::ifstream::in);
    std::locale loc ("");
    std::locale::global (loc);
    //DUMP(std::setlocale(LC_ALL, NULL));
    //DUMP(std::setlocale(LC_ALL, ""));    
    fin.imbue (loc);
    // read     
    for(wstring s; fin >> s; )
            wcout << s.substr(1,s.size()-2) << L"\n";
}

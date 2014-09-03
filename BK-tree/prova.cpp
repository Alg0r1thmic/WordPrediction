#include <iostream>
#include <locale>
#include <clocale>

#define DUMP(x) do { std::wcerr << #x ": " << x << "\n"; } while (0)

int main(){
    using namespace std;

    std::locale loc ("");
    std::locale::global (loc);
    DUMP(std::setlocale(LC_ALL, NULL));
    DUMP(std::setlocale(LC_ALL, ""));    
    wcin.imbue (loc);

    DUMP (wcin.good());
    wstring s;
    wchar_t aChar = 0;
	
    while (wcin >> s ){
    DUMP (wcin.good());
    DUMP ((int)aChar);
    wcout << L"You entered " << s << L" " << s.size() << L" .\n";
    wstring r = L"úí";
    for (int i=0; i<s.size(); i++) {
	wcout << s[i] << L"\n";
	if (s[i] == r[0] or s[i] == r[1]) wcout << L"one found!\n";
    }
    }

}

#include <iostream>
#include <fstream>

#define FILE_MODE true
#if FILE_MODE
    std::fstream file;
    #define INPUT file
#else
    #define INPUT cin
#endif

using namespace std;

int main()
{
    string lineOfText;
    #if FILE_MODE
        ::file.open("hypergrade.txt", ios::in );
    #endif
        do {
            getline(INPUT, lineOfText);
            cout << lineOfText << endl;
        } while(INPUT.good()&&lineOfText != ".end");

    #if FILE_MODE
        ::file.close();
    #endif
    return 0;
}

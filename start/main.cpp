#include "instructions_map.h"

void tester(string in_in, map<string,Format> &Instrucs){
    map<string,Format>::iterator kindaPointer; // Treat it like a pointer.
    kindaPointer = Instrucs.find(in_in);
    if (kindaPointer == Instrucs.end())
        cout << endl << in_in << " is not a valid instruction"<<endl;
    else{
        cout <<endl<<in_in <<" is in "<< kindaPointer->second.form
             <<" format, and style "  << kindaPointer->second.style << endl;
        cout <<"It has an opcode of " << kindaPointer->second.opcode
             <<" and function code "  << kindaPointer->second.func << endl;
    }
}
int main() {
    map<string,Format> Instrucs;
    fillMap(Instrucs);

    tester("movz", Instrucs);
    tester("sllv", Instrucs);
    tester("slti", Instrucs);
    tester("ORI", Instrucs);
    tester("tlti", Instrucs);
    tester("potato", Instrucs);
    tester("jal", Instrucs);
    return 0;
}

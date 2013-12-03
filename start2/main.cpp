#include <iostream>
#include <map>
using namespace std;

void outputHex(int);

class Format{
public:
    char form, style;
    int opcode, func;

    Format(char f, char s, int o, int fun){ // 4 arg constructor
        init(f,s,o,fun);
    }
    Format(char f, char s, int o){ // 3 arg constructor
        init(f,s,o,0);
    }
    Format(){ // Mapvoid outputHex(int someInt) requires the class have a default constructor.
    }         // This one does basically nothing.
private:
    void init(char &f, char &s, int &o, int fun){
        form = f;
        style = s;
        opcode = o;
        func = fun;
        return;
    }
};

void fillMap(map<string,Format> &Instrucs) {
    /* Below I add each instruction to the Instrucs map
     * The grouping, ordering, and category descriptions are shamelessly
     * copied from Tom Murphy's hypergrade instructions pdf
     */

    //R format with rd, rs, and rt

    Instrucs["movz"]   = Format('R', '1', 0x00, 0x0A);
    Instrucs["movn"]   = Format('R', '1', 0x00, 0x0B);
    Instrucs["add"]    = Format('R', '1', 0x00, 0x20);
    Instrucs["addu"]   = Format('R', '1', 0x00, 0x21);
    Instrucs["sub"]    = Format('R', '1', 0x00, 0x22);
    Instrucs["subu"]   = Format('R', '1', 0x00, 0x23);
    Instrucs["and"]    = Format('R', '1', 0x00, 0x24);
    Instrucs["or"]     = Format('R', '1', 0x00, 0x25);
    Instrucs["xor"]    = Format('R', '1', 0x00, 0x26);
    Instrucs["nor"]    = Format('R', '1', 0x00, 0x27);
    Instrucs["slt"]    = Format('R', '1', 0x00, 0x2A);
    Instrucs["sltu"]   = Format('R', '1', 0x00, 0x2B);
    Instrucs["mul"]    = Format('R', '1', 0x1C, 0x02);

    //R format with rd, rt, and rs

    Instrucs["sllv"]   = Format('R', '2', 0x00, 0x04);
    Instrucs["srlv"]   = Format('R', '2', 0x00, 0x06);
    Instrucs["srav"]   = Format('R', '2', 0x00, 0x07);

    //R format with rd, rt, and shiftAmt

    Instrucs["sll"]    = Format('R', '3', 0x00, 0x00);
    Instrucs["srl"]    = Format('R', '3', 0x00, 0x02);
    Instrucs["sra"]    = Format('R', '3', 0x00, 0x03);

    //R format with rs and rt

    Instrucs["mult"]   = Format('R', '4', 0x00, 0x18);
    Instrucs["multu"]  = Format('R', '4', 0x00, 0x19);
    Instrucs["div"]    = Format('R', '4', 0x00, 0x1A);
    Instrucs["divu"]   = Format('R', '4', 0x00, 0x1B);
    Instrucs["tge"]    = Format('R', '4', 0x00, 0x30);
    Instrucs["tgeu"]   = Format('R', '4', 0x00, 0x31);
    Instrucs["tlt"]    = Format('R', '4', 0x00, 0x32);
    Instrucs["tltu"]   = Format('R', '4', 0x00, 0x33);
    Instrucs["teq"]    = Format('R', '4', 0x00, 0x34);
    Instrucs["tne"]    = Format('R', '4', 0x00, 0x36);
    Instrucs["madd"]   = Format('R', '4', 0x1C, 0x00);
    Instrucs["maddu"]  = Format('R', '4', 0x1C, 0x01);
    Instrucs["msub"]   = Format('R', '4', 0x1C, 0x04);
    Instrucs["msubu"]  = Format('R', '4', 0x1C, 0x05);

    //R format with rd and rs

    Instrucs["clz"]    = Format('R', '5', 0x1C, 0x20);
    Instrucs["clo"]    = Format('R', '5', 0x1C, 0x21);

    //R format with rs and optional rd that defaults to 31

    Instrucs["jalr"]   = Format('R', '6', 0x00, 0x09);

    //R format with rd only

    Instrucs["mfhi"]   = Format('R', '7', 0x00, 0x10);
    Instrucs["mflo"]   = Format('R', '7', 0x00, 0x12);

    //R format with rs only

    Instrucs["jr"]     = Format('R', '8', 0x00, 0x08);
    Instrucs["mthi"]   = Format('R', '8', 0x00, 0x11);
    Instrucs["mtlo"]   = Format('R', '8', 0x00, 0x13);

    //R format with rd holding an integer value

    Instrucs["break"]  = Format('R', '9', 0x00, 0x0D);

    //R format with no registers

    Instrucs["nop"]    = Format('R', 'a', 0x00, 0x00);
    Instrucs["syscall"]= Format('R', 'a', 0x00, 0x0C);

    //I format with rt and rs, and immediate value

    Instrucs["addi"]   = Format('I', '1', 0x08);
    Instrucs["addiu"]  = Format('I', '1', 0x09);
    Instrucs["slti"]   = Format('I', '1', 0x0A);
    Instrucs["sltiu"]  = Format('I', '1', 0x0B);
    Instrucs["andi"]   = Format('I', '1', 0x0C);
    Instrucs["ori"]    = Format('I', '1', 0x0D);
    Instrucs["xori"]   = Format('I', '1', 0x0E);

    //I format with rs and rt and branch label

    Instrucs["beq"]    = Format('I', '2', 0x04);
    Instrucs["bne"]    = Format('I', '2', 0x05);

    //I format with rs and branch label, and rt holding a
    //kind of function code

    Instrucs["bltz"]   = Format('I', '3', 0x01, 0x00);
    Instrucs["bgez"]   = Format('I', '3', 0x01, 0x01);
    Instrucs["bgezal"] = Format('I', '3', 0x01, 0x11);
    Instrucs["blez"]   = Format('I', '3', 0x06, 0x00);
    Instrucs["bgtz"]   = Format('I', '3', 0x07, 0x00);
    Instrucs["bltzal"] = Format('I', '3', 0x07, 0x10);

    //I format with rt and immediate value

    Instrucs["lui"]    = Format('I', '4', 0x0F);

    //I format with rs and immediate value, and rt holding
    //a psuedo function code

    Instrucs["tgei"]   = Format('I', '5', 0x01, 0x08);
    Instrucs["tgeiu"]  = Format('I', '5', 0x01, 0x09);
    Instrucs["tlti"]   = Format('I', '5', 0x01, 0x0A);
    Instrucs["tltiu"]  = Format('I', '5', 0x01, 0x0B);
    Instrucs["teqi"]   = Format('I', '5', 0x01, 0x0C);
    Instrucs["tneqi"]  = Format('I', '5', 0x01, 0x0E);

    //I format load/store with rt and immediate value and rs
    //representing the address

    Instrucs["lb"]     = Format('I', '6', 0x20);
    Instrucs["lh"]     = Format('I', '6', 0x21);
    Instrucs["lw"]     = Format('I', '6', 0x23);
    Instrucs["lbu"]    = Format('I', '6', 0x24);
    Instrucs["lhu"]    = Format('I', '6', 0x25);
    Instrucs["sb"]     = Format('I', '6', 0x28);
    Instrucs["sh"]     = Format('I', '6', 0x29);
    Instrucs["sw"]     = Format('I', '6', 0x2B);

    //J format

    Instrucs["j"]      = Format('J', '1', 0x02);
    Instrucs["jal"]    = Format('J', '1', 0x03);

    return;
}
class Assem{
public:
    map<string,Format>::iterator kindaPointer; // Treat it like a pointer.
    string in_in;
    void tester(string, map<string,Format> &);
    int assem1(){
        int temp = (kindaPointer->second.opcode)<<26;
        char form = kindaPointer->second.form;
        if(form == 'R'){
            return temp+r();
        }else if(form =='I'){
            return temp+i();
        }else if(form =='J'){
            return temp+j();
        }else {
            cout << "ERROR! ERROR! VERY BAD!"<<endl;
            return 0;
        }
    }
private:
    int r(){
        talk();
        return 0;
    }
    int i(){
        talk();
        return 0;
    }
    int j(){
        talk();
        return 0;
    }
    void talk(){
        cout <<endl<<in_in <<" is in "<< kindaPointer->second.form
             <<" format, and style "  << kindaPointer->second.style << endl;
        cout <<"It has an opcode of " << kindaPointer->second.opcode
             <<" and function code "  << kindaPointer->second.func << endl;
    }
};
void Assem::tester(string s, map<string,Format> &Instrucs){
    in_in = s;
    int counter = 0;
    kindaPointer = Instrucs.find(in_in);
    if (kindaPointer == Instrucs.end()){
        //cout << endl << in_in << " is not a valid instruction"<< endl;
        return;
    }else{
        int bytes = assem1();
        cout<< bytes<<endl<<endl;
        ::outputHex(bytes);
        counter++;
        if (counter == 3){
            cout<<endl;
        }else if(counter !=4 && counter %4 == 0){
            cout<<endl;
        }
        return;
    }
}
void outputHex(int someInt){
/*  This function is completely superfluos. Because of the line 'cout<<hex;' at the
 *  beginning of main, 'cout<<someInt<<" ";' will produce the same output.
 */
    for (int n=1;n<=8;n++){
        int temp = (someInt>>(4*(8-n)))&15;
        switch (temp){
            case 10:
                cout << "a";
                break;
            case 11:
                cout << "b";
                break;
            case 12:
                cout << "c";
                break;
            case 13:
                cout << "d";
                break;
            case 14:
                cout << "e";
                break;
            case 15:
                cout << "f";
                break;
            default:
                cout << temp;
        }
    }
    cout << " ";
}
int main() {
    cout<<hex;
    cout<<"[400024]"<<endl;
    map<string,Format> Instrucs;
    fillMap(Instrucs);
    Assem instance = Assem();
    string s1;
    cin >> s1;
    while(s1 !=".end"){
        if(s1==".data"){
            while(s1 !=".text" && s1 !=".end"){
                //Save either input or assembled bytes (with "[10010000]\n" tag)
                //to a file
                cin >> s1;
            }
            if (s1 ==".end")
                break;
        } else {
            instance.tester(s1, Instrucs);
            cin >> s1;
        }
    }
    return 0;
}

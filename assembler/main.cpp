//#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

ifstream hyper;

vector<string> textInstrucs;
vector<int> dataOuts;
map<string,int> labelsMap;
int characters, dataInHex;
string dataString;
const int MAX_OPERANDS = 64;
const int LAST_OPERAND = MAX_OPERANDS-1;
string regNames[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
    "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0",
    "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0",
    "$k1", "$gp", "$sp", "$fp", "$ra"};

void outputHex(int);
int getRegNum(string);

class Definition{
public:
    char form, style;
    int opcode, func;

    Definition(char f, char s, int o, int fun){ // 4 arg constructor
        init(f,s,o,fun);
    }
    Definition(char f, char s, int o){ // 3 arg constructor
        init(f,s,o,0);
    }
    Definition(){   // Map requires the class have a default constructor.
    }               // This one does basically nothing.
private:
    void init(char &f, char &s, int &o, int fun){
        form = f;
        style = s;
        opcode = o;
        func = fun;
        return;
    }
};

void fillMap(map<string,Definition> &Dictionary) {
    /* Below I add each instruction to the Dictionary map
     * The grouping, ordering, and category descriptions are shamelessly
     * copied from Tom Murphy's hypergrade instructions pdf.
     *
     * I think this code is pretty, but it's not efficient.
     * If I'm not mistaken, a copy is made of each of those Definition objects
     * and that copy has the scope of Dictionary. The copy is what the map
     * actually points to. GCC has copy-elision enabled by default, so this
     * may not be an issue.
     */

    //R format with rd, rs, and rt

    Dictionary["movz"]   = Definition('R', '1', 0x00, 0x0A);
    Dictionary["movn"]   = Definition('R', '1', 0x00, 0x0B);
    Dictionary["add"]    = Definition('R', '1', 0x00, 0x20);
    Dictionary["addu"]   = Definition('R', '1', 0x00, 0x21);
    Dictionary["sub"]    = Definition('R', '1', 0x00, 0x22);
    Dictionary["subu"]   = Definition('R', '1', 0x00, 0x23);
    Dictionary["and"]    = Definition('R', '1', 0x00, 0x24);
    Dictionary["or"]     = Definition('R', '1', 0x00, 0x25);
    Dictionary["xor"]    = Definition('R', '1', 0x00, 0x26);
    Dictionary["nor"]    = Definition('R', '1', 0x00, 0x27);
    Dictionary["slt"]    = Definition('R', '1', 0x00, 0x2A);
    Dictionary["sltu"]   = Definition('R', '1', 0x00, 0x2B);
    Dictionary["mul"]    = Definition('R', '1', 0x1C, 0x02);

    //R format with rd, rt, and rs

    Dictionary["sllv"]   = Definition('R', '2', 0x00, 0x04);
    Dictionary["srlv"]   = Definition('R', '2', 0x00, 0x06);
    Dictionary["srav"]   = Definition('R', '2', 0x00, 0x07);

    //R format with rd, rt, and shiftAmt

    Dictionary["sll"]    = Definition('R', '3', 0x00, 0x00);
    Dictionary["srl"]    = Definition('R', '3', 0x00, 0x02);
    Dictionary["sra"]    = Definition('R', '3', 0x00, 0x03);

    //R format with rs and rt

    Dictionary["mult"]   = Definition('R', '4', 0x00, 0x18);
    Dictionary["multu"]  = Definition('R', '4', 0x00, 0x19);
    Dictionary["div"]    = Definition('R', '4', 0x00, 0x1A);
    Dictionary["divu"]   = Definition('R', '4', 0x00, 0x1B);
    Dictionary["tge"]    = Definition('R', '4', 0x00, 0x30);
    Dictionary["tgeu"]   = Definition('R', '4', 0x00, 0x31);
    Dictionary["tlt"]    = Definition('R', '4', 0x00, 0x32);
    Dictionary["tltu"]   = Definition('R', '4', 0x00, 0x33);
    Dictionary["teq"]    = Definition('R', '4', 0x00, 0x34);
    Dictionary["tne"]    = Definition('R', '4', 0x00, 0x36);
    Dictionary["madd"]   = Definition('R', '4', 0x1C, 0x00);
    Dictionary["maddu"]  = Definition('R', '4', 0x1C, 0x01);
    Dictionary["msub"]   = Definition('R', '4', 0x1C, 0x04);
    Dictionary["msubu"]  = Definition('R', '4', 0x1C, 0x05);

    //R format with rd and rs

    Dictionary["clz"]    = Definition('R', '5', 0x1C, 0x20);
    Dictionary["clo"]    = Definition('R', '5', 0x1C, 0x21);

    //R format with rs and optional rd that defaults to 31

    Dictionary["jalr"]   = Definition('R', '6', 0x00, 0x09);

    //R format with rd only

    Dictionary["mfhi"]   = Definition('R', '7', 0x00, 0x10);
    Dictionary["mflo"]   = Definition('R', '7', 0x00, 0x12);

    //R format with rs only

    Dictionary["jr"]     = Definition('R', '8', 0x00, 0x08);
    Dictionary["mthi"]   = Definition('R', '8', 0x00, 0x11);
    Dictionary["mtlo"]   = Definition('R', '8', 0x00, 0x13);

    //R format with rd holding an integer value

    Dictionary["break"]  = Definition('R', '9', 0x00, 0x0D);

    //R format with no registers

    Dictionary["nop"]    = Definition('R', 'a', 0x00, 0x00);
    Dictionary["syscall"]= Definition('R', 'a', 0x00, 0x0C);

    //I format with rt and rs, and immediate value

    Dictionary["addi"]   = Definition('I', '1', 0x08);
    Dictionary["addiu"]  = Definition('I', '1', 0x09);
    Dictionary["slti"]   = Definition('I', '1', 0x0A);
    Dictionary["sltiu"]  = Definition('I', '1', 0x0B);
    Dictionary["andi"]   = Definition('I', '1', 0x0C);
    Dictionary["ori"]    = Definition('I', '1', 0x0D);
    Dictionary["xori"]   = Definition('I', '1', 0x0E);

    //I format with rs and rt and branch label

    Dictionary["beq"]    = Definition('I', '2', 0x04);
    Dictionary["bne"]    = Definition('I', '2', 0x05);

    //I format with rs and branch label, and rt holding a
    //kind of function code

    Dictionary["bltz"]   = Definition('I', '3', 0x01, 0x00);
    Dictionary["bgez"]   = Definition('I', '3', 0x01, 0x01);
    Dictionary["bgezal"] = Definition('I', '3', 0x01, 0x11);
    Dictionary["blez"]   = Definition('I', '3', 0x06, 0x00);
    Dictionary["bgtz"]   = Definition('I', '3', 0x07, 0x00);
    Dictionary["bltzal"] = Definition('I', '3', 0x01, 0x10);

    //I format with rt and immediate value

    Dictionary["lui"]    = Definition('I', '4', 0x0F);

    //I format with rs and immediate value, and rt holding
    //a psuedo function code

    Dictionary["tgei"]   = Definition('I', '5', 0x01, 0x08);
    Dictionary["tgeiu"]  = Definition('I', '5', 0x01, 0x09);
    Dictionary["tlti"]   = Definition('I', '5', 0x01, 0x0A);
    Dictionary["tltiu"]  = Definition('I', '5', 0x01, 0x0B);
    Dictionary["teqi"]   = Definition('I', '5', 0x01, 0x0C);
    Dictionary["tneqi"]  = Definition('I', '5', 0x01, 0x0E);

    //I format load/store with rt and immediate value and rs
    //representing the address

    Dictionary["lb"]     = Definition('I', '6', 0x20);
    Dictionary["lh"]     = Definition('I', '6', 0x21);
    Dictionary["lw"]     = Definition('I', '6', 0x23);
    Dictionary["lbu"]    = Definition('I', '6', 0x24);
    Dictionary["lhu"]    = Definition('I', '6', 0x25);
    Dictionary["sb"]     = Definition('I', '6', 0x28);
    Dictionary["sh"]     = Definition('I', '6', 0x29);
    Dictionary["sw"]     = Definition('I', '6', 0x2B);

    //J format

    Dictionary["j"]      = Definition('J', '1', 0x02);
    Dictionary["jal"]    = Definition('J', '1', 0x03);

    return;
}

class Assem{
public:
    map<string,Definition>::iterator kindaPointer; // Treat it like a pointer.
    string string0, mnemonic, label;
    char form, style;
    int func;
    int spaceLoc, counter;
    string operands[MAX_OPERANDS];
    void getLineJK();
    void loadOperands();
    void tester(map<string,Definition> &);
    int assem1(){
        int temp = (kindaPointer->second.opcode)<<26;
        form = kindaPointer->second.form;
        style = kindaPointer->second.style;
        func = kindaPointer->second.func;
        if(form == 'R'){
            return temp+r();
        }else if(form =='I'){
            return temp+i();
        }else if(form =='J'){
            return temp+j();
        }else {
            //cout << "ERROR! ERROR! VERY BAD!"<<endl;
            return 0;
        }
    }
private:
    int r1(int rs, int rt, int rd, int shft){
        return (::getRegNum(operands[rs])<<21) + (::getRegNum(operands[rt])<<16) +
        (::getRegNum(operands[rd])<<11) + (::getRegNum(operands[shft])<<6) + func;
    }
    int r(){
        switch (style){
            case '1':
                return r1(1,2,0,LAST_OPERAND); // Lazy hack
                break;
            case '2':
                return r1(2,1,0,LAST_OPERAND);
                break;
            case '3':
                return (::getRegNum(operands[LAST_OPERAND])<<21) + (::getRegNum(operands[1])<<16) +
                    (::getRegNum(operands[0])<<11) + (atoi(operands[2].c_str())<<6) + func;
                break;
            case '4':
                return r1(0,1,LAST_OPERAND,LAST_OPERAND);
                break;
            case '5':
                return r1(1,0,0,LAST_OPERAND);
                break;
            case '6':
                return r1(0,LAST_OPERAND,0,LAST_OPERAND); // Noncompliant.
                break;
            case '7':
                return r1(LAST_OPERAND,LAST_OPERAND,0,LAST_OPERAND);
                break;
            case '8':
                return r1(0,LAST_OPERAND,LAST_OPERAND,LAST_OPERAND);
                break;
            case '9':
                return (::getRegNum(operands[LAST_OPERAND])<<21) + (::getRegNum(operands[LAST_OPERAND])<<16) +
                     (atoi(operands[0].c_str())<<11)+ (::getRegNum(operands[LAST_OPERAND])<<6) + func;
                break;
            case 'a':
                return r1(LAST_OPERAND,LAST_OPERAND,LAST_OPERAND,LAST_OPERAND);
                break;
        }
        return -1;
    }
    int i(){
        //
        return 0;
    }
    int j(){
        //
        return 0;
    }
    void removeJunk(char junk){
        spaceLoc = 0;
        while (true){
            spaceLoc = string0.find(junk); // More like future spaceLoc
            if (spaceLoc == -1) {
                break;
            } else {
                string0.replace(spaceLoc, 1," "); // Now it's a spaceLoc
            }
        }
    }
};
Assem instance;
void Assem::getLineJK(){
    getline(::hyper, string0);
    //getline(cin, string0);
    int poundLoc = string0.find('#');
    string0 = string0.substr(0,poundLoc-1);
    removeJunk('\t');
    removeJunk('\f');
    int colonLoc = string0.find(':');
    if (colonLoc != -1) {
        label = string0.substr(0,colonLoc-1);
        string0 = string0.substr(string0.find(':')+1,-1); // Remove labels
    }
    while (string0[0]==' '){
        string0 = string0.substr(1,-1);
    }
    spaceLoc = string0.find(' ');
    mnemonic = string0.substr(0,spaceLoc);
}

void Assem::loadOperands(){ // I may have chosen the absolute worst way to do this.
    int i=0;
    for (int k=0; k<MAX_OPERANDS; k++){
        operands[k] = "$zero"; // This is for the lazy hack in r1.
    }
    operands[1] = "$ra"; // An even lazier hack. Will be overwriten in most cases.
    int nextSpace;
    while ((spaceLoc !=-1)&&(i<MAX_OPERANDS-1)&&( (string0.find(' ',spaceLoc+1)>0)||
            (string0.find(',',spaceLoc+1)>0) )){
        // The above means: "while there's still chunks of text in string0 that need
        // to be saved to operands[], do this:"
        if ((string0.find(' ',spaceLoc+1)<(string0.find(',',spaceLoc+1)))&&
                string0.find(' ',spaceLoc+1)>0) {
            // "If the next space comes before the next comma, and the next space
            // is not in position '-1':"
            nextSpace = string0.find(' ',spaceLoc+1);
            if (nextSpace != spaceLoc+1){
                // "Don't bother saving the little string if it's only 1 character."
                operands[i] = string0.substr(spaceLoc+1,nextSpace-spaceLoc-1);
                //cout << operands[i] << endl; // for debugging
                i++;
            }
            spaceLoc = nextSpace;
        } else {
            // The while loop conditions plus the if conditions mean that this
            // line only runs if a comma exists on the line after spaceLoc but
            // before the next space.
            nextSpace = string0.find(',',spaceLoc+1); // COMMA
            if (nextSpace != spaceLoc+1){
                // Don't bother saving the little string if it's only 1 character.
                operands[i] = string0.substr(spaceLoc+1,nextSpace-spaceLoc-1);
                //cout << operands[i] << endl; // for debugging
                i++;
            }
            spaceLoc = nextSpace;
        }
    }
}

void Assem::tester(map<string,Definition> &Instrucs){
    spaceLoc = string0.find(' ');
    mnemonic = string0.substr(0,spaceLoc);
    kindaPointer = Instrucs.find(mnemonic);
    if (kindaPointer == Instrucs.end()){
        //cout << endl << string1 << " is not a valid instruction"<< endl;
        return;
    }else{
        labelsMap[label] = counter;
        loadOperands();
        int bytes = assem1();
        ::outputHex(bytes);
        counter++;
        if (counter %4 == 3){
            //cout<<"\n";
        }
        return;
    }
}
void outputHex(int someInt){
    for (int n=1;n<=8;n++){ // From left to right, cout the hex digits of someInt
        ((someInt>>(4*(8-n)))&15);
        //cout << ((someInt>>(4*(8-n)))&15);
    }
    //cout << " ";
}
int getRegNum(string reg){
    if (reg == regNames[31]) {
        return 31; // "$ra" returns 31
    } else if (find(regNames, regNames+31, reg)==regNames+31){
        reg = reg.substr(reg.find('$')+1,-1);
        return atoi(reg.c_str()); // "$25" returns 25
    } else {
        return (find(regNames, regNames+31, reg))-regNames; // "$sp" returns 29
    }
}
void dataReader(void(*FunctionPointer)()){
    string readerString = instance.string0;
    int start = instance.string0.find(' ');
    if (start != -1) {
        readerString = instance.string0.substr(start,-1); //skip over the mnemonic
        while (readerString[0]==' '){ //remove leading spaces
            readerString = readerString.substr(1,-1);
        }
    }
    dataString = readerString;
    start = 0;
    int commaLoc = 0;
    do {
        commaLoc = readerString.find(',',start);
   //         cout <<dataString<<"commaLoc = " << commaLoc<< endl;
        if(commaLoc !=-1){
            dataString = readerString.substr(start,commaLoc-start);
    //        cout <<dataString<<"commaLoc = " << commaLoc<< endl;
            FunctionPointer();
            start = commaLoc+1;
        } else {
            dataString = readerString.substr(start,commaLoc-start);
            FunctionPointer();
        }
    }while(commaLoc != -1);
}
void asciiFun(){
    int quoteLoc = dataString.find('"')+1;
    for (int i = quoteLoc; i<(dataString.find('"',quoteLoc)); i++){
            dataInHex = dataInHex + ((int)dataString[i]<<(8*(characters)));
            characters++;
            if (characters == 4){
                dataOuts.push_back(dataInHex);
 //               cout <<"dataInHex = "<<dataInHex<<endl;
                dataInHex = 0;
                characters = 0;
            }
        }
}
void asciizFun(){
    asciiFun();
    characters++;
    if (characters == 4){
        dataOuts.push_back(dataInHex);
 //       cout <<"ZZZdataInHex = "<<dataInHex<<endl;
        dataInHex = 0;
        characters = 0;
    }
}
void floatFun(){
    if (characters != 0){
        characters = 0;
        dataOuts.push_back(dataInHex);
    }
    float flo = atof(dataString.c_str());
    long *point = (long *)&flo; //The baddest of practices.
//    cout << "the contents of " << point << " are " << *point << endl;
    dataInHex = (*point)&(-1); //4294967295 aka 0xffffff
    dataOuts.push_back(dataInHex);
    dataInHex = 0;
}
void spaceFun(){
    while (dataString[0]==' '){
        dataString = dataString.substr(1,-1);
    }
//    cout << dataString << " " << dataString.c_str();
    int temp = atoi(dataString.c_str());
//    cout <<endl<<endl<< temp <<endl <<endl;
    for (int i = 0; i< temp; i++){
        characters++;
        if (characters == 4){
            dataOuts.push_back(dataInHex);
//            cout <<"ss dataInHex = "<<dataInHex<<endl;
            dataInHex = 0;
            characters = 0;
        }
    }
}
void wordFun(){
    if (characters != 0){
        characters = 0;
        dataOuts.push_back(dataInHex);
    }
    int temp = dataString.find('x');
    if (temp != -1){
        dataString = dataString.substr(temp+1,-1);
        temp = 0;
        for (int n=0;n<dataString.length();n++){
            if ((dataString[n] >='0')&&(dataString[n]<='9')){
                temp = (temp<<4) + (dataString[n]-'0');
            }
        }
        dataInHex = temp;
        dataOuts.push_back(dataInHex);
    } else {
    //   cout << dataString << endl;
        temp = atoi(dataString.c_str());
        dataInHex = temp;
        dataOuts.push_back(dataInHex);
    }
    dataInHex = 0;
}
void byteFun(){
    while ((dataString[0]==' ')||(dataString[0]=='\'')){
        dataString = dataString.substr(1,-1);
    }
    if ((dataString[0] >= 45)&&(dataString[0] <= 57)){
        dataInHex += (atoi(dataString.c_str())&255)<<(8*characters);
    } else {
        dataInHex += ((int)dataString[0]<<(8*(characters)));
    }
    characters++; //More acurately 'bytes++'.
    if (characters == 4){
        dataOuts.push_back(dataInHex);
        //cout <<"dataInHex = "<<dataInHex<<endl;
        dataInHex = 0;
        characters = 0;
    }
}
void doubleFun(){
    if (characters != 0){
        characters = 0;
        dataOuts.push_back(dataInHex);
    }
    double dub = atof(dataString.c_str());
    long long *point = (long long *)&dub; //The baddest of practices.
//    cout << "the contents of " << point << " are " << *point << endl;
    dataInHex = (*point)&(-1); //4294967295 aka 0xffffff
    dataOuts.push_back(dataInHex);
    dataInHex = (*point)>>32;
    dataOuts.push_back(dataInHex);
    dataInHex = 0;
}

int main() {
    map<string,Definition> Dictionary;
    fillMap(Dictionary);
    instance = Assem();
for (int runs=0;runs<300;runs++){
    hyper.open ("hypergrade.txt", ios::in);

    textInstrucs.reserve(260);  //When dynamic arrays are completely filled, more
    dataOuts.reserve(32);       //memory must be allocated. This often involves
                                //copying the whole array to a new location;
                                //which is expensive. The default sizes to the left
                                //were arbitrarily chosen but should be sufficient
                                //in the majority of cases.
    int dataExists = 0;
    //cout<<hex;
    //cout<<"[400024]"<<endl;
    instance.counter = 0;

    do{
        instance.getLineJK();
        if(instance.mnemonic==".data"){
            dataExists = 1;
            characters = 0;
            dataInHex = 0;
            while(instance.mnemonic !=".text" && instance.mnemonic !=".end"){
                if (instance.mnemonic == ".asciiz") {
                    dataReader(&asciizFun);
                } else if (instance.mnemonic == ".ascii") {
                    dataReader(&asciiFun);
                } else if (instance.mnemonic == ".space") {
                    dataReader(&spaceFun);
                } else if (instance.mnemonic == ".word") {
                    dataReader(&wordFun);
                } else if (instance.mnemonic == ".byte") {
                    dataReader(&byteFun);
                } else if (instance.mnemonic == ".float") {
                    dataReader(&floatFun);
                } else if (instance.mnemonic == ".double") {
                    dataReader(&doubleFun);
                }
                instance.getLineJK();
            }
        } else {
            textInstrucs.push_back(instance.string0);
        }
    }while(instance.mnemonic !=".end");
    if (characters !=0){
        dataOuts.push_back(dataInHex);
    }
    for(int i=0; i< textInstrucs.size(); i++){
        instance.string0 = textInstrucs[i];
        instance.tester(Dictionary);
    }

    hyper.close();

    //cout << endl;
    if (dataExists == 1){
        //cout << "[10010000]"<<endl;
        int ii = 1;
        while (ii <= (int)dataOuts.size()) {
            ::outputHex(dataOuts[ii-1]);
            if (ii%4 == 0){
                //cout<<endl;
            }
            ii++; //Not sure why I didn't use a for-loop.
        }
        //cout << endl;
    }
}
    return 0;
}

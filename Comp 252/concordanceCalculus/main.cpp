#include <iostream>
#include <algorithm>

using namespace std;

//positionOnLine;

struct InputLine {
    string lineOfText;
    string box[];

    InputLine(){
        getline(cin, lineOfText);
        putWordsInTheirBoxes();
    }

    void putWordsInTheirBoxes(){
        return;
    }

    bool itFits(){
 //       find_if(box.begin,box.end,( bothExist(a[i],b[i]) && areUnequal(a[i],b[i]) )){
        if(1){
            return false;
        }
        return true;
    }
    bool hasAColon(){
        ///
        return true;
    }
    bool looksLikeMath(){
        ///
        return true;
    }
} theInput;

void loadALine() {
    ///
}

void readInputLine() {
    theInput = InputLine();
}

void loadAllTheLinesIntoTheMap(){
    loadALine();
}

void outputALine(){
    cout << "Hi" << endl;
}

void outputAllTheLinesInTheMap(){
    outputALine();
}

void simplifyAndEcho(){
    cout << "Hello" << endl;
}

void simplifyAndEchoAllTheEquations(){
    simplifyAndEcho();
}

int main()
{
    readInputLine();
    if (theInput.looksLikeMath()){
        if (theInput.hasAColon()) {
            loadAllTheLinesIntoTheMap();
            simplifyAndEchoAllTheEquations();
        } else {
        simplifyAndEcho();
        }
    } else {
        loadAllTheLinesIntoTheMap();
        outputAllTheLinesInTheMap();
    }
    return EXIT_SUCCESS;
}

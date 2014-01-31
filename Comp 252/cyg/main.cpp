#include <iostream>
#include <algorithm>
#include <pthread.h>

using namespace std;

//positionOnLine;

struct InputLine {
    string lineOfText;

    InputLine(){
        getline(cin, lineOfText);
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

struct lineOfWords {
    string box[5];

    lineOfWords(){
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
};

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
    cout << "..starting up.." << endl;
//    readInputLine();
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

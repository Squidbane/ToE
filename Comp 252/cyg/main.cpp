/* This file can be found at: github.com/Squidbane/ToE/tree/master/Comp 252/cyg/main.cpp */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <vector>
#include <map>
#include <pthread.h>

using namespace std;
#define DEBUG_MODE true
#define FILE_MODE true
#if FILE_MODE
    fstream file;
    #define INPUT file
#else
    #define INPUT cin
#endif

struct RawLine {
    string lineOfText;

    RawLine(){
        getline(INPUT, lineOfText);
    }

    void refresh(){
        getline(INPUT, lineOfText);
        return;
    }

    bool refreshFailed(){
        if(!::INPUT.good() || lineOfText == ".end") {
            return true;
        } else {
            return false;
        }
    }

    bool hasAColon(){
        //
        return true;
    }
    bool looksLikeMath(){
        //
        return false;
    }
} theInput;

struct RefinedLine {
    vector<string> words;

    RefinedLine(){
        putWordsInTheirBoxes();
    }

    void putWordsInTheirBoxes(){
        return;
    }
};

struct OutputLine {
    vector<string> leftWing;
    vector<string> rightWing;
    vector<string>::iterator it;

    OutputLine(vector<string> words){
        copy(words.begin()+1, words.end(), rightWing.begin());
        reverse_copy(words.begin(), words.end(), leftWing.begin()); //end->back
    }

    bool add(vector<string> words){
        if(search(rightWing.begin(), rightWing.end(), // haystack
                  words.begin(), words.end()) != rightWing.end()) {
            return true;
        } else if (search(rightWing.begin(), rightWing.end(), //end->back
                          words.begin(), words.end()) != rightWing.end()) { //end->back *2
            rightWing.push_back(words.back());
            return true;
        } else {
            reverse(words.begin(),words.end());
            if(search(leftWing.begin(), leftWing.end(),
                      words.begin(), words.end()) != leftWing.end()) {
                return true;
            } else if (search(leftWing.begin(), leftWing.end(), //end->back
                              words.begin(), words.end()) != leftWing.end()) { //end->back *2
                leftWing.push_back(words.back());
                return true;
            } else {
                return false;
            }
        }
    }
    string stringify(){
        reverse(leftWing.begin(),leftWing.end());
        return  accumulate(leftWing.begin(), leftWing.end(), string(" ")) + string(" ") +
                accumulate(rightWing.begin()+4, rightWing.end(), string(" "));
    }
};

void loadALine() {
    theInput.refresh();
}

//void loadAllTheLinesIntoTheMap(){
//    loadALine();
//}

void outputALine(){
    #if DEBUG_MODE
        cout << "Hi" << endl;
    #endif
}

void outputAllTheLinesInTheMap(){
    outputALine();
}

void simplifyAndEcho(){
    #if DEBUG_MODE
        cout << "Hello" << endl;
    #endif
}

void simplifyAndEchoAllTheEquations(){
    simplifyAndEcho();
}

string uglifyThis(string pretty) {
    string ugly = pretty;
    int colonLocation = ugly.find(':');
    int endLocation = ugly.length();
    for(unsigned int i=0; i < (endLocation - colonLocation); i++){
        ugly.insert(ugly.begin()+colonLocation+1, 'x');
    }
    for(int i=0; i < (colonLocation); i++){
        ugly.insert(ugly.begin(), 'x');
    }
    return ugly;
}

map<string,OutputLine> outputMap;

int main()
{
    #if DEBUG_MODE
        cout << "..starting up.." << endl;
    #endif
    #if FILE_MODE
        ::file.open("hypergrade.txt", ios::in );
        theInput = RawLine();   // Invokes the copy assignment operator
                                // theInput.lineOfText := temporary.lineOfText
    #endif

    cout << theInput.lineOfText << endl;
    if (theInput.looksLikeMath()){
        if (theInput.hasAColon()) {
            //loadAllTheLinesIntoTheMap();

            simplifyAndEchoAllTheEquations();
        } else {
        simplifyAndEcho();
        }
    } else {
        //loadAllTheLinesIntoTheMap();

        outputAllTheLinesInTheMap();
    }
    cout << "Don't pass hypergrade just yet." << endl;
    #if FILE_MODE
        ::file.close();
    #endif
    return 0;
}

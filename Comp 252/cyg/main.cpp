/* This file can be found at: github.com/Squidbane/ToE/tree/master/Comp 252/cyg/main.cpp */
#include <iostream>
#include <algorithm>
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

string uglifyThis(string);

struct RefinedLine {
    vector<string> words;
    string key;

    RefinedLine(){
        putWordsInTheirBoxes();
    }

    void putWordsInTheirBoxes(){
        int spaceLoc = theInput.lineOfText.find(' ');
        int poundLoc = theInput.lineOfText.find('#');
        theInput.lineOfText.erase(poundLoc,1);
        int nextSpace;
        key = ::uglifyThis(theInput.lineOfText.substr(0,spaceLoc));
        #if DEBUG_MODE
            //cout << key << endl;
        #endif // DEBUG_MODE
        do{
            nextSpace = theInput.lineOfText.find(' ',spaceLoc+1);
            #if DEBUG_MODE
                //cout << "spaceLoc = "<< spaceLoc << " nextSpace = " << nextSpace << endl;
            #endif // DEBUG_MODE
            words.push_back( theInput.lineOfText.substr( spaceLoc+1, nextSpace-spaceLoc-1 ) );
            #if DEBUG_MODE
                //cout << words.back() << endl;
            #endif // DEBUG_MODE
            spaceLoc = nextSpace;
        } while (spaceLoc != -1);
        return;
    }
};

struct OutputLine {
    vector<string> leftWing;
    vector<string> rightWing;
    vector<string>::iterator it;

    OutputLine(vector<string> words){
        leftWing = vector<string>(words.size());
        rightWing = vector<string>(words.size());
        #if DEBUG_MODE
            //cout << "calling OutputLine constructor" <<endl;
            //cout << "the first word in words is " << *(words.begin()) << endl;
        #endif
        copy(words.begin()+1, words.end(), rightWing.begin());
        #if DEBUG_MODE
            //cout << "the first word in rightWing is " << *(rightWing.begin()) <<endl;
        #endif
        reverse_copy(words.begin(), words.end(), leftWing.begin()); //end->back
        #if DEBUG_MODE
            //cout << "Construction complete" <<endl;
        #endif
    }
    OutputLine(){
    }

    bool add(vector<string> words){
        if(search(rightWing.begin(), rightWing.end(), // haystack
                  words.begin(), words.end()) != rightWing.end()) {
            #if DEBUG_MODE
                //cout<<"already in rightWing"<<endl;
            #endif // DEBUG_MODE
            return true;
        } else if (search(rightWing.begin(), rightWing.end()-1, //end->back
                          words.begin(), words.end()-1) != rightWing.end()-1) { //end->back *2
            rightWing.push_back(words.back());
            #if DEBUG_MODE
                cout<<rightWing.back()<<endl;
            #endif // DEBUG_MODE
            return true;
        } else {
            reverse(words.begin(),words.end());
            if(search(leftWing.begin(), leftWing.end(),
                      words.begin(), words.end()) != leftWing.end()) {
                #if DEBUG_MODE
                    //cout<<"already in leftWing"<<endl;
                #endif // DEBUG_MODE
                return true;
            } else {
                //cout<< int(words.begin()+words.size()-1) << endl;
                if (search(leftWing.begin(), leftWing.end()-1, //end->back
                              words.begin(), words.begin()+words.size()-1) != leftWing.end()-1) { //end->back *2
                    leftWing.push_back(words.back());
                    #if DEBUG_MODE
                        cout<<leftWing.back()<<endl;
                    #endif // DEBUG_MODE
                    return true;
                } else {
                    #if DEBUG_MODE
                        //cout<<"doesn't fit"<<endl;
                    #endif // DEBUG_MODE
                    return false;
                }
            }
        }
    }
    string stringify(){
        reverse(leftWing.begin(),leftWing.end());
        string temp = "";
        for(vector<string>::iterator it = leftWing.begin(); it != leftWing.end(); it++){
            temp += *it + " ";
        }
        for(vector<string>::iterator it = rightWing.begin()+4; it != rightWing.end(); it++){
            temp += *it + " ";
        }
        temp.erase(temp.find_last_not_of(" ")+1);
//        string temp = accumulate(leftWing.begin(), leftWing.end(), string(""));
//        cout << temp << endl;
//        temp.append(" ");
//        cout << temp << endl;
//        string temp2 = accumulate(rightWing.begin()+4, rightWing.end(), string(""));
        return temp;

    }
};
map<string,OutputLine> outputMap;

void loadALine(RefinedLine & refLine) {
    theInput.refresh();
    refLine = RefinedLine();
    map<string,OutputLine>::iterator it = outputMap.find(refLine.key);
    if (it == outputMap.end()) {
        outputMap[refLine.key] = OutputLine(refLine.words);
    } else {
        it->second.add(refLine.words);
    }
}

//void loadAllTheLinesIntoTheMap(){
//    loadALine();
//}

void outputALine(map<string,OutputLine>::iterator it){
    cout << it->first <<" "<< it->second.stringify() <<endl;
}

void outputAllTheLinesInTheMap(){
    map<string,OutputLine>::iterator it;
    for( it = ::outputMap.begin(); it != ::outputMap.end(); ++it){
        outputALine(it);
    }
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

int main()
{
    #if DEBUG_MODE
        //cout << "..starting up.." << endl;
    #endif
    #if FILE_MODE
        ::file.open("hypergrade.txt", ios::in );
        theInput = RawLine();   // Invokes the copy assignment operator
                                // theInput.lineOfText := temporary.lineOfText
    #endif

    if (theInput.looksLikeMath()){
        if (theInput.hasAColon()) {
            //loadAllTheLinesIntoTheMap();

            simplifyAndEchoAllTheEquations();
        } else {
        simplifyAndEcho();
        }
    } else {
        //loadAllTheLinesIntoTheMap();
        RefinedLine refLine = RefinedLine();
        #if DEBUG_MODE
            //cout << "else" <<endl;
        #endif
        outputMap[refLine.key] = OutputLine(refLine.words);
        #if DEBUG_MODE
            //
        #endif
        while(!theInput.refreshFailed()){
            loadALine(refLine);
        }
        outputAllTheLinesInTheMap();
    }
    //cout << "Don't pass hypergrade just yet." << endl;
    #if FILE_MODE
        ::file.close();
    #endif
    return 0;
}

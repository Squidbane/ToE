/* This file can be found at: github.com/Squidbane/ToE/tree/master/Comp 252/cyg/main.cpp
 *
 * A few things: Feel free to skip these ramblings, as you won't need them to understand the program.
 * Initially my goal for this project was to make something that could pass maybe 3 out of the
 * 6 assignments on Hypergrade, while at the same time writing my functions in such a way that even
 * someone with no c++ knowledge could understand the program. (If you want to see what I had in mind,
 * go to github.com/Squidbane/ToE/commits/ , find “human readable control flow”(1-16-2014), and look at
 * Comp 252/concordanceCalculus/main.cpp .) I was frustrated that code I had written only a month prior
 * was now difficult for me to read, and I figured that it should be possible to write code in such a
 * way that even dummies like future-me can understand it without much effort.
 * However, over the past month, I've been reading about modern C++ and thinking a lot about what kind
 * of programmer I want to be.
 * I've thus come up with a different set of goals for this particular project:
 *
 * 1. Make it multithreaded. (I want to learn, and there's no time like the present.)
 *    Unfortunately this rule poses a problem because I can't send compiler flags to Hypergrade to
 *    activate C++11 for <threads>, or link the libraries for OpenMP or Boost/Threads. (Trying to
 *    #include any of those, or <process>, gives me an error.) AFAIK this leaves me with only one
 *    recourse: pthreads.
 *
 * 2. Avoid excessive OOP. (I already took Java!)
 *
 * 3.a. Avoid explicit use of pointers (I already took Data Structures in C!) except where necessary
 *      in order to use pthreads.
 *
 * 3.b. In general, pass by value, not by reference. (Modern compilers are extremely good at copy
 *      elision (especially in C++11, with its move semantics) so, unless they save me from saving a
 *      lot of large objects to lvalues, references wont save me a meaningful amount of execution-time.
 *      See: http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/ )
 *
 * 4. Try to pass the last 5 assignments with one unmodified program. (Unfortunately I don't have enough
 *    late days at this point to submit this for the simple concordance.)
 *
 * 5. Make the code self-explanatory. (But not quite to the extent I originally planned.)
 *
 * 6. Avoid comments, they can be redundant and distracting. (See goal #5.)
 *    I should probably delete this big one.
 */
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
        return true;
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
};

void loadALine() {
    //
}

void readInputLine() {
    theInput = RawLine();
}

void loadAllTheLinesIntoTheMap(){
    loadALine();
}

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

int main()
{
    #if DEBUG_MODE
        cout << "..starting up.." << endl;
    #endif
    #if FILE_MODE
        ::file.open("hypergrade.txt", ios::in );
        theInput = RawLine(); // Invokes the copy assignment operator
                                // theInput.lineOfText := temporary.lineOfText
    #endif
    cout << theInput.lineOfText << endl;
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
    cout << "Don't pass hypergrade just yet." << endl;
    #if FILE_MODE
        ::file.close();
    #endif
    return 0;
}

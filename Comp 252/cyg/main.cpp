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
 * I've thus come up with a different set of goals for this project:
 *
 * 1. Make it multithreaded. (I want to learn, and there's no time like the present.)
 *    Unfortunately this rule poses a problem because I can't send compiler flags to Hypergrade to
 *    activate C++11 for <threads>, or link the libraries for OpenMP or Boost/Threads. (Trying to
 *    #include any of those, or <process>, gives me an error.) AFAIK this leaves me with only one
 *    recourse: pthreads. (My Windows machine of course does not support POSIX threads natively,
 *    so I wound up installing CygWin and integrating it with Code::Blocks.)
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
 * 4. Try to pass all 6 assignments with one unmodified program. (Shoot for the moon!)
 *
 * 5. Make the code self-explanatory. (But not quite to the extent I originally planned.)
 *
 * 6. Avoid comments, they can be redundant and distracting. (See goal #5.)
 *    I should probably delete this big one.
 */
#include <iostream>
#include <algorithm>
#include <pthread.h>

using namespace std;
#define DEBUG_MODE true

struct InputLine {
    string lineOfText;

    InputLine(){
        getline(cin, lineOfText);
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
    //
}

void readInputLine() {
    theInput = InputLine();
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
    cout << "Don't pass hypergrade just yet." << endl;
    return EXIT_SUCCESS;
}

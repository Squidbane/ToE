#include <iostream>
#include <algorithm>
#include <pthread.h>
//#include <cstdio>

using namespace std;

//positionOnLine; potato

struct InputLine {
    string lineOfText;
    string box[5];

    InputLine():lineOfText(""){
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
    cout << "Hello Potato" << endl;
}

void simplifyAndEchoAllTheEquations(){
    simplifyAndEcho();
}
void * do_work(void * t){

int i;
long tid;
double result =0.0;
tid = *(long*)t;
cout << " Thread " << tid << "starting" << endl;
if (tid == 2){
cout<<"sleep(15);"<<endl;
}
cout << " Thread " << tid << "finished" << endl;
pthread_exit(NULL);

}

void *TaskCode(void *argument)
{
   int tid;

   tid = *((int *) argument);
//   printf("Hello World! It's me, thread %d!\n", tid);

   /* optionally: insert more useful stuff here */

   return NULL;
}

int main()
{
    pthread_t threads[5];
    int thread_args[5];
    int rc, i;
    for (i=0; i<5; ++i){
        rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &thread_args[i]);
    }
    for (i=0; i<5; ++i) {
      // block until thread i completes
      rc = pthread_join(threads[i], NULL);
//      printf("In main: thread %d is complete\n", i);
   }
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

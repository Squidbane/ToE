#include <iostream>

using namespace std;

unsigned int i = 0;

void recurHanoi(int numToMove, int origin, int dest, int* address) {
    if(numToMove>1) recurHanoi(numToMove-1, origin, 3-dest-origin, address);
    address[i] = ((origin+1)*10) + dest+1;
//    cout << address[i] << " ";
    i = i + 1;
//    cout << "move " << origin+1 << " to " << dest+1 << endl;
    if(numToMove>1) recurHanoi(numToMove-1, 3-origin-dest, dest, address);
}

int main()
{
    int n;
    unsigned long int moves = 1;
    unsigned long int j;
//    cout << "One positive integer please: \n";
//    cin >> n;
//    if(n <= 0) {
//        cout << "Nice positive integer, ass.\n";
//        return 1;
//    }
    n = 19;
    cout << "n= " << n << endl;
    moves = (moves << n)-1;
    int a[moves];
    for (j=0; j< moves; j++){
        a[j]=0;
    }
    recurHanoi(n,0,1, &a[0]);

//    for (j=0; j< moves; j++){
//        cout << a[j] << " ";
//    }
    cout << endl << "(2^n)-1= " << moves << endl;
    cout << "Incidently, " <<  i << " moves were made." << endl;
    cout << "The middle move was from position " << a[((i-1)/2)]/10
        << " to position " << a[((i-1)/2)]%10 << endl;
    cout << "The last move was from position " << a[(i-1)]/10
        << " to position " << a[(i-1)]%10 << endl;
    return 0;
}
/*
void alternate(){
    do {
        while(topOfStackObject.numToMove > 1) {
            push2topOfStack(newObject(numToMove-1,origin,3-dest-origin));
            cout << "move " << topOfStackObject.origin+1
                 << " to " << topOfStackObject.dest+1 << endl;
            push2topOfStack(newObject(numToMove-1,origin,3-dest-origin));
        }
    } while(stackIsNotEmpty);
}
*/

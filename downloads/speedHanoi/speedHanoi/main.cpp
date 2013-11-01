#include <iostream>

using namespace std;

void recurHanoi(int numToMove, int origin, int dest) {
    if(numToMove>1) recurHanoi(numToMove-1, origin, 3-dest-origin);
    cout << "move " << origin+1 << " to " << dest+1 << endl;
    if(numToMove>1) recurHanoi(numToMove-1, 3-origin-dest, dest);
}

int main()
{
    int n;
    cout << "One positive integer please: \n";
    cin >> n;
    recurHanoi(n,0,1);
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

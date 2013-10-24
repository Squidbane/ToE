#include <iostream>
#include <stack>
#include <math.h>
#include <stdio.h>

using namespace std;
std::stack<int> maxS;
int v0;
void maxpush( int a0 ) {
    maxS.push(a0);
    return;
}
void maxpop() {
    maxS.pop();
    return;
}
int maxread() {
    v0 = maxS.top();
    return v0;
}
int main()
{
    int minI=0;
    int disks;
    cout << "One positive integer please: \n";
    cin >> disks;
    int moves = (int)pow(2,disks) -1;
    int a[moves];
    int origin = 1;
    int dest = 2;
    int temp;
    int escapes = 0;
    int i;
    cout << "Moving " << disks << " disks takes ";
    printf ("%d moves.\n",moves);
    maxpush(-1);
    maxpush(moves);
    while(!(maxread()==-1)){
        while((!(maxread() == minI))&&(!(maxread()==-1))){
            maxpush((maxread()+minI)/2);
            a[maxread()]= origin*10 + dest;
            dest = 6 - origin - dest;
            cout << maxread() << " " <<a[maxread()] << endl;
        }
        origin = 6 - origin - dest;
        a[minI+2] = origin*10 + dest;
        cout << (minI+2) << " " <<a[minI+2] << endl;
        maxpop();
        maxpop();
        temp = origin;
        origin = dest;
        dest = temp;
        escapes++;
        cout << escapes << endl;
        if (escapes>=2) {
            dest = 6 - origin - dest;
            cout << dest << endl;
        }
        minI= maxread()+1;
        maxpop();
        cout << "loop finished. Current origin is: " << origin << endl;
        cout << "Current dest is: " << dest << endl;
    }
    for (i=0; i<moves;i++) {
        cout << "move " << a[i]/10 << " to " << a[i]%10 << endl;
    }
    return 0;
}

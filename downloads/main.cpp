#include <iostream>
#include <stack>

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
    int minS=0;
    int disks;
    cin >> disks;
    int moves = (disks*disks) -1;
    int a[moves];
    maxpush(-1);
    maxpush(moves);
    while(!(maxread()==-1)){
        while((!(maxread() == minS))&&(!(maxread()==-1))){
            maxpush((maxread()-minS)/2);
            a[maxread()]= 32;
            cout << maxread() << " " <<a[maxread()] << endl;
        }
        maxpop();
        maxpop();
        a[maxread()-1];
        minS= maxread();
        maxpop();
    }
    int i;
    for (i=0; i<moves;i++) {

    }
    cout << "move " << a[i] << " ";
    return 0;
}

#include <iostream>

using namespace std;

int main()
{
Stack T = Stack();
int unsorted = 0;

while(!S.isEmpty()){
	unsorted++;
	T.push(S.pop);
}
while(!T.isEmpty()){
	S.push(T.pop);
}

Element smallest;
while(unsorted>1){
	smallest = S.pop();
	for (int i=0; i<unsorted; ++i){
		Element temp = S.pop();
		if (smallest.value > temp.value){
			T.push(smallest);
			smallest = temp;
		} else {
			T.push(temp);
		}
	}
	S.push(smallest);
	unsorted--;
	while(!T.isEmpty()){
		S.push(T.pop());
	}
}
    return 0;
}

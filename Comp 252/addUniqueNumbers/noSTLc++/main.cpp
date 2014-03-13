#include <iostream>
using namespace std;

unsigned short largest;

struct Link{
    int data;
    Link* next;
    Link(int n = 0):data(n),next(0){
    }
};
struct LinkedList{
    Link* first;
    Link* last;
    LinkedList(){
        first = 0;
        last = 0;
    }
    void pushBack(int n){
        if (last == 0){
            first = new Link(n);
            last = first;
        } else {
            last->next = new Link(n);
            last = last->next;
        }
    }
};

void getAllInts(LinkedList &inputs){
    int inI;
    while (cin >> inI){
        inputs.pushBack(inI);
        largest = largest|inI;
    }
}

int main()
{
    long long sum;
    largest = 0;
    int* table;
    LinkedList inputs = LinkedList();

    getAllInts(inputs);
    table = new int[largest+1];
    for(unsigned int i = 0; i<=largest; i++){
        table[i] = 0;
    }

    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned short toTest;
        while (temp->next !=0){
            toTest = temp->data;
            table[toTest] += 1;
            temp = temp->next;
        }
        table[unsigned(temp->data)] += 1;
    }
    sum = 0;
    for(unsigned int i=0; i<=largest;i++){
        if(1==table[i]) {
            sum += (signed short)i;
        }
    }
    cout << "Sum is "<< sum << endl;
    delete []table;
    delete table;
    return 0;
}

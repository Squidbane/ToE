#include <iostream>
using namespace std;

unsigned int largest;

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
        if(-11211== inI){
            return;
        }
        inputs.pushBack(inI);
        largest = largest|inI;
    }
}

int main()
{
    int* test = new (std::nothrow) int[unsigned(4294967295)];
    if (!test) {
        cout << "table not allocated" << endl;
        return 1;
    }
    long long sum;
    largest = 0;
    int* table;
    LinkedList inputs = LinkedList();

    getAllInts(inputs);
    cout << "all inputs got" << endl;
    table = new (std::nothrow) int[(unsigned long long)largest+1];
    if (!table) {
        cout << "table not allocated" << endl;
        return 1;
    }
    for(unsigned long long i = 0; i<=largest; i++){
        if (i%(0x1000)==0){
            cout << i << " ";
        }
        table[i] = 0;

    }
    cout << "table initialized to 0" << endl;
    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned short toTest;
        while (temp->next !=0){
            toTest = temp->data;
            table[toTest] += 1;
            temp = temp->next;
        }
        table[unsigned(temp->data)] += 1;
        cout<< "table[" << unsigned(temp->data) << "] = " << table[unsigned(temp->data)] <<endl;
    }
    sum = 0;
    for(unsigned long long i=0; i<=largest;i++){
        if(1==table[i]) {
            sum += (signed int)i;
        }
    }
    cout << "Sum is "<< sum << endl;
    delete []table;
    delete table;
    return 0;
}

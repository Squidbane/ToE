#include <iostream>
#include <string>
using namespace std;

const string mark = "xyzzy";;

struct Node {
	int data;
	string marker;
	Node* next;
	Node(int d=0, Node *n=0) : data(d), next(n) {
		if (n == 0) next = this;
		marker = mark;
	}
};

// list is a circular singly linked list
void insertAtEnd(Node *&list, int d);

void insertAtEnd(Node *&list, int d) {
	Node* newNode = new Node();
	newNode->data = d;
    if (list == 0 ){
        list = newNode;
    } else {
        Node* temp = list;
        while(temp->next != list) {
            temp = temp->next;
        }
	temp->next = newNode;
	newNode->next = list;
    }
}


int main() {
	Node *list=0, *node;
	int n;

	cin>>n;
	while (!cin.eof()) {
		insertAtEnd(list, n);
		cout << "list->" << list->data;
		for(node=list->next; node && (node != list) && (node->marker==mark); node=node->next) {
			cout <<  "->" << node->data;
		}
		if (!node || (node->marker != mark)) cout << "(early termination)";
		cout << endl;
		cin>>n;
	}
	return 0;
}
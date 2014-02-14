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
       marker= mark;}
};

// list is a circular singly linked list
/*
void insertAtEnd(Node *&list, int data) {
    Node* start = list;
	while(list->next != start) {
		list = list->next;
	}
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = start;
	list->next = newNode;
}
*/
void insertAtEnd(Node *&list, int d) {
	Node* newNode = new Node(d);
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

int main()
{
    Node* list = 0;

    insertAtEnd(list,56);
    insertAtEnd(list,7);
    insertAtEnd(list,7);
    insertAtEnd(list,42);

    Node* temp = list;
    cout << "First node contains data: ";
    int counter = 1;
    while (temp->next != list){
        counter++;
        cout << temp->data << endl;
        cout << "Node "<< counter << " contains data: ";
        temp = temp->next;
    }
    cout << temp->data << endl;
    cout << "Node "<< counter << " is the last node" << endl;
    return 0;
}

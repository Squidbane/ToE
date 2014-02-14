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

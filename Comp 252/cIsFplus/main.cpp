#include <stdio.h>
#include <stdlib.h>
#include <winpthread.h>

typedef struct nnode {
    int data;
    struct nnode* next;
} Node;
int main()
{
    Node *myListHead = (Node *)malloc(sizeof(Node));
    myListHead->data = 42;
    myListHead->next = NULL;
    Node **myListHeadPtr = &myListHead;
    Node ***myListHeadPtrPtr = &myListHeadPtr;

    printf("%d\n",(**myListHeadPtrPtr)->data);
    return (***myListHeadPtrPtr).data;
}

#include <stdio.h>
#include <stdlib.h>

unsigned short largest;

typedef struct Link{
    short data;
    struct Link* next;
} Link;

typedef struct LinkedList{
    Link* first;
    Link* last;

} LinkedList;

void pushBack(LinkedList* ll, short n){
    if (ll->last == 0){
        ll->first = (Link*)malloc(sizeof(Link));
        ll->first->data = n;
        ll->first->next = 0;
        ll->last = ll->first;
    } else {
        ll->last->next = (Link*)malloc(sizeof(Link));
        ll->last->next->data = n;
        ll->last->next->next = 0;
        ll->last = ll->last->next;
    }
}

void getAllInts(LinkedList* inputs){
    int inI;
    while (scanf("%d", &inI)){
//        printf("%d",inI);
        if(feof(stdin)){
            break;
        }
//        if(inI == -9999){
//            break;
//        }
        pushBack(inputs,(short)inI);
        largest = largest|(short)inI;
    }
}

int main()
{
    long long sum;
    largest = 0;
    short* table;
    LinkedList inputs;
    inputs.first = 0;
    inputs.last = 0;
    unsigned int i;

    getAllInts(&inputs);
    table = (short*)malloc(sizeof(short[largest+1]));
    for(i = 0; i<=largest; i++){
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
        table[(unsigned short)temp->data] += 1;
    }
    sum = 0;
    for(i=0; i<=largest;i++){
        if(1==table[i]) {
//            printf("table[%d] = %d",(int)i,(int)table[i]);
            sum += (signed short)i;
        }
    }
    printf("Sum is %d\n",(int)sum);
    free(table);
    return 0;
}

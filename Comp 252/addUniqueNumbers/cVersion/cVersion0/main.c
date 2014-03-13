#include <stdio.h>
#include <stdlib.h>

unsigned int largest;

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
        if(feof(stdin)){
            break;
        }
        if(inI == -11211){
            break;
        }
        pushBack(inputs,(short)inI);
        largest = largest|(unsigned)inI;
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
//    printf("The table size will be %d\n",(int)largest);
//    printf("(meaning the smallest absolute value negative number that");
//    printf("can be stored  is %d)\n",(signed short)largest);
    table = (short*)malloc(sizeof(short[65535]));
//    printf("malloc complete\n");
    for(i = 0; i<(((unsigned int)largest)+1); i++){
        if(i==0){
        }
        table[i] = 0;
    }
//    printf("table built\n");

    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned short toTest;
        while (temp->next !=0){
//            printf("adding to table: %d\n",(int)temp->data);
            toTest = temp->data;
            table[toTest] += 1;
//            printf("table[%d] = %d\n",(unsigned int)toTest,(unsigned int)table[toTest]);
            temp = temp->next;
        }
        toTest = temp->data;
        table[toTest] += 1;
//        printf("\ttable[%d] = %d\n",(int)toTest,(int)table[toTest]);
    }
    sum = 0;
    for(i=0; i<=65535;i++){
        if(1==table[i]) {
//            printf("table[%d] = %d\n",(int)i,(int)table[i]);
            sum += (signed short)i;
        }
    }
    printf("Sum is %d\n",(int)sum);
    free(table);
    return 0;
}

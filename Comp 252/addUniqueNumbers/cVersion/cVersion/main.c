#include <stdio.h>
#include <stdlib.h>

unsigned int largest;
int* table;

typedef struct Link{
    int data;
    struct Link* next;
} Link;

typedef struct LinkedList{
    Link* first;
    Link* last;

} LinkedList;

void pushBack(LinkedList* ll, int n){
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
        pushBack(inputs,inI);
        largest = largest|inI;
    }
}

int main()
{
    int neg1 = -1;
    long long sum;
    largest = 0;
    LinkedList inputs;
    inputs.first = 0;
    inputs.last = 0;
    unsigned int tableSize;

    getAllInts(&inputs);
    if(((unsigned)largest)<((unsigned)neg1)){
        tableSize = largest+1;
        printf("%u +1 = %u\n", largest,(largest+1));
    } else {
        tableSize = ((unsigned)neg1);
        printf("tableSize = %u\n",tableSize);
    }
    table = (int*)calloc(tableSize , sizeof(unsigned int));
    if (table == NULL) {
   /* Memory could not be allocated, so print an error and exit. */
   fprintf(stderr, "Couldn't allocate memory\n");
   exit(EXIT_FAILURE);
}
    printf("table of size %u malloc complete\n",tableSize);
    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned int toTest;
        while (temp->next !=0){
            toTest = temp->data;
            printf("toTest = temp->data = %u",toTest);
            table[toTest] = 0;
            printf("table[toTest] = 0;");
            printf("table[%d] = %d\n",(unsigned int)toTest,(unsigned int)table[toTest]);
            temp = temp->next;
        }
        toTest = temp->data;
        table[toTest] = 0;
        printf("\ttable[%d] = %d\n",(int)toTest,(int)table[toTest]);
    }
    printf("table of size %d initialized to 0\n",(int)tableSize);
    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned int toTest;
        while (temp->next !=0){
            printf("adding to table: %d\n",(int)temp->data);
            toTest = temp->data;
            table[toTest] += 1;
            printf("table[%d] = %d\n",(unsigned int)toTest,(unsigned int)table[toTest]);
            temp = temp->next;
        }
        toTest = temp->data;
        table[toTest] += 1;
        printf("\ttable[%d] = %d\n",(int)toTest,(int)table[toTest]);
    }
    sum = 0;
    if(inputs.first != 0){
        Link* temp = inputs.first;
        unsigned int toTest;
        while (temp->next !=0){
            toTest = temp->data;
            sum += (signed)toTest;
            printf("table[%d] = %d\n",(unsigned int)toTest,(unsigned int)table[toTest]);
            temp = temp->next;
        }
        toTest = temp->data;
        sum += (signed)toTest;
        printf("\ttable[%d] = %d\n",(int)toTest,(int)table[toTest]);
    }
    printf("Sum is %d\n",(int)sum);
    free(table);
    return 0;
}

#include "array_list.h"

void print_list(ArrayList* al){
    for(int i = 0; i < al->size; i++)
        printf("%d->", al->array[i]);
    printf("\n");
}

int main(void){
    ArrayList al;

    inti_arraylist(&al);

    for(int i = 1; i <= 3; i++)
    {
        insert(&al, 0, i * 10);
        print_list(&al);
    }
    insert_last(&al, 40);
    print_list(&al);
    delete(&al, 0);
    print_list(&al);

    return 0;
}

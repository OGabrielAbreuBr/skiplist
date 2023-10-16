#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"
int main() {
    srand(time(NULL));
    SkipList* list = createSkipList();

    insert(list, 3);
    insert(list, 1);
    insert(list, 5);
    insert(list, 2);
    insert(list, 4);

    printSkipList(list);

    int key = 2;
    if (search(list, key)) {
        printf("%d found in the Skip List.\n", key);
    } else {
        printf("%d not found in the Skip List.\n", key);
    }

    int removed = 3;
    if (removeElement(list, removed)) {
        printf("%d removed from the Skip List.\n", removed);
    } else {
        printf("%d not found in the Skip List.\n", removed);
    }

    printSkipList(list);

    freeSkipList(list);
    return 0;
}
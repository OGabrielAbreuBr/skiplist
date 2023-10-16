#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "skiplist.h"


#define MAX_LEVEL 10
typedef struct no_ NO;
struct no_ {
    ITEM *item;
    NO **next;
};

struct lista_ {
    NO* cabeca;
    int nivel;
};

NO* createNode(ITEM *item, int level) {
    NO* node = (NO*)malloc(sizeof(NO));
    node->item = item;
    node->next = (NO**)malloc(sizeof(NO*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        node->next[i] = NULL;
    }
    return node;
}

LISTA* createLISTA() {
    LISTA* lista= (LISTA*)malloc(sizeof(LISTA));
    lista->cabeca = createNode(-1, MAX_LEVEL);
    lista->nivel = 0;
    return lista;
}

int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void insert(LISTA* lista, ITEM *item) {
    int level = randomLevel();
    NO* newNode = createNode(value, level);
    NO* current = lista->cabeca;

    for (int i = lista->nivel; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
        if (i <= level) {
            newNode->next[i] = current->next[i];
            current->next[i] = newNode;
        }
    }

    if (level > lista->level) {
        lista->level = level;
    }
}

bool search(LISTA* list, int value) {
    NO* current = lista->head;
    for (int i = lista->level; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
    }
    current = current->next[0];
    return (current != NULL && current->value == value);
}

bool removeElement(LISTA* list, int value) {
    NO* current = lista->head;
    NO* update[MAX_LEVEL + 1];

    for (int i = lista->level; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != NULL && current->value == value) {
        for (int i = 0; i <= lista->level; i++) {
            if (update[i]->next[i] != current) {
                break;
            }
            update[i]->next[i] = current->next[i];
        }
        free(current->next);
        free(current);
        while (lista->level > 0 && lista->head->next[lista->level] == NULL) {
            lista->level--;
        }
        return true;
    }

    return false;
}

void printLISTA(LISTA* list) {
    printf("Skip lista(level %d):\n", lista->level);
    for (int level = lista->level; level >= 0; level--) {
        NO* current = lista->head;
        printf("Level %d: ", level);
        while (current->next[level] != NULL) {
            printf("%d ", current->next[level]->value);
            current = current->next[level];
        }
        printf("\n");
    }
}

void freeLISTA(LISTA* list) {
    NO* current = lista->head;
    while (current != NULL) {
        NO* next = current->next[0];
        free(current->next);
        free(current);
        current = next;
    }
    free(list);
}



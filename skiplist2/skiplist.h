#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdbool.h>
#include "item.h"
#define ERRO -32000
#define ORDENADA 0

typedef struct lista_ LISTA;

LISTA* createSkipList();
void freeSkipList(LISTA* list);
bool search(LISTA* list, int value);
void insert(LISTA* list, int value);
bool removeElement(LISTA* list, int value);
void printSkipList(LISTA* list);
#endif
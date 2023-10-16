#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>  // Adicionamos essa linha para usar strncpy
#include "skiplist.h"

#define MAX_LEVEL 10

typedef struct no_ NO;
struct no_ {
    ITEM *item;
    NO **proximo;
};

struct lista_ {
    NO* cabeca;
    int nivel;
};

NO* createNode(ITEM *item, int level) {
    NO* p = (NO*)malloc(sizeof(NO));
    p->item = item;
    p->proximo = (NO**)malloc(sizeof(NO*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        p->proximo[i] = NULL;
    }
    return p;
}

LISTA* lista_criar() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    lista->cabeca = createNode(item_criar("", ""), MAX_LEVEL);
    lista->nivel = 0;
    return lista;
}

int nivelAleatorio() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void lista_inserir(LISTA* lista, ITEM *item) {
    int level = nivelAleatorio();
    NO* pnovo = createNode(item, level);
    NO* atual = lista->cabeca;

    for (int i = lista->nivel; i >= 0; i--) {
        while (atual->proximo[i] != NULL && strcmp(item_get_palavra(atual->proximo[i]->item), item_get_palavra(item)) < 0) {
            atual = atual->proximo[i];
        }
        if (i <= level) {
            pnovo->proximo[i] = atual->proximo[i];
            atual->proximo[i] = pnovo;
        }
    }

    if (level > lista->nivel) {
        lista->nivel = level;
    }
}

NO *lista_buscar(LISTA* lista, char *chave) {
    NO* atual = lista->cabeca;
    for (int i = lista->nivel; i >= 0; i--) {
        while (atual->proximo[i] != NULL && strcmp(item_get_palavra(atual->proximo[i]->item), chave) < 0) {
            atual = atual->proximo[i];
        }
    }
    atual = atual->proximo[0];
    return atual;
}

void lista_alterar(LISTA *lista, char *chave, char *nova_definicao) {
    if (lista != NULL) {
        NO *p = lista_buscar(lista, chave);
        item_set_definicao(p->item, nova_definicao);
    }
}

int lista_remover(LISTA* lista, char *chave) {
    NO* atual = lista->cabeca;
    NO* update[MAX_LEVEL + 1];

    for (int i = lista->nivel; i >= 0; i--) {
        while (atual->proximo[i] != NULL && strcmp(item_get_palavra(atual->proximo[i]->item), chave) < 0) {
            atual = atual->proximo[i];
        }
        update[i] = atual;
    }

    atual = atual->proximo[0];

    if (atual != NULL && strcmp(item_get_palavra(atual->item), chave) == 0) {
        for (int i = 0; i <= lista->nivel; i++) {
            if (update[i]->proximo[i] != atual) {
                break;
            }
            update[i]->proximo[i] = atual->proximo[i];
        }
        free(atual->proximo);
        free(atual);
        while (lista->nivel > 0 && lista->cabeca->proximo[lista->nivel] == NULL) {
            lista->nivel--;
        }
        return 1;
    }

    return 0;
}

void lista_imprimir(LISTA* lista, char c) {
    printf("Skip lista (nível %d):\n", lista->nivel);
    for (int level = lista->nivel; level >= 0; level--) {
        NO* atual = lista->cabeca;
        printf("Level %d: ", level);
        while (atual->proximo[level] != NULL) {
            printf("%s ", item_get_palavra(atual->proximo[level]->item));
            atual = atual->proximo[level];
        }
        printf("\n");
    }
}

void lista_apagar(LISTA **lista) {
    NO* atual = (*lista)->cabeca->proximo[0];
    while (atual != NULL) {
        NO* proximo = atual->proximo[0];
        free(atual->proximo);
        free(atual);
        atual = proximo;
    }
    free(*lista);
}

#include "skiplist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct no_ NO;

struct no_
{
    ITEM *item;
    int nivel;
    NO *prox;
    NO *baixo;
};

struct lista_{
    // Nível Máximo
    int nivelMax;
    // Nível atual do nó
    int nivel;
    // Ponteiro para o nó cabeca
    NO *cabeca;
};

int sorteiaNivel(LISTA *lista);
NO *novoNO(ITEM *item, int nivel, NO *prox, NO *baixo);

LISTA *lista_criar(int nivelMax){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista != NULL){
        NO *novo_no;
        lista->nivelMax = nivelMax;
        lista->nivel = 0;
        ITEM *item = item_criar(-1);
        novo_no = novoNO(item, 0, NULL, NULL);
        lista->cabeca = novo_no;
        return lista;
    }
    return NULL;
}

void lista_apagar(LISTA **lista){
    if ((*lista) != NULL){
        NO *atual = (*lista)->cabeca;
        (*lista)->cabeca = atual->baixo;
        while ((*lista)->cabeca != NULL){
            while (atual != NULL){
                NO *aux = atual->prox;
                free(atual);
                atual = aux;
            }
            atual = (*lista)->cabeca;
            (*lista)->cabeca = atual->baixo;
        }
        free(*lista); *lista = NULL;
        return;
    }
    return;
}

void lista_inserir(LISTA *lista, ITEM *item){
    if (lista == NULL)
        return;
    NO *atual = lista->cabeca;
    NO *update[lista->nivelMax];
    int nivel_no = sorteiaNivel(lista);

    while (atual->nivel != 0){
        while (item_get_chave(atual->prox->item) < item_get_chave(item))
            atual = atual->prox;
        
        update[atual->nivel] = atual;
        atual = atual->baixo;
    }

    if (atual->prox != NULL){
        while (item_get_chave(atual->prox->item) < item_get_chave(item))
            atual = atual->prox;
    }

    update[atual->nivel] = atual;
    int nivelAtual = 0;

    while (nivelAtual <= lista->nivel){
        NO *novo_no = novoNO(item, nivelAtual, NULL, NULL);
        if (nivelAtual == 0){
            novo_no->prox = update[nivelAtual]->prox;
            novo_no->baixo = NULL;
        } else{
            novo_no->prox = update[nivelAtual]->prox;
            novo_no->baixo = update[nivelAtual - 1]->prox;
        }
        update[nivelAtual]->prox = novo_no;
        nivelAtual++;
    }

    for (int i = lista->nivel + 1; i < nivel_no; i++){
        NO *novo_no = novoNO(item, i, NULL, update[i - 1]->prox);
        ITEM *item_cabeca = item_criar(-1);
        NO *novo_cabeca = novoNO(item_cabeca, i, novo_no, lista->cabeca);
        lista->cabeca = novo_cabeca;
        update[i] = novo_cabeca;
    }
    lista->nivel = nivel_no;
    return;
}

int sorteiaNivel(LISTA *lista){
    return rand() % (lista->nivelMax);
}

NO *novoNO(ITEM *item, int nivel, NO *prox, NO *baixo){
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo != NULL){
        novo->item = item;
        novo->nivel = nivel;
        novo->prox = prox;
        novo->baixo = baixo;
    }
    return novo;
}

void lista_imprimir(LISTA *lista){
    if (lista == NULL)
        return;
    NO *atual = lista->cabeca->prox;
    
    // while (atual->prox != NULL)
    //     atual = atual->prox;
    
    // atual = atual->prox;
    while (atual != NULL){
        int chave = item_get_chave(atual->item);
        printf("[%d]; ", chave);
        atual = atual->prox;
    }
    printf("\n");
}
#ifndef SKIPLIST_H
    #define SKIPLIST_H

    #include <stdbool.h>
    #include "item.h"
    #define ERRO -32000
    #define ORDENADA 0

    typedef struct lista_ LISTA;

    LISTA* lista_criar(int nivelMax);
    void lista_apagar(LISTA **lista);
    ITEM* lista_busca(LISTA *lista, int chave);
    void lista_inserir(LISTA *lista, ITEM *item);
    ITEM* lista_remover(LISTA *lista, int chave);
    void lista_imprimir(LISTA *lista);
#endif
#ifndef LISTA_H
    #define LISTA_H

    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA* lista_criar(); //feito
    int lista_vazia(LISTA* lista); // feito
    int lista_cheia(LISTA *lista);

    ITEM* lista_buscar(LISTA* lista, char *chave); // feito
    int lista_alterar(LISTA *lista, char *chave, char *nova_definicao); // feito
    int lista_inserir(LISTA* lista, ITEM *item); // ??
    int lista_remover(LISTA* lista, char *chave); // feito
    
    void lista_imprimir_bloco(LISTA* lista, char c); // feito
    void lista_imprimir_palavra(LISTA* lista, char *palavra); // feito

    void lista_apagar(LISTA** lista); //feito

#endif
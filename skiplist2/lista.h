#ifndef LISTA_H
    #define LISTA_H

    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA* lista_criar(); 
    int lista_vazia(LISTA* lista); 
    int lista_cheia(LISTA *lista);

    ITEM* lista_buscar(LISTA* lista, char *chave); 
    int lista_alterar(LISTA *lista, char *chave, char *nova_definicao); 
    int lista_inserir(LISTA* lista, ITEM *item); 
    int lista_remover(LISTA* lista, char *chave); 
    
    void lista_imprimir_bloco(LISTA* lista, char c); 
    void lista_imprimir_palavra(LISTA* lista, char *palavra); 

    void lista_apagar(LISTA** lista); 

#endif
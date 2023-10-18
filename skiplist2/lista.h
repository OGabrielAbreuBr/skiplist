#ifndef LISTA_H
    #define LISTA_H

    #include "item.h"

    typedef struct lista_ LISTA;
    typedef struct no_ NO;

    LISTA* lista_criar(); //feito
    int lista_vazia(LISTA* lista); // feito

    NO* lista_buscar(LISTA* lista, char *chave); // feito
    int lista_alterar(LISTA *lista, char *chave, char *nova_definicao); // feito
    int lista_inserir(LISTA* lista, ITEM *item); // em processo
    int lista_remover(LISTA* lista, char *chave); // quase feito, testar
    
    void lista_imprimir_bloco(LISTA* lista, char c); // feito
    void lista_imprimir_palavra(LISTA* lista, char *palavra); // feito

    void lista_apagar(LISTA** lista); //feito

#endif
#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdbool.h>
#include "item.h"
#define ERRO -32000
#define ORDENADA 0

typedef struct lista_ LISTA;
typedef struct no_ NO;

LISTA* lista_criar();
void lista_apagar(LISTA** lista) ;
NO* lista_buscar(LISTA* lista, char *chave);
void lista_alterar(LISTA *lista, char *chave, char *nova_definicao);
void lista_inserir(LISTA* lista, ITEM *item);
int lista_remover(LISTA* lista, char *chave);
void lista_imprimir(LISTA* lista, char c);
#endif
/*
    Trabalho realizado por:
    Gabriel de Andrade Abreu NUMUSP: 14571362
    Leonardo Marangoni NUMUSP: 

    O objetivo foi implementar uma skiplist para a realização de um dicionário. A impplementação da 
    skiplist está em lista.c e para facilitar o desenvolvimento foi utilizado o TAD item com algumas alterações na interface
*/

#include <stdio.h>
#include "lista.h"
#include "item.h"
#include <string.h>

int main(void)
{
    LISTA *l = lista_criar();
    char s[51];

    while (scanf(" %s", s) != EOF){
        char palavra[50];
        char definicao[140];

        if (strcmp(s, "insercao") == 0){
            scanf(" %s", palavra);
            scanf(" %[^\n]s", definicao);
            ITEM *item = item_criar(palavra, definicao);
            lista_inserir(l, item);
        } else if (strcmp(s, "remocao") == 0){
            scanf("%s", palavra);
            lista_remover(l, palavra);
        } else if (strcmp(s, "busca") == 0){
            scanf(" %s", palavra);
            NO *p = lista_buscar(l, palavra);
            if (p != NULL)
                lista_imprimir_palavra(l, palavra);
            else
                printf("OPERACAO INVALIDA");
        } else if (strcmp(s, "alteracao") == 0){
            scanf(" %s", palavra);
            char nova_definicao[140];
            scanf(" %[^\n]s", nova_definicao);
            lista_alterar(l, palavra, nova_definicao);
        } else if (strcmp(s, "impressao") == 0){
            char caracter;
            scanf(" %c", &caracter);
            lista_imprimir_bloco(l, caracter);
        } else {
            
        }
    }

    lista_apagar(&l);
    return 0;
}

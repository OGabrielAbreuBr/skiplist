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
        char palavra[51];
        char definicao[141];

        if (strcmp(s, "insercao") == 0){
            scanf(" %s", palavra);
            scanf(" %[^\n]s", definicao);
            ITEM *item = item_criar(palavra, definicao);
            
            if(lista_inserir(l, item) == 0){
                item_apagar(&item); item = NULL;
                printf("OPERACAO INVALIDA\n");  
            }
        } else if (strcmp(s, "remocao") == 0){
            scanf(" %s", palavra);   
            if(lista_remover(l, palavra) == 0)
                printf("OPERACAO INVALIDA\n");
        } else if (strcmp(s, "busca") == 0){
            scanf(" %s", palavra);
            ITEM *item = lista_buscar(l, palavra);
            if(item == NULL){
                printf("OPERACAO INVALIDA\n");  
            } else
                lista_imprimir_palavra(l, palavra);

        } else if (strcmp(s, "alteracao") == 0){
            scanf(" %s", palavra);
            char nova_definicao[141];
            scanf(" %[^\n]s", nova_definicao);
            if(lista_alterar(l, palavra, nova_definicao) == 0)
                printf("OPERACAO INVALIDA\n");
            
        } else if (strcmp(s, "impressao") == 0){
            char caracter;
            scanf(" %c", &caracter);
            lista_imprimir_bloco(l, caracter);
        }
    }

    lista_apagar(&l);
    return 0;
}

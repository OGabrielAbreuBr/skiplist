/*
    Trabalho realizado por:
    Gabriel de Andrade Abreu NUMUSP: 14571362
    Leonardo Marangoni NUMUSP: 14747614

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
    char s[51]; // string para armazenar os comandos do usuário

    while (scanf(" %s", s) != EOF){ 
        char palavra[51];
        char definicao[141];

        if (strcmp(s, "insercao") == 0){ 
        // se a entrada do usuário for igual a insercao a strcmp retorna 0 e a operacao feita será a insercao
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
            scanf(" %s", definicao);
            scanf(" %[^\n]s", definicao);
            if(lista_alterar(l, palavra, definicao) == 0)
                printf("OPERACAO INVALIDA\n");
            
        } else if (strcmp(s, "impressao") == 0){
            char caracter;
            scanf(" %c", &caracter);
            lista_imprimir_bloco(l, caracter);
        }
    }

    lista_apagar(&l); // liberando a memória da lista
    return 0;
}

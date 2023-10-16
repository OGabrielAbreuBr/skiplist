#include <stdio.h>
#include "skiplist.h"
#include "item.h"
#include <string.h>

int main(void)
{
    LISTA *l = lista_criar();
    char *s;
    while ((scanf("%s", s)) != EOF){
        char palavra[50];
        char definicao[140];

        if (strcmp(s, "insercao")){
            scanf("%s", palavra);
            scanf("%s", definicao); // alterar
            ITEM *item = item_criar(palavra, definicao);
            lista_inserir(l, item);
        } else if(strcmp(s, "remocao")){
            scanf("%s", palavra);
            lista_remover(l, palavra);
        } else if(strcmp(s, "busca")){
            scanf("%s", palavra);
            NO *p = lista_busca(l, palavra);
            if(p != NULL)
                printf("%s %s", item_get_palavra(p), item_get_definicao(p)); //alterar
            else
                printf("OPERACAO INVALIDA");
        } else if(strcmp(s, "alteracao")){
            scanf("%s", palavra);
            char nova_definicao[140];
            scanf("%s", nova_definicao);
            lista_alterar(l, palavra, nova_definicao);
        } else if(strcmp(s, "impressao")){
            char caracter;
            scanf(" %c", &caracter);
            lista_imprimir(l, caracter);
        }
    }

    lista_apagar(&l);
    return 0;
}
#include <stdio.h>
#include "lista.h"
#include "item.h"
#include <string.h>

int main(void)
{
    LISTA *l = lista_criar();
    char s[51]; // Alteração: Alocando s como um array de caracteres

    while (scanf("%s", s) != EOF){
        char palavra[50];
        char definicao[140];

        if (strcmp(s, "insercao") == 0){
            scanf("%s", palavra);
            scanf(" %[^\n]s", definicao); // Leitura de linha inteira, permitindo espaços em branco
            ITEM *item = item_criar(palavra, definicao);
            lista_inserir(l, item);
        } else if (strcmp(s, "remocao") == 0){
            scanf("%s", palavra);
            lista_remover(l, palavra);
        } else if (strcmp(s, "busca") == 0) // Comparação corrigida
        {
            scanf("%s", palavra);
            NO *p = lista_buscar(l, palavra);
            if (p != NULL)
                lista_imprimir_palavra(l, palavra); // Alteração
            else
                printf("OPERACAO INVALIDA");
        } else if (strcmp(s, "alteracao") == 0){
            scanf("%s", palavra);
            char nova_definicao[140];
            scanf(" %[^\n]s", nova_definicao); // Leitura de linha inteira, permitindo espaços em branco
            lista_alterar(l, palavra, nova_definicao);
        } else if (strcmp(s, "impressao") == 0){
            char caracter;
            scanf(" %c", &caracter);
            lista_imprimir_bloco(l, caracter);
        }
    }

    lista_apagar(&l);
    return 0;
}

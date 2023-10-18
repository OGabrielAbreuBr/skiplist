#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lista.h"
#include "item.h"

#define MAX_LEVEL 10

typedef struct no_ NO;

struct no_ {
    ITEM *item;
    NO *proximo;
    NO *baixo;
    int nivel;
};

struct lista_ {
    NO* cabeca;
    int tamanho, maior_nivel;
    int nivel;
};

LISTA* lista_criar() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    if(lista == NULL)
        return NULL;

    lista->maior_nivel = 0;
    lista->tamanho = 0;

    NO *cabeca = (NO*) malloc(sizeof(NO));
    if(cabeca == NULL) {
        free(lista);
        return NULL;
    }
    cabeca->baixo = NULL;
    cabeca->proximo = NULL;
    cabeca->item = NULL;
    cabeca->nivel = 0;
    lista->nivel = 0;
    lista->cabeca = cabeca;

    return lista;
}

int nivelAleatorio(int nivelMaximo) {
    int nivel = 0;
    while (rand() < RAND_MAX / 2 && nivel < nivelMaximo)
        nivel++;
    return nivel;
}

int lista_vazia(LISTA* lista) {
    return (lista == NULL || lista->tamanho == 0);
}

int lista_inserir(LISTA *lista, ITEM *item) {
    if (lista == NULL || item == NULL)
        return 0;

    int nivel = nivelAleatorio(MAX_LEVEL);
    NO *atual = lista->cabeca;
    NO *ant = NULL;

    for (int i = lista->nivel; i < nivel; i++) {
        NO *novoCabeca = (NO*) malloc(sizeof(NO));
        novoCabeca->proximo = NULL;
        novoCabeca->item = NULL;
        novoCabeca->baixo = atual;
        novoCabeca->nivel = 1 + atual->nivel;
        atual = novoCabeca;
    }
    if (lista->nivel < nivel) {
        lista->nivel = nivel;
        lista->cabeca = atual;
    }

    while (atual != NULL) {
        if (atual->proximo == NULL) {
            if (atual->nivel <= nivel) {
                NO *novoNo = (NO*) malloc(sizeof(NO));
                novoNo->nivel = atual->nivel;
                novoNo->proximo = NULL;
                novoNo->baixo = NULL;
                novoNo->item = item;
                atual->proximo = novoNo;

                if (ant != NULL) {
                    ant->baixo = novoNo;
                }

                ant = novoNo;
            }
            atual = atual->baixo;
        }
        else {
            if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) > 0) {
                if (atual->nivel <= nivel) {
                    NO *novoNo = (NO *)malloc(sizeof(NO));
                    novoNo->nivel = atual->nivel;
                    novoNo->proximo = NULL;
                    novoNo->baixo = NULL;
                    novoNo->item = item;

                    if (ant != NULL) {
                        ant->baixo = novoNo;
                    }

                    novoNo->proximo = atual->proximo;
                    atual->proximo = novoNo;
                    ant = novoNo;
                }
                atual = atual->baixo;
            }
            else if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) == 0) {
                // Elemento já existe na lista
                return 0;
            }
            else {
                atual = atual->proximo;
            }
        }
    }

    lista->tamanho++;
    return 1; // Inserção bem-sucedida
}

ITEM *lista_buscar(LISTA* lista, char *chave) {
    if(lista == NULL || lista_vazia(lista)) 
        return NULL; 

    NO *p = lista->cabeca;
    while(p != NULL) {
        if(p->item != NULL && !strcmp(item_get_palavra(p->item), chave)) 
            return p->item;
        else if(p->proximo == NULL)
            p = p->baixo; 
        else {
            if(strcmp(item_get_palavra((p->proximo)->item), chave) > 0)
                p = p->baixo; 
            else
                p = p->proximo; 
        } 
    }
    return NULL; 
}

int lista_alterar(LISTA *lista, char *chave, char *nova_definicao) {
    if((lista == NULL) || (lista_vazia(lista)) || (lista_buscar(lista, chave) == NULL))
        return 0;

    NO *p = lista->cabeca; 
    while(p != NULL) {
        if(p->item != NULL && !strcmp(item_get_palavra(p->item), chave)) {
            item_set_definicao(p->item, nova_definicao);
            return 1; 
        } else {
            if(p->proximo == NULL) 
                p = p->baixo; 
            else {
                if(strcmp(item_get_palavra((p->proximo)->item), chave) > 0) 
                    p = p->baixo; 
                else 
                    p = p->proximo;  
            }
        }
    }
    return 0; 
}

int lista_remover(LISTA* lista, char *chave) {
    // if(lista == NULL || lista_vazia(lista) || !lista_buscar(lista, chave))
    //     return 0;
    if((lista != NULL) && (!lista_vazia(lista)) && (lista_buscar(lista, chave) != NULL)) {
        NO* atual = lista->cabeca;
        int item_removido = 0;
        while(atual != NULL) {
            if(atual->item == NULL) {
                if(atual->proximo == NULL)
                    atual = atual->baixo;
                else{
                    if(strcmp(item_get_palavra((atual->proximo)->item), chave) > 0) 
                        atual = atual->baixo;
                    else{
                        if(!strcmp(item_get_palavra((atual->proximo)->item), chave)){
                            NO *temp = atual->proximo;
                            atual->proximo = temp->proximo;
                            item_removido = 1;

                            if(atual->baixo == NULL && temp != NULL){
                                item_apagar(&(temp->item));
                                free(temp); temp = NULL;
                            }
                            atual = atual->baixo;
                        } else
                            atual = atual->proximo;
                    }
                }
            } else{
                if(atual->proximo != NULL){
                    if(!strcmp(item_get_palavra(atual->item), chave)) {
                        NO *temp = atual->proximo;
                        atual->proximo = temp->proximo;
                        item_removido = 1;

                        if(atual->baixo == NULL && temp != NULL){
                            item_apagar(&(temp->item));
                            free(temp); temp = NULL;
                        }
                        atual = atual->baixo;
                    } else{
                        if(strcmp(item_get_palavra(atual->item), chave) > 0)
                            atual = atual->baixo;
                        else  
                            atual = atual->proximo;
                    }
                } else 
                    atual = atual->baixo;
            }
        }
        return item_removido;
    }
    return 0;
}

void lista_imprimir_bloco(LISTA *lista, char c)
{
    if (lista == NULL)
    {
        return;
    }
    NO *atual = lista->cabeca;
    while (atual != NULL)
    {
        if (atual->proximo == NULL)
        {
            atual = atual->baixo;
        }
        else
        {
            if (atual->item != NULL && atual->baixo == NULL && c == item_get_palavra(atual->item)[0])
            {

                for (NO *p = atual; p != NULL && c == item_get_palavra((p)->item)[0]; p = p->proximo)
                {
                    printf("%s %s\n", item_get_palavra(p->item), item_get_definicao(p->item));
                }

                return;
            }

            else if (atual->baixo == NULL && atual->proximo != NULL && c == item_get_palavra((atual->proximo)->item)[0])
            {

                for (NO *p = atual->proximo; p != NULL && c == item_get_palavra((p)->item)[0]; p = p->proximo)
                {
                    printf("%s %s\n", item_get_palavra(p->item), item_get_definicao(p->item));
                }
                return;
            }
            else if (c - 'a' <= (item_get_palavra((atual->proximo)->item))[0] - 'a')
                atual = atual->baixo;

            else
                atual = atual->proximo;
        }
    }
    printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
    return;
}

void lista_imprimir_palavra(LISTA* lista, char *palavra) {
    if (lista != NULL) {
        ITEM *item = lista_buscar(lista, palavra);
        if (item != NULL) {
            printf("%s %s\n", item_get_palavra(item), item_get_definicao(item));
        } else {
            printf("OPERACAO INVALIDA\n");
        }
    } else {
        printf("OPERACAO INVALIDA\n");
    }
}

void apagar_no(NO *p) {
    if (p == NULL) 
        return;
    apagar_no(p->proximo);
    p->proximo = NULL;
    free(p);
}

void lista_apagar(LISTA **lista) {
    NO *temp = (*lista)->cabeca;
    while(temp != NULL) {
        if (temp->baixo == NULL) {
            NO *aux = (*lista)->cabeca;
            while(aux != NULL){
                item_apagar(&(aux->item));
                aux = aux->proximo;
            }
        }
        temp = temp->baixo; 
    }
    
    NO *aux2 = (*lista)->cabeca;
    while(aux2 != NULL){ // liberando a lista
        if(aux2->proximo != NULL) 
            apagar_no(aux2->proximo);
        aux2->proximo = NULL;
        aux2 = aux2->baixo;
    }

    while(aux2 != NULL){
        aux2->baixo = NULL;
        free(aux2);
        aux2 = NULL;
    }

    free(*lista);
    *lista = NULL;
}

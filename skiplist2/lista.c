#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lista.h"
#include "item.h"

#define MAX_LEVEL 10



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

// NO* criar_no(ITEM *item, int nivel) {
//     NO* p = (NO*)malloc(sizeof(NO));
//     p->item = item;
//     p->proximo = (NO**) malloc(sizeof(NO*) * (nivel + 1));
//     for (int i = 0; i <= nivel; i++) {
//         p->proximo[i] = NULL;
//     }
//     return p;
// }

LISTA* lista_criar() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    if(lista == NULL)
        return NULL;
    
    lista->maior_nivel = 0;
    lista->tamanho = 0;
    
    NO *cabeca = (NO*) malloc(sizeof(NO));
    if(cabeca == NULL)
        return NULL;
    cabeca->baixo = NULL;
    cabeca->proximo = NULL;
    cabeca->item = NULL;
    cabeca->nivel = 0;
    lista->nivel = 0;

    return lista;
}

int nivelAleatorio() {
    int nivel = 0;
    while (rand() < RAND_MAX / 2 && nivel < MAX_LEVEL)
        nivel++;
    return nivel;
}

int lista_vazia(LISTA* lista){
    if(lista != NULL){
        if(lista->maior_nivel == 0)
            return 1;
        else
            return 0;
    }
}

int lista_inserir(LISTA *lista, ITEM *item)
{
    if (lista == NULL || item == NULL)
    {
        return 0; // Não podemos inserir se a lista ou o item for nulo
    }

    int nivel = nivelAleatorio(lista->maior_nivel);
    NO *atual = lista->cabeca;
    NO *ant = NULL;

    for (int i = lista->nivel; i < nivel; i++)
    {
        NO *novoCabeca = (NO *)malloc(sizeof(NO));
        novoCabeca->proximo = NULL;
        novoCabeca->item = NULL;
        novoCabeca->baixo = atual;
        novoCabeca->nivel = 1 + atual->nivel;
        atual = novoCabeca;
    }
    if (lista->nivel < nivel)
    {
        lista->nivel = nivel;
        lista->cabeca = atual;
    }

    while (atual != NULL)
    {
        if (atual->proximo == NULL)
        {
            // Não há próximo, apenas o nó cabeça
            if (atual->nivel <= nivel)
            {
                // Adicionar se o nível for adequado
                NO *novoNo = (NO *)malloc(sizeof(NO));
                novoNo->nivel = atual->nivel;
                novoNo->proximo = NULL;
                novoNo->baixo = NULL;
                novoNo->item = item;
                atual->proximo = novoNo;

                if (ant != NULL)
                {
                    ant->baixo = novoNo;
                }

                ant = novoNo;
            }
            atual = atual->baixo;
        }
        else
        {
            if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) > 0)
            {
                // Descer e adicionar se o nível for adequado
                if (atual->nivel <= nivel)
                {
                    NO *novoNo = (NO *)malloc(sizeof(NO));
                    novoNo->nivel = atual->nivel;
                    novoNo->proximo = NULL;
                    novoNo->baixo = NULL;
                    novoNo->item = item;

                    if (ant != NULL)
                    {
                        ant->baixo = novoNo;
                    }

                    novoNo->proximo = atual->proximo;
                    atual->proximo = novoNo;
                    ant = novoNo;
                }
                atual = atual->baixo;
            }
            else if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) == 0)
            {
                // Elemento já existe na lista
                return 0;
            }
            else
            {
                // Continue procurando à direita
                atual = atual->proximo;
            }
        }
    }

    return 1; // Inserção bem-sucedida
}

NO *lista_buscar(LISTA* lista, char *chave) {
    if(lista == NULL || lista_vazia(lista)) 
        return NULL; 

    NO *p = lista->cabeca;
    while(p != NULL){
        if(p->item != NULL && !strcmp(item_get_palavra(p->item), chave)) 
            return p;
        else if(p->proximo == NULL)
            p = p->baixo; 
        else{
            if(strcmp(item_get_palavra((p->proximo)->item), chave) > 0)
                p = p->baixo; 
            else
                p = p->proximo; 
        } 
    } 
    return NULL; 

    // NO* atual = lista->cabeca;
    // for (int i = lista->nivel; i >= 0; i--) {
    //     while (atual->proximo[i] != NULL && strcmp(item_get_palavra(atual->proximo[i]->item), chave) < 0) {
    //         atual = atual->proximo[i];
    //     }
    // }
    // atual = atual->proximo[0];
    // return atual;
}

int lista_alterar(LISTA *lista, char *chave, char *nova_definicao) {

    if((lista == NULL) || (lista_vazia(lista)) || (lista_buscar(lista, nova_definicao) == NULL))
       return 0;

    NO *p = lista->cabeca; 
    while(p != NULL){
        if(p->item != NULL && !strcmp(chave, nova_definicao)){ // achei = tenho q alterar e descer nele 
            item_set_definicao(p->item, nova_definicao);
            return 1; 
        } else{
            if(p->proximo == NULL) 
                p = p->baixo; // caso não tenha próximo, é necessário descer um nível
            else{
                if(strcmp(item_get_palavra((p->proximo)->item), nova_definicao) > 0) 
                    p = p->baixo; // por conta da lista ser ordenada, pode encerrar a execução caso o próximo seja maior 
                else 
                    p = p->proximo;  
            }
        }
    }
    return 0; 

    // if (lista != NULL) {
    //     NO *p = lista_buscar(lista, chave);
    //     item_set_definicao(p->item, nova_definicao);
    //     return 1;
    // }
    // return 0;
}

int lista_remover(LISTA* lista, char *chave) {
    if(lista != NULL && !lista_vazia(lista)){
        NO* atual = lista->cabeca;

        while(atual != NULL){
            if(atual->item == NULL){
                if(atual->proximo == NULL){
                    atual = atual->baixo;
                } else{
                    if(!strcmp(item_get_palavra((atual->proximo)->item), chave)){ 

                        NO *temp = atual->proximo; 
                        atual->proximo = temp->proximo; 

                        if (atual != NULL && atual->baixo == NULL) {
                            item_apagar(&(temp->item));
                            free(temp); temp = NULL;
                        }
                        atual = atual->baixo; 
                    }
                    else 
                        atual = atual->proximo; 
                }
            }      
            return 1;
        }
    }
    printf("OPERACAO INVALIDA\n");
    return 0;
}


void lista_imprimir_bloco(LISTA* lista, char c) {

    NO *p = lista->cabeca; 

    while(p != NULL){
        if(p->proximo == NULL) 
            p = p->baixo; // caso não tenha próximo, é necessário descer um nível
        else{
            if((p->baixo == NULL) && (p->proximo != NULL) && c == item_get_palavra((p->proximo)->item)[0]){ // quando é o nó cabeca
                NO *temp = p->proximo;
                while(temp != NULL && c == item_get_palavra(temp->item)[0])
                    temp = temp->proximo;
                return; 
            } else if((p->item != NULL) && (p->baixo == NULL) && (c == item_get_palavra(p->item)[0])){ // quando não é o nó cabeca
                NO *temp = p;
                while(temp != NULL && c == item_get_palavra(temp->item)[0]){
                    printf("%s %s\n", item_get_palavra(temp->item), item_get_definicao(temp->item));
                    temp = temp->proximo;
                }
                return; 
            } else if(c -'a' <= (item_get_palavra((p->proximo)->item))[0] - 'a'){
                p = p->baixo; // descer o nivel quando o próximo ter um caracter diferente
            } else 
                p = p->proximo; 
        }
    }
    printf("OPERACAO INVALIDA\n");
    return;

    // if (lista == NULL) {
    //     return;
    // }

    // int encontrado = 0; // Variável para indicar se pelo menos uma palavra foi encontrada

    // for (int level = lista->nivel; level >= 0; level--) {
    //     NO* atual = lista->cabeca;

    //     while (atual->proximo[level] != NULL) {
    //         char *palavra = item_get_palavra(atual->proximo[level]->item);
    //         if (palavra[0] == c) {
    //             encontrado = 1; // Pelo menos uma palavra foi encontrada
    //             printf("%s %s\n", item_get_palavra(atual->proximo[level]->item), item_get_definicao(atual->proximo[level]->item));
    //         }

    //         if (palavra[0] > c) {
    //             break;
    //         }

    //         atual = atual->proximo[level];
    //     }
    // }

    // if (!encontrado) {
    //     printf("OPERACAO INVALIDA\n");
    // }
}

void lista_imprimir_palavra(LISTA* lista, char *palavra) {
    if (lista != NULL) {
        NO *p = lista_buscar(lista, palavra);
        if (p != NULL) {
            printf("%s %s\n", item_get_palavra(p->item), item_get_definicao(p->item));
        } else {
            printf("OPERACAO INVALIDA\n");
        }
    } else {
        printf("OPERACAO INVALIDA\n");
    }
}

void apagar_no(NO **p){
    if((*p) == NULL) 
        return;     
    apagar_no(&((*p)->proximo));
    (*p)->proximo = NULL;
    free(*p); p = NULL; 
}

// void apagar_nos_cabecas(NO **p){
//     if((*p) == NULL) 
//         return ; 
//     apagar_nos_cabecas(&((*p)->baixo));

//     (*p)->baixo = NULL;
//     free(*p); (*p) = NULL; 
// }

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
            apagar_no(&(aux2->proximo));
        aux2 = aux2->proximo;
    }

    while(aux2 != NULL){
        aux2->baixo = NULL;
        free(aux2); aux2 = NULL;
    }

    free(*lista); *lista = NULL; 
}

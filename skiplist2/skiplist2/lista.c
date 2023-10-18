#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lista.h"
#include "item.h"

#define MAX_LEVEL 100

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
};

// essa função tem o objetivo de criar a lista alocando memória para ela
LISTA* lista_criar() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    if(lista == NULL)
        return NULL;
    // inicializando a lista
    lista->maior_nivel = 0;
    lista->tamanho = 0;
    lista->cabeca = NULL;

    NO *cabeca = (NO*) malloc(sizeof(NO));
    if(cabeca == NULL) { // caso a alocação tenha dado errado
        free(lista);
        return NULL;
    }
    // inicializando o nó cabeça
    cabeca->baixo = NULL;
    cabeca->proximo = NULL;
    cabeca->item = NULL;
    cabeca->nivel = 0;
    lista->cabeca = cabeca;

    return lista;
}

// funcao para gerar o nivel do nó que vai ser implementado, assim a complexidade da insercao, remocao e busca tende a ser O(log n)
int nivelAleatorio(int nivelMaximo) {
    int nivel = 0;
    while (rand() < RAND_MAX / 2 && nivel < nivelMaximo) // gera um valor aleatório até o valor maximo
        nivel++;
    return nivel;
}

int lista_vazia(LISTA* lista) {
    return (lista->tamanho == 0 || lista == NULL);
}

// funcao para ver se a lista está cheia, ela tenta alocar memória, caso não haja a lista está cheia
int lista_cheia(LISTA *lista){
    if(lista != NULL){
        NO *temp = (NO*) malloc(sizeof(NO)); 
        // se houver espaço na memória a função irá retornar zero que significa que a lista não está cheia
        if(temp == NULL)
            return 0;
        else{
            free(temp); temp = NULL; // desalocando o nó para não haver vazamento de memória
            return 1; 
        }
    }
    return 1;
}

int lista_inserir(LISTA *lista, ITEM *item){
    if(lista == NULL || lista_buscar(lista, item_get_palavra(item)) != NULL || (!lista_cheia(lista)))
        return 0;
    
    lista->tamanho++;

    int nivel = nivelAleatorio(MAX_LEVEL);

    NO *atual = lista->cabeca;

    if(atual->nivel < nivel){
        int temp = nivel - (atual->nivel);

        while(temp--){
            NO *pnovo = (NO *) malloc(sizeof(NO));
            pnovo->proximo = NULL; pnovo->item = NULL;
            pnovo->nivel = 1 + (atual->nivel);

            pnovo->baixo = atual;
            atual = pnovo;
        }
    }
    lista->maior_nivel = atual->nivel;
    lista->cabeca = atual;

    NO *ant = NULL;

    while(atual != NULL){
        if(atual->proximo == NULL){
            if(atual->nivel <= nivel){
                NO *aux = (NO*) malloc(sizeof(NO));

                aux->nivel = atual->nivel;
                aux->proximo = NULL; aux->baixo = NULL;
                aux->item = item;
                atual->proximo = aux;

                if(ant != NULL){
                    ant->baixo = aux;
                }
                ant = aux;
            }
            atual = atual->baixo;

        }

        else{
            if(strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) > 0){
                if(atual->nivel <= nivel){
                    NO *aux = (NO*) malloc(sizeof(NO));

                    aux->nivel = atual->nivel;
                    aux->proximo = NULL; aux->baixo = NULL;
                    aux->item = item;

                    if(ant != NULL){
                        ant->baixo = aux;
                    }

                    aux->proximo = atual->proximo;
                    atual->proximo = aux;
                    ant = aux;
                }
                atual = atual->baixo;
            }
            else
                atual = atual->proximo;
        }
    } 
    return 1;
}

// int lista_inserir(LISTA *lista, ITEM *item) {
//     if (lista == NULL || item == NULL || lista_buscar(lista, item_get_palavra(item)) != NULL)
//         return 0;

//     int nivel = nivelAleatorio(MAX_LEVEL);
//     NO *atual = lista->cabeca;
//     NO *ant = NULL;

//     for (int i = lista->cabeca->nivel; i < nivel; i++) {
//         NO *novoCabeca = (NO*) malloc(sizeof(NO));
//         novoCabeca->proximo = NULL;
//         novoCabeca->item = NULL;
//         novoCabeca->baixo = atual;
//         novoCabeca->nivel = 1 + atual->nivel;
//         atual = novoCabeca;
//     }
//     if (lista->cabeca->nivel < nivel) {
//         lista->cabeca->nivel = nivel;
//         lista->cabeca = atual;
//     }

//     while (atual != NULL) {
//         if (atual->proximo == NULL) {
//             if (atual->nivel <= nivel) {
//                 NO *novoNo = (NO*) malloc(sizeof(NO));
//                 novoNo->nivel = atual->nivel;
//                 novoNo->proximo = NULL;
//                 novoNo->baixo = NULL;
//                 novoNo->item = item;
//                 atual->proximo = novoNo;

//                 if (ant != NULL) {
//                     ant->baixo = novoNo;
//                 }

//                 ant = novoNo;
//             }
//             atual = atual->baixo;
//         }
//         else {
//             if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) > 0) {
//                 if (atual->nivel <= nivel) {
//                     NO *novoNo = (NO *)malloc(sizeof(NO));
//                     novoNo->nivel = atual->nivel;
//                     novoNo->proximo = NULL;
//                     novoNo->baixo = NULL;
//                     novoNo->item = item;

//                     if (ant != NULL) {
//                         ant->baixo = novoNo;
//                     }

//                     novoNo->proximo = atual->proximo;
//                     atual->proximo = novoNo;
//                     ant = novoNo;
//                 }
//                 atual = atual->baixo;
//             }
//             else if (strcmp(item_get_palavra((atual->proximo)->item), item_get_palavra(item)) == 0) {
//                 // Elemento já existe na lista
//                 return 0;
//             }
//             else {
//                 atual = atual->proximo;
//             }
//         }
//     }

//     lista->tamanho++;
//     return 1; // Inserção bem-sucedida
// }

// funcao criada para buscar um item e assim verificar se ele existe, caso exista a funcao o retorna
ITEM *lista_buscar(LISTA* lista, char *chave) {
    if(lista != NULL && !lista_vazia(lista)){
        NO *p = lista->cabeca;

        while(p != NULL) {
            
            if(p->item != NULL && !strcmp(chave, item_get_palavra(p->item))) // caso o item seja encontrado
                return p->item;
            else if(p->proximo == NULL) // se o próximo for nulo é necessário descer um nível para continuar a busca
                p = p->baixo; 
            else {
                if(strcmp(item_get_palavra((p->proximo)->item), chave) > 0) // verificando de acordo com a ordenação da lista
                    p = p->baixo; 
                else
                    p = p->proximo; 
            } 
        }
    }
    return NULL; 
}

// funcao criada para realizar a alteracao da definicao de um item
int lista_alterar(LISTA *lista, char *chave, char *nova_definicao) {
    if(lista != NULL && !lista_vazia(lista) && lista_buscar(lista, chave)){ // verificacoes necessárias para se fazer a alteracao corretamente
        NO *p = lista->cabeca; // necessario para percorrer todos os nós
        while(p != NULL) {
            if(p->item != NULL && !strcmp(chave, item_get_palavra(p->item))) { // nó encontrado, agora é necessário alterar em todos os niveis
                item_set_definicao(p->item, nova_definicao); 
                return 1; 
            } else {
                if(p->proximo == NULL) // se não tem proximo é necessario descer
                    p = p->baixo; 
                else {
                    if(strcmp(item_get_palavra((p->proximo)->item), chave) > 0) // melhorando o código pois a lista é ordenada
                        p = p->baixo; 
                    else 
                        p = p->proximo;  
                }
            }
        }
    }
    return 0; 
}

int lista_remover(LISTA* lista, char *chave) {
    if((lista != NULL) && (!lista_vazia(lista)) && (lista_buscar(lista, chave) != NULL)) {
        NO* atual = lista->cabeca;
        int no_removido = 0;
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
                            no_removido = 1;

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
                    
                    if(!strcmp(item_get_palavra((atual->proximo)->item), chave)) {
                        
                        NO *temp = atual->proximo;
                        atual->proximo = temp->proximo;
                        no_removido = 1;
                    

                        if(atual->baixo == NULL && temp != NULL){
                            item_apagar(&(temp->item));
                            free(temp); temp = NULL;
                        }
                        atual = atual->baixo;
                    } else{
                        if(strcmp(item_get_palavra((atual->proximo)->item), chave) > 0)
                            atual = atual->baixo;
                        else  
                            atual = atual->proximo;
                    }
                } else 
                    atual = atual->baixo;
            }
        }
        return no_removido;
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
        ITEM *item = lista_buscar(lista, palavra); // buscando a palavra para imprimi-la
        if (item != NULL) { 
            printf("%s %s\n", item_get_palavra(item), item_get_definicao(item));
        } else { // caso a palavra não exista
            printf("OPERACAO INVALIDA\n");
        }
    } else {
        printf("OPERACAO INVALIDA\n");
    }
}

void apagar_no(NO *p) { // apagando uma linha de nós
    if (p == NULL) 
        return;
    apagar_no(p->proximo); 
    p->proximo = NULL;
    free(p);
}

void lista_apagar(LISTA **lista) {
    NO *temp = (*lista)->cabeca; // necessário para percorrer todos os nós
    while(temp != NULL) {
        if (temp->baixo == NULL) { // caso esteja no nível 0
            NO *aux = (*lista)->cabeca;
            while(aux != NULL){
                item_apagar(&(aux->item)); aux->item = NULL;
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

    while(aux2 != NULL){ // apagando nó cabeça
        aux2->baixo = NULL;
        free(aux2);
        aux2 = NULL;
    }

    free(*lista); // liberando a memória da lista
    *lista = NULL;
}

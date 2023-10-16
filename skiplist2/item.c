#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include <stdbool.h>

struct item_ {
    char *palavra;  // Substitua MAX_TAMANHO pelo tamanho máximo necessário
    char *definicao;
};

ITEM *item_criar (char *palavra, char *definicao){
          ITEM *item;
          
          item = (ITEM *) malloc(sizeof(ITEM));
          
          if (item != NULL){
             item->palavra = palavra;
             item->definicao = definicao;
             return(item);
          }
          return(NULL);
}

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL; /*Boa pr�tica!*/
      return(true);
   }
   return(false);
}

char* item_get_palavra(ITEM *item){
    if (item != NULL)
      return(item->palavra);
    exit(1);
}

char* item_get_definicao(ITEM *item){
    if (item != NULL)
      return(item->definicao);
    exit(1);
}


bool item_set_palavra(ITEM *item, char *palavra){
  if (item != NULL){
    item->palavra = palavra;
    return (true);
  }
  return (false);
}

bool item_set_definicao(ITEM *item, char *definicao){
  if (item != NULL){
    item->definicao = definicao;
    return (true);
  }
  return (false);
}
#include <string.h>
#include "item.h"

struct item_ {
    char palavra[51];
    char definicao[141];
};

ITEM *item_criar(char palavra[], char definicao[]){
  ITEM *item;
  
  item = (ITEM *) malloc(sizeof(ITEM));
  
  if (item != NULL){
      strcpy(item->palavra, palavra);
      strcpy(item->definicao, definicao);
      return(item);
  }
  return NULL;
}

int item_apagar(ITEM **item){
  if (*item != NULL){
    free (*item);
    *item = NULL; 
    return 1;
  }
  return 0;
}

char* item_get_palavra(ITEM *item){
  if (item != NULL)
    return(item->palavra);
  return NULL;
}

char* item_get_definicao(ITEM *item){
  if (item != NULL)
    return(item->definicao);
  return NULL;
}


int item_set_palavra(ITEM *item, char *palavra){
  if (item != NULL){
    strcpy(item->palavra, palavra);
    return 1;
  }
  return 0;
}

int item_set_definicao(ITEM *item, char *definicao){
  if (item != NULL){
    strcpy(item->definicao, definicao);
    return 1;
  }
  return 0;
}
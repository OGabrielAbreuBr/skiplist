#ifndef ITEM_H
	#define ITEM_H

	#include <stdlib.h>
	#include <stdio.h>
	
	typedef struct item_ ITEM;

	ITEM *item_criar (char *palavra, char *definicao);
	int item_apagar(ITEM **item);
	char* item_get_palavra(ITEM *item);
	char* item_get_definicao(ITEM *item);
	int item_set_definicao(ITEM *item, char *definicao);
	int item_set_palavra(ITEM *item, char *palavra);

#endif

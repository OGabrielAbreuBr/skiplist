#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>
	#include <stdlib.h>
	#include <stdio.h>
	typedef struct item_ ITEM;

	ITEM *item_criar (char *palavra, char *definicao);
	bool item_apagar(ITEM **item);
	char* item_get_palavra(ITEM *item);
	char* item_get_definicao(ITEM *item);
	bool item_set_definicao(ITEM *item, char *definicao);
	bool item_set_palavra(ITEM *item, char *palavra);

#endif

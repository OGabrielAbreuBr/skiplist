#include "skiplist.h"
#include "item.h"

int main(void){

    int x, n; scanf("%d %d", &x, &n);

    LISTA *skipkist = lista_criar(x);

    for(int i = 0; i < n; i++){
        int it; scanf("%d", &it);
        ITEM *item = item_criar(it);
        lista_inserir(skipkist, item);    
    }
    lista_imprimir(skipkist);

    return 0;
}
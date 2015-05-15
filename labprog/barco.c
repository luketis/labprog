#include "barco.h"
#include "Structs.h"

int posiciona_barco(Map map, int B, Boat barco){
    if(map->map[0][B] == ' '){
        map->map[0][B] = 'B';
	barco->pos[0] = 0;
	barco->pos[1] = B;
        return 1;
    }
    return 0;
}

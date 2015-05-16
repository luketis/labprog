#include "barco.h"
#include "Structs.h"
#include "combate.h"
int posiciona_barco(Map map, int B, Boat barco){
  if(B < map->m && B >= 0 && map->map[0][B] == ' '){
    map->map[0][B] = 'B';
    barco->pos[0] = 0;
    barco->pos[1] = B;
    return 1;
  }
  return 0;
}

int rema_barco(Map map, Boat barco, int movimento){

  switch(movimento){

  case 0:
    return 1;
  case 1:
    if(barco->pos[0][0] + 1 < map->n){
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'T';
      barco->pos[0][0] += 1;
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'B';
      return 1;
    }
    return 0;
  case 2:
    if(barco->pos[0][1] + 1 < map->m && !ehembarcacao(map->map[barco->pos[0][0]][barco->pos[0][1] + 1])){
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'T';
      barco->pos[0][1] += 1;
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'B';
      return 1;
    }
    return 0;
  case 3:
    if(barco->pos[0][1] - 1 >= 0 && !ehembarcacao(map->map[barco->pos[0][0]][barco->pos[0][1] - 1])){
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'T';
      barco->pos[0][1] -= 1;
      map->map[barco->pos[0][0]][barco->pos[0][1]] = 'B';
      return 1;
    }
    return 0;
  case default:
    //movimento invalido
    return 0;
  }
}


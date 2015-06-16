#include "barco.h"
#include "Structs.h"
#include "combate.h"
#include <stdio.h>
int posiciona_barco(Map map, int B, Boat barco){
  if(B < map->n && B >= 0 && map->map[0][B] == ' '){
    map->map[0][B] = 'B';
    barco->pos.x = 0;
    barco->pos.y = B;
    return 1;
  }
  return 0;
}

int rema_barco(Map map, Boat barco, char movimento){

  switch(movimento){
  case 'c':
    if(barco->pos.x - 1 >= 0 && !ehembarcacao(map->map[barco->pos.x - 1][barco->pos.y])){
      map->map[barco->pos.x][barco->pos.y] = 'T';
      barco->pos.x -= 1;
      map->map[barco->pos.x][barco->pos.y] = 'B';
      return 1;
    }
    return 0;
  case 'b':
    if(barco->pos.x + 1 < map->m && !ehembarcacao(map->map[barco->pos.x + 1][barco->pos.y])){
      map->map[barco->pos.x][barco->pos.y] = 'T';
      barco->pos.x += 1;
      map->map[barco->pos.x][barco->pos.y] = 'B';
      return 1;
    }
    return 0;
  case 'd':
    if(barco->pos.y + 1 < map->n && !ehembarcacao(map->map[barco->pos.x][barco->pos.y + 1])){
      map->map[barco->pos.x][barco->pos.y] = 'T';
      barco->pos.y += 1;
      map->map[barco->pos.x][barco->pos.y] = 'B';
      return 1;
    }
    return 0;
  case 'e':
    if(barco->pos.y - 1 >= 0 && !ehembarcacao(map->map[barco->pos.x][barco->pos.y - 1])){
      map->map[barco->pos.x][barco->pos.y] = 'T';
      barco->pos.y -= 1;
      map->map[barco->pos.x][barco->pos.y] = 'B';
      return 1;
    }
    return 0;
    
  default:
    //movimento invalido
    return -1;
  }
}


#ifndef _Structs_h
#define _Structs_h

typedef struct{
  int x, y;
} coord;

typedef struct{
  char **map;
  int m, n;
} mapStruct;

typedef mapStruct* Map;

typedef struct{
  coord pos;
  int alive;
  char tipo;
} boat;

typedef boat* Boat;

#endif

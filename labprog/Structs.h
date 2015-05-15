typedef struct{
  int x, y;
} coord;

typedef struct{
  char **map;
  int m, n;
} mapStruct;

typedef mapStruct* Map;

typedef struct{
  char type;
  int size;
  coord *pos;
} boat;

typedef boat* Boat;

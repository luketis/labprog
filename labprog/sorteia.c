#include <stdio.h>
#include <stdlib.h>
#include "sorteia.h"
#include <time.h>

/*  srand ((unsigned int) time(NULL)); */

int sorteia(int k){
  return (int)(1 + (rand()/(RAND_MAX+1.0))*k);
}

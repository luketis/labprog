#include "Structs.h"
#include "grafico.h"
#include "combate.h"
#include <stdio.h>
//#include "xwc.h"

int max2(int a, int b){
  if(a > b)
    return a;
  return b;
}

WINDOW* init(char nome[], Map mapa, PIC texturas[], char caminhoTexturas[], coord* tamanhotela/*por referencia pois vou alteralo*/, int* tamanhocelula/*idem*/){

  int n = 50;
  int i;
  WINDOW* w;
  char s[] = "texturas/nn.xpm";
  MASK msk;
  *tamanhocelula = 800/max2(mapa->m, mapa->n);
  tamanhotela->x = (*tamanhocelula)*mapa->m;
  tamanhotela->y = (*tamanhocelula)*mapa->n;
  w = InitGraph(tamanhotela->y, tamanhotela->x + 200, nome);
  msk = NewMask(w, *tamanhocelula, *tamanhocelula);
   for(i = 0; i < n;i++){
    s[9] = i/10 + 48;
    s[10] = i%10 + 48;
    texturas[i] = ReadPic(w, s, NULL); 
  }
  WShow(w);
  return w;
}

void desenha(WINDOW* win, Map mapa, PIC texturas[], char texto[], coord tamanhotela, int tamanhocelula){
  coord c;
  c.y = tamanhotela.x + 100;
  c.x = 40;
  desenha_fundo(win);
  desenha_texto(win, texto, c);
  desenha_grid(win, mapa, texturas, tamanhotela, 50);
  }

void apaga(WINDOW* win, PIC texturas[]){
  
  int n = 10;
  int i;
  for(i = 0; i < n; i++)
    FreePic(texturas[i]);
  //WDestroy(win);
}

void desenha_fundo(WINDOW* win){
  WCor(win,WNamedColor("DimGray"));
}

void desenha_texto(WINDOW* win, char texto[], coord xy){
  WPrint(win, xy.x, xy.y, texto);
}

void desenha_grid(WINDOW* win, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula){
  
  Boat embarcoes[256];
  int **desenhado = malloc(mapa->m*sizeof(int*));
  int i, j;
  coord co;
  
  for(i = 0; i < mapa->m; i++){
    desenhado[i] = malloc(mapa->n*sizeof(int));
    for(j = 0; j < mapa->n; j++)
      desenhado[i][j] = 0;
  }
  printf("cheguei\n");
  for(i = 0; i < mapa->m; i++)
    for(j = 0; j < mapa->n; j++)
      if(!desenhado[i][j]){
	
	co.x = i;
	co.y = j;
	if(ehembarcacao(mapa->map[i][j])){
	  printf("cheguei1\n");
	  switch(mapa->map[i][j]){
	  case 'S':
	    desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    break;
	  case 'P':
	    printf("chegueip\n");
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'P')
	      desenhar_P(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'P')
	      desenhar_P(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'P')
	      desenhar_P(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'P')
	      desenhar_P(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    break;
	  case 'C':
	    
	    printf("chegueic\n");
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'C')
	      desenhar_C(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'C')
	      desenhar_C(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'C')
	      desenhar_C(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'C'){
	      printf("chegueic3\n");
	      desenhar_C(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    }
	    break;
	  case 'D':
	    printf("chegueiD\n");
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'D')
	      desenhar_D(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'D')
	      desenhar_D(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'D')
	      desenhar_D(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'D')
	      desenhar_D(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    
	    break;
	  case 'H':
	    printf("chegueiH\n");
	    if(i + 2 < mapa->m && mapa->map[i + 2][j] == 'H')
	      if(j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'H')
		desenhar_H(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	      else
		desenhar_H(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else
	      if(j - 1 >= 0 && i + 1 < mapa->m && mapa->map[i + 1][j - 1] == 'H')
		desenhar_H(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	      else
		desenhar_H(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    break;
	  case 'B':
	    desenha_celula(win, mapa, co, texturas, tamanhotela, tamanhocelula);
	    desenhado[i][j] = 1;
	    break;
	  }
	  printf("cheguei2\n");
	}
	else{
	  co.x = i;
	  co.y = j;
	  desenha_celula(win, mapa, co, texturas, tamanhotela, tamanhocelula);
	  desenhado[i][j] = 1;
	}	
      }

  
  for(i = 0; i < mapa->m; i++)
    free(desenhado[i]);
  free(desenhado);
}

void desenha_celula(WINDOW* win, Map mapa, coord coordenadas, PIC texturas[], coord tamanhotela, int tamanhocelula){

  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  switch(mapa->map[coordenadas.x][coordenadas.y]){
    
  case ' ':
    p = texturas[0];
    break;
  case '=':
    p = texturas[1];
    break;
  case '*':
    p = texturas[2];
    break;
  case '!':
    p = texturas[1]; //GAMBIARRA
    break;
  case '+':
    p = texturas[1];
    break;
  case 'B':
    p = texturas[4];
    break;
  case 'T':
    p = texturas[0];
    break;
  }
  //SetMask(p, msk);
  printf("%d  %d   %c\n", coordenadas.y, coordenadas.x, mapa->map[coordenadas.x][coordenadas.y]);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
  printf("desenhou\n");

}

void desenhar_S(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p = texturas[21];
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  SetMask(p, msk);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
  desenhado[coordenadas.x][coordenadas.y] = 1;
}

void desenhar_P(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i, j;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    //SetMask(p, msk);
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y - i] = 1;
    }
    p = texturas[8];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 4), tamanhocelula*(coordenadas.x + 4));
    desenhado[coordenadas.x + 4][coordenadas.y - 4] = 1;
    
    for(i = 0; i < 4; i++){
      switch(mapa->map[coordenadas.x + i][coordenadas.y - i - 1]){
      case ' ':
	p = texturas[7];
	break;
      case '=':
	p = texturas[46];
	break;
      case '!':
	p = texturas[38];
	break;
      case '+':
	p = texturas[46];
	break;
      case 'B':
	p = texturas[30];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i - 1), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y - i - 1] = 1;
    }
    for(i = 0; i < 4; i++){
      switch(mapa->map[coordenadas.x + i + 1][coordenadas.y - i]){
      case ' ':
	p = texturas[9];
	break;
      case '=':
	p = texturas[47];
	break;
      case '!':
	p = texturas[39]; 
	break;
      case '+':
	p = texturas[47];
	break;
      case 'B':
	p = texturas[31];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[19];
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 4));
    desenhado[coordenadas.x + 4][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    //SetMask(p, msk);
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i));
    desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 4), tamanhocelula*(coordenadas.x + 4));
    desenhado[coordenadas.x + 4][coordenadas.y + 4] = 1;
    
    for(i = 0; i < 4; i++){
      switch(mapa->map[coordenadas.x + i][coordenadas.y + i + 1]){
      case ' ':
	p = texturas[6];
	break;
      case '=':
	p = texturas[48];
	break;
      case '!':
	p = texturas[40]; 
	break;
      case '+':
	p = texturas[48];
	break;
      case 'B':
	p = texturas[42];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i + 1), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y + i + 1] = 1;
    }
    for(i = 0; i < 4; i++){
      switch(mapa->map[coordenadas.x + i + 1][coordenadas.y + i]){
      case ' ':
	p = texturas[8];
	break;
      case '=':
	p = texturas[49];
	break;
      case '!':
	p = texturas[41]; 
	break;
      case '+':
	p = texturas[49];
	break;
      case 'B':
	p = texturas[33];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[20];
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*coordenadas.x);
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
    }
    p = texturas[11];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 4), tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y + 4] = 1;
    break;
  }
}
void desenhar_C(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    // /SetMask(p, msk);
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i));
    desenhado[coordenadas.x + 1][coordenadas.y - i] = 1;
    }
    p = texturas[8];
    //SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 3), tamanhocelula*(coordenadas.x + 3));
    desenhado[coordenadas.x + 3][coordenadas.y - 3] = 1;
    
    for(i = 0; i < 3; i++){
      switch(mapa->map[coordenadas.x + i][coordenadas.y - i - 1]){
      case ' ':
	p = texturas[7];
	break;
      case '=':
	p = texturas[46];
	break;
      case '!':
	p = texturas[38]; 
	break;
      case '+':
	p = texturas[46];
	break;
      case 'B':
	p = texturas[30];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i - 1), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y - i - 1] = 1;
    }
    for(i = 0; i < 3; i++){
      switch(mapa->map[coordenadas.x + i + 1][coordenadas.y - i]){
      case ' ':
	p = texturas[9];
	break;
      case '=':
	p = texturas[47];
	break;
      case '!':
	p = texturas[39]; 
	break;
      case '+':
	p = texturas[47];
	break;
      case 'B':
	p = texturas[31];
	break;
      }
      //SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x - i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 3; i++){
      p = texturas[19];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 3));
    desenhado[coordenadas.x + 3][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    SetMask(p, msk);
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 3), tamanhocelula*(coordenadas.x + 3));
    desenhado[coordenadas.x + 3][coordenadas.y + 3] = 1;
    
    for(i = 0; i < 3; i++){
      switch(mapa->map[coordenadas.x + i][coordenadas.y + i + 1]){
      case ' ':
	p = texturas[6];
	break;
      case '=':
	p = texturas[48];
	break;
      case '!':
	p = texturas[40]; 
	break;
      case '+':
	p = texturas[48];
	break;
      case 'B':
	p = texturas[42];
	break;

      }
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i + 1), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y + i + 1] = 1;
    }
    for(i = 0; i < 3; i++){
      switch(mapa->map[coordenadas.x + i + 1][coordenadas.y + i]){
      case ' ':
	p = texturas[8];
	break;
      case '=':
	p = texturas[49];
	break;
      case '!':
	p = texturas[41]; 
	break;
      case '+':
	p = texturas[49];
	break;
      case 'B':
	p = texturas[33];
	break;
      }
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    printf("chegueiceita\n");
    desenhado[coordenadas.x][coordenadas.y] = 1;
    printf("%d\n", coordenadas.y);
    for(i = 1; i < 3; i++){
      p = texturas[20];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*coordenadas.x);
      printf("%d\n", coordenadas.y + i);
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
      
    }
    printf("chegueiceita2\n");
    p = texturas[11];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 3), tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y + 3] = 1;
    break;
  }
}

void desenhar_D(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y - 1] = 1;
    
    switch(mapa->map[coordenadas.x][coordenadas.y - 1]){
    case ' ':
      p = texturas[7];
      break;
    case '=':
      p = texturas[46];
      break;
    case '!':
      p = texturas[38]; 
      break;
    case '+':
      p = texturas[46];
      break;
    case 'B':
      p = texturas[30];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y - 1] = 1;
    
    
    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
      case ' ':
	p = texturas[9];
	break;
      case '=':
	p = texturas[47];
	break;
      case '!':
	p = texturas[39]; 
	break;
      case '+':
	p = texturas[47];
	break;
      case 'B':
	p = texturas[31];
	break;
	
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 1:
    p = texturas[10];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[12];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    
    switch(mapa->map[coordenadas.x][coordenadas.y + 1]){
    	p = texturas[6];
	break;
      case '=':
	p = texturas[48];
	break;
      case '!':
	p = texturas[40]; 
	break;
      case '+':
	p = texturas[48];
	break;
      case 'B':
	p = texturas[42];
	break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;
    
    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
    case ' ':
      p = texturas[8];
	break;
      case '=':
	p = texturas[49];
	break;
      case '!':
	p = texturas[41]; 
	break;
      case '+':
	p = texturas[49];
	break;
      case 'B':
	p = texturas[33];
	break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 3:
    p = texturas[13];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[11];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;
    break;
  }
}

void desenhar_H(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  printf("chegueiHDENTRO\n");
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i;
  
  switch(tipo){
  case 0:
    printf("chegueiH0\n");
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[15];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y - 1] = 1;
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 2));
    desenhado[coordenadas.x + 2][coordenadas.y] = 1;
    
    switch(mapa->map[coordenadas.x][coordenadas.y - 1]){
    case ' ':
      p = texturas[7];
      break;
    case '=':
      p = texturas[46];
      break;
    case '!':
      p = texturas[38]; 
      break;
    case '+':
      p = texturas[46];
      break;
    case 'B':
      p = texturas[30];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y - 1] = 1;

    switch(mapa->map[coordenadas.x + 2][coordenadas.y - 1]){
    case ' ':
      p = texturas[8];
      break;
    case '=':
      p = texturas[49];
      break;
    case '!':
      p = texturas[41]; 
      break;
    case '+':
      p = texturas[49];
      break;
    case 'B':
      p = texturas[33];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 2));
    desenhado[coordenadas.x + 2][coordenadas.y - 1] = 1;

    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
    case ' ':
      p = texturas[22];
      break;
    case '=':
      p = texturas[45];
      break;
    case '!':
      p = texturas[37]; 
      break;
    case '+':
      p = texturas[45];
      break;
    case 'B':
      p = texturas[29];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 1:
    printf("chegueiH1\n");
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[14];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 2));
    desenhado[coordenadas.x + 2][coordenadas.y] = 1;

    switch(mapa->map[coordenadas.x][coordenadas.y + 1]){
    case ' ':
      p = texturas[6];
      break;
    case '=':
      p = texturas[48];
      break;
    case '!':
      p = texturas[40]; 
      break;
    case '+':
      p = texturas[48];
      break;
    case 'B':
      p = texturas[32];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;

    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
    case ' ':
      p = texturas[24];
      break;
    case '=':
      p = texturas[44];
      break;
    case '!':
      p = texturas[36]; 
      break;
    case '+':
      p = texturas[44];
      break;
    case 'B':
      p = texturas[28];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;

    switch(mapa->map[coordenadas.x + 2][coordenadas.y + 1]){
    case ' ':
      p = texturas[9];
      break;
    case '=':
      p = texturas[47];
      break;
    case '!':
      p = texturas[39]; 
      break;
    case '+':
      p = texturas[47];
      break;
    case 'B':
      p = texturas[31];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 2));
    desenhado[coordenadas.x + 2][coordenadas.y + 1] = 1;
    break;

  case 2:
    printf("chegueiH2\n");
    p = texturas[5];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y - 1] = 1;
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    
    switch(mapa->map[coordenadas.x][coordenadas.y - 1]){
    case ' ':
      p = texturas[7];
      break;
    case '=':
      p = texturas[46];
      break;
    case '!':
      p = texturas[38]; 
      break;
    case '+':
      p = texturas[46];
      break;
    case 'B':
      p = texturas[30];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y - 1] = 1;

    switch(mapa->map[coordenadas.x][coordenadas.y + 1]){
    case ' ':
     p = texturas[6];
      break;
    case '=':
      p = texturas[48];
      break;
    case '!':
      p = texturas[40]; 
      break;
    case '+':
      p = texturas[48];
      break;
    case 'B':
      p = texturas[32];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;

    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
    case ' ':
      p = texturas[23];
      break;
    case '=':
      p = texturas[43];
      break;
    case '!':
      p = texturas[35]; 
      break;
    case '+':
      p = texturas[43];
      break;
    case 'B':
      p = texturas[27];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;

  case 3:
    printf("chegueiH3\n");
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[16];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 2), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 2] = 1;
    
    switch(mapa->map[coordenadas.x][coordenadas.y + 1]){
    case ' ':
      p = texturas[25];
      break;
    case '=':
      p = texturas[42];
      break;
    case '!':
      p = texturas[34]; 
      break;
    case '+':
      p = texturas[42];
      break;
    case 'B':
      p = texturas[26];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;

    switch(mapa->map[coordenadas.x + 1][coordenadas.y]){
    case ' ':
     p = texturas[8];
      break;
    case '=':
      p = texturas[49];
      break;
    case '!':
      p = texturas[41]; 
      break;
    case '+':
      p = texturas[49];
      break;
    case 'B':
      p = texturas[33];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;

    switch(mapa->map[coordenadas.x + 1][coordenadas.y + 2]){
    case ' ':
      p = texturas[9];
      break;
    case '=':
      p = texturas[47];
      break;
    case '!':
      p = texturas[39]; 
      break;
    case '+':
      p = texturas[47];
      break;
    case 'B':
      p = texturas[31];
      break;
    }
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 2), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 2] = 1;
    break;
  }
}

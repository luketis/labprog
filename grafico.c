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

  int n = 51;
  int i;
  WINDOW* w;
  char s[] = "texturas/nn.xpm";
  MASK msk;
  *tamanhocelula = 50;
  tamanhotela->x = 50*mapa->m;
  tamanhotela->y = 50*mapa->n;
  w = InitGraph(tamanhotela->y, tamanhotela->x + 100, nome);
  msk = NewMask(w, *tamanhocelula, *tamanhocelula);
   for(i = 0; i < n;i++){
    s[9] = i/10 + 48;
    s[10] = i%10 + 48;
    texturas[i] = ReadPic(w, s, NULL); 
  }
  WShow(w);
  return w;
}

void desenha(WINDOW* win, Map mapa, PIC texturas[], char texto[], coord tamanhotela, int tamanhocelula, int modo){
  coord c;
  c.y = tamanhotela.x + 50;
  c.x = 40;
  WClear(win);
  desenha_fundo(win);
  desenha_texto(win, texto, c);
  desenha_grid(win, mapa, texturas, tamanhotela, 50, modo);
  }

void apaga(WINDOW* win, PIC texturas[]){
  
  int n = 10;
  int i;
  for(i = 0; i < n; i++)
    FreePic(texturas[i]);
}

void desenha_fundo(WINDOW* win){
  WCor(win,WNamedColor("DimGray"));
}

void desenha_texto(WINDOW* win, char texto[], coord xy){
  WPrint(win, xy.x, xy.y, texto);
}

void desenha_grid(WINDOW* win, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula, int modo){
  
  Boat embarcoes[256];
  int **desenhado = malloc(mapa->m*sizeof(int*));
  int i, j;
  coord co;
  
  for(i = 0; i < mapa->m; i++){
    desenhado[i] = malloc(mapa->n*sizeof(int));
    for(j = 0; j < mapa->n; j++)
      desenhado[i][j] = 0;
  }
  for(i = 0; i < mapa->m; i++)
    for(j = 0; j < mapa->n; j++)
      if(!desenhado[i][j]){
        
        co.x = i;
        co.y = j;
        if(ehembarcacao(mapa->map[i][j]) && modo){
          switch(mapa->map[i][j]){
          case 'S':
            desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
            break;
          case 'P':
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
            if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'C')
              desenhar_C(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
            else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'C')
              desenhar_C(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
            
            else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'C')
              desenhar_C(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
            else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'C')
              desenhar_C(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
            break;
          case 'D':
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
    p = texturas[50];
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
  default:
    p = texturas[0];
    break;
  }
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
}

void desenhar_S(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p = texturas[21];
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
  desenhado[coordenadas.x][coordenadas.y] = 1;
}

void desenhar_P(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  int i, j;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y - i] = 1;
    }
    p = texturas[8];
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
      default:
        p = texturas[7];
        break;
      }
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
      default:
        p = texturas[9];
        break;
      }
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[19];
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 4));
    desenhado[coordenadas.x + 4][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i));
    desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
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
        p = texturas[32];
        break;
      default:
        p = texturas[6];
        break;
      }
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
        default:
        p = texturas[8];
        break;
      }
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[20];
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*coordenadas.x);
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
    }
    p = texturas[11];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 4), tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y + 4] = 1;
    break;
  }
}
void desenhar_C(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - i), tamanhocelula*(coordenadas.x + i));
    desenhado[coordenadas.x + 1][coordenadas.y - i] = 1;
    }
    p = texturas[8];
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
      default:
        p = texturas[7];
        break;
      }
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
      default:
        p = texturas[9];
        break;
      }
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x - i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 3; i++){
      p = texturas[19];
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*(coordenadas.x + 3));
    desenhado[coordenadas.x + 3][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i));
      desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
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
      default:
        p = texturas[6];
        break;

      }
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
      default:
        p = texturas[8];
        break;
      }
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*(coordenadas.x + i + 1));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 3; i++){
      p = texturas[20];
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + i), tamanhocelula*coordenadas.x);
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
      
    }
    p = texturas[11];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 3), tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y + 3] = 1;
    break;
  }
}

void desenhar_D(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[8];
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
    default:
      p = texturas[7];
      break;
    }
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
    default:
      p = texturas[9];
      break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 1:
    p = texturas[10];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[12];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[9];
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
    default:
      p = texturas[6];
      break;
    }
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
    default:
      p = texturas[8];
      break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 3:
    p = texturas[13];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[11];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;
    break;
  }
}

void desenhar_H(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  int i;

  switch(tipo){
  case 0:
    p = texturas[6];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[15];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y - 1] = 1;
    p = texturas[9];
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
      default:
        p = texturas[7];
        break;
    }
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
      default:
        p = texturas[8];
        break;
    }
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
      default:
        p = texturas[22];
        break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 1:
    p = texturas[7];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[14];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    p = texturas[8];
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
      default:
        p = texturas[6];
        break;
    }
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
      default:
        p = texturas[9];
        break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 2));
    desenhado[coordenadas.x + 2][coordenadas.y + 1] = 1;
    break;

  case 2:
    p = texturas[5];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[8];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y - 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y - 1] = 1;
    p = texturas[9];
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
      default:
        p = texturas[7];
        break;
    }
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
      default:
        p = texturas[6];
        break;
    }
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
      default:
        p = texturas[23];
        break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;

  case 3:
    p = texturas[7];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.y, tamanhocelula*coordenadas.x);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[16];
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 1), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 1] = 1;
    p = texturas[6];
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
      default:
        p = texturas[25];
        break;
    }
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
      default:
        p = texturas[8];
        break;
    }
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
      default:
        p = texturas[9];
        break;
    }
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.y + 2), tamanhocelula*(coordenadas.x + 1));
    desenhado[coordenadas.x + 1][coordenadas.y + 2] = 1;
    break;
  }
}

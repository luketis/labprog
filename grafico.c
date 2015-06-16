#include "Structs.h"
#include "grafico.h"
#include "combate.h"
//#include "xwc.h"


WINDOW* init(char nome[], PIC texturas[], char caminhoTexturas[], coord tamanhotela){

  int n = 10;
  int i;
  WINDOW* w = InitGraph(tamanhotela.x, tamanhotela.y, "Batalha Naval");
  char s[2];
  s[1] = '\0';
  for(i = 0; i < n;i++){
    s[0] = i + 48;
    caminhoTexturas[i] = ReadPic(w, s, NULL); 
  }
  WShow(w);
  return w;
}

void desenha(WINDOW* win, PIC texturas[], char texto[], coord tamanhotela, int tamanhocelula);

void apaga(WINDOW* win, PIC texturas[]){
  
  int n = 10;
  int i;
  for(i = 0; i < n; i++)
    FreePic(texturas[i]);
  WDestroy(win);
}

void desenha_fundo(WINDOW* win){
  WCor(win,WNamedColor("DimGray"));
}

void desenha_texto(WINDOW* win, char texto[], coord xy){
  WPrint(win, xy.x, xy.y, texto);
}

void desenha_grid(WINDOW* win, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula){
  
  Boat embarcoes[256];
  int desenhado[mapa->m][mapa->n];
  int i, j, k = 0;
  PIC p;
  MASK msk;
  for(i = 0; i < mapa->m; i++)
    for(j = 0; j < mapa->n; j++)
      desenhado[i][j] = 0;

  for(i = 0; i < mapa->m; i++)
    for(j = 0; j < mapa->n; j++)
      if(!desenhado[i][j]){
	coord co;
	co.x = i;
	co.y = j;
	if(ehembarcacao(mapa->map[i][j])){
	  switch(mapa->map[i][j]){
	  case 'S':
	    
	    break;
	  case 'P':
	    
	    break;
	  case 'C':
	    
	    break;
	  case 'D':
	    
	    break;
	  case 'H':
	    
	    break;
	  }
	  k++;
	}
	else{
	  desenha_celula(win, mapa, co, texturas, tamanhotela, tamanhocelula);
	  desenhado[i][j] = 1;
	}
	
	
      }
  
  for(i = 0; i < k; i++);
  

}

void desenha_embarcacoes(WINDOW* win, Map mapa, PIC texturas[]);

void desenha_celula(WINDOW* win, Map mapa, coord coordenadas, PIC texturas[], coord tamanhotela, int tamanhocelula){

  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  switch(mapa->map[coordenadas.x][coordenadas.y]){
    
  case ' ':
    p = ReadPic(win, "texturas/1.xpm", msk);
    break;
  case '=':
    p = ReadPic(win, "texturas/2.xpm", msk);
    break;
  case '*':
    p = ReadPic(win, "texturas/3.xpm", msk);
    break;
  case '!':
    p = ReadPic(win, "texturas/4.xpm", msk); 
    break;
  case '+':
    p = ReadPic(win, "texturas/5.xpm", msk);
    break;

  }
  SetMask(p, msk);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);

}

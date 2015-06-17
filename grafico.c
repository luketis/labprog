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
	    embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas[5]);
	    break;
	  case 'P':
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'P')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    //usa do 6-8 (incl)
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'P')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    //usa o 9
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'P')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    //usa do 10-12(incl)
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'P')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    //usa o 13
	    break;
	  case 'C':
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'C')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    //usa do 6-8 (incl)
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'C')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    //usa o 14
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'C')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	     //usa do 10-12(incl)
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'C')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    //usa o 15
	    break;
	  case 'D':
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'D')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas[16]);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'D')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas[17]);
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'D')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas[18]);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'D')
	      embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas[19]);
	    
	    break;
	  case 'H':
	    if(i + 2 < mapa->m && mapa->map[i + 2][j] == 'H')
	      if(j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'H')
		embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas[18]);
	      else
		embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas[19]);
	    else
	      if(j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'H')
		embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas[20]);
	      else
		embarcacoes[k] = adesenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas[21]);
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
  //TODO

}

void desenha_embarcacoes(WINDOW* win, Map mapa, PIC texturas[]);

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
    p = texturas[3]; 
    break;
  case '+':
    p = texturas[4];
    break;

  }
  SetMask(p, msk);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);

}

Boat adesenhar_S(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC textura);

Boat adesenhar_P(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas);

Boat adesenhar_C(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas);

Boat adesenhar_D(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC textura);

Boat adesenhar_H(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC textura);

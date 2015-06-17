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
  int i, j;
  
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
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'P')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'P')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'P')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    break;
	  case 'C':
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'C')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'C')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'C')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'C')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	
	    break;
	  case 'D':
	    if(i + 1 < mapa->m && j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'D')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	    else if(i + 1 < mapa->m && mapa->map[i + 1][j] == 'D')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else if(i + 1 < mapa->m && j + 1 < mapa->n && mapa->map[i + 1][j + 1] == 'D')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	    else if(j + 1 < mapa->n && mapa->map[i][j + 1] == 'D')
	      desenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    
	    break;
	  case 'H':
	    if(i + 2 < mapa->m && mapa->map[i + 2][j] == 'H')
	      if(j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'H')
		desenhar_S(win, co, mapa, desenhado, tamanhocelula, 0, texturas);
	      else
		desenhar_S(win, co, mapa, desenhado, tamanhocelula, 1, texturas);
	    else
	      if(j - 1 >= 0 && mapa->map[i + 1][j - 1] == 'H')
		desenhar_S(win, co, mapa, desenhado, tamanhocelula, 2, texturas);
	      else
		desenhar_S(win, co, mapa, desenhado, tamanhocelula, 3, texturas);
	    break;
	  case 'B':
	    desenha_celula(win, mapa, co, texturas, tamanhotela, tamanhocelula);
	    desenhado[i][j] = 1;
	    break;
	  }
	}
	else{
	  desenha_celula(win, mapa, co, texturas, tamanhotela, tamanhocelula);
	  desenhado[i][j] = 1;
	}
	
	
      }
 

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
    p = texturas[3]; 
    break;
  case '+':
    p = texturas[4];
    break;
  case 'B':
    p = texturas[50];
  }
  SetMask(p, msk);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);

}

void desenhar_S(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p = texturas[21];
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  SetMask(p, msk);
  PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
  desenhado[coordenadas.x][coordenadas.y] = 1;
}

void desenhar_P(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i, j;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    SetMask(p, msk);
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y - i));
      desenhado[coordenadas.x + i][coordenadas.y - i] = 1;
    }
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 4), tamanhocelula*(coordenadas.y - 4));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y - i - 1));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i + 1), tamanhocelula*(coordenadas.y - i));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[19];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*coordenadas.y);
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 4), tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x + 4][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    SetMask(p, msk);
    for(i = 1; i < 4; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y + i));
    desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 4), tamanhocelula*(coordenadas.y + 4));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y + i + 1));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i + 1), tamanhocelula*(coordenadas.y + i));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 4; i++){
      p = texturas[20];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*(coordenadas.y + i));
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
    }
    p = texturas[11];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*(coordenadas.y + 4));
    desenhado[coordenadas.x][coordenadas.y + 4] = 1;
    break;
  }
}
void desenhar_C(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[18];
    SetMask(p, msk);
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y - i));
    desenhado[coordenadas.x + 1][coordenadas.y - i] = 1;
    }
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 3), tamanhocelula*(coordenadas.y - 3));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y - i - 1));
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
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i + 1), tamanhocelula*(coordenadas.y - i));
      desenhado[coordenadas.x + i + 1][coordenadas.y - i] = 1;
    }
    break;
  case 1:
    p = texturas[10];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 3; i++){
      p = texturas[19];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*coordenadas.y);
      desenhado[coordenadas.x + i][coordenadas.y] = 1;
    }
    p = texturas[12];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 3), tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x + 3][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[17];
    SetMask(p, msk);
    for(i = 1; i < 3; i++){
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y + i));
      desenhado[coordenadas.x + i][coordenadas.y + i] = 1;
    }
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 3), tamanhocelula*(coordenadas.y + 3));
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
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i), tamanhocelula*(coordenadas.y + i + 1));
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
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + i + 1), tamanhocelula*(coordenadas.y + i));
      desenhado[coordenadas.x + i + 1][coordenadas.y + i] = 1;
    }
    break;
  case 3:
    p = texturas[13];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    for(i = 1; i < 3; i++){
      p = texturas[20];
      SetMask(p, msk);
      PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*(coordenadas.y + i));
      desenhado[coordenadas.x][coordenadas.y + i] = 1;
    }
    p = texturas[11];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*(coordenadas.y + 3));
    desenhado[coordenadas.x][coordenadas.y + 3] = 1;
    break;
  }
}

void desenhar_D(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){
  PIC p;
  MASK msk = NewMask(win, tamanhocelula, tamanhocelula);
  int i;
  switch(tipo){
  case 0:
 
    p = texturas[6];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[8];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 1), tamanhocelula*(coordenadas.y - 1));
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
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x), tamanhocelula*(coordenadas.y- 1));
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
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 1), tamanhocelula*(coordenadas.y));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 1:
    p = texturas[10];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[12];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 1), tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;

  case 2:
    p = texturas[7];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[9];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 1), tamanhocelula*(coordenadas.y + 1));
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
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x), tamanhocelula*(coordenadas.y + 1));
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
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*(coordenadas.x + 1), tamanhocelula*(coordenadas.y));
    desenhado[coordenadas.x + 1][coordenadas.y] = 1;
    break;
  case 3:
    p = texturas[13];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*coordenadas.y);
    desenhado[coordenadas.x][coordenadas.y] = 1;
    p = texturas[11];
    SetMask(p, msk);
    PutPic(win, p, 0,0, tamanhocelula, tamanhocelula, tamanhocelula*coordenadas.x, tamanhocelula*(coordenadas.y + 1));
    desenhado[coordenadas.x][coordenadas.y + 1] = 1;
    break;
  }
}

void desenhar_H(WINDOW* win, coord coordenas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]){



}

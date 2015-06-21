#include <stdio.h>
#include "interface.h"
#include "Structs.h"

char* introducao(){
  return "Entre com o caminho do arquivo que contem o mapa";
}

int get_inicio(WINDOW* w, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula){

  int tecla0, tecla1, tecla2, resultado, valido = 0;
  coord c;
  c.x = 40;
  c.y = tamanhotela.x + 100;
  while(!valido){
    tecla0 = WGetKey(w);
    tecla1 = WGetKey(w);

    printf("%d", tecla1);
    if(tecla0 == 19)
      tecla0 = 9;
    if(tecla1 == 19)
      tecla1 = 9;
    if(tecla1 == 36)
      if(tecla0 - 9 < mapa->m && tecla0 - 9 >= 0 && mapa->map[0][tecla0 - 9] == ' '){
        resultado = tecla0 - 9;
        break;
      }
      else{ 
        desenha(w, mapa, texturas, "Posicao invalida,  escolha a posicao e aperte ENTER", tamanhotela, tamanhocelula, 1);
        continue;
      }
    tecla2 = WGetKey(w);
    if(tecla2 == 36){
      int u = 10*(tecla0 - 9) + tecla1 - 9;
      if(u < mapa->m && u >= 0 && mapa->map[0][u] == ' '){
        resultado = u;
        break;
      }
      else{
        desenha(w, mapa, texturas, "Posicao invalida,  escolha a posicao e aperte ENTER", tamanhotela, tamanhocelula, 1);
        continue;
      }
    }
    desenha(w, mapa, texturas, "Posicao invalida, escolha a posicao e aperte ENTER", tamanhotela, tamanhocelula, 1);
  }
  return resultado;
}

int get_movimento(WINDOW* w, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula, char texto[]){
  int tecla, ok = 1;
  coord c;
  c.x = 40;
  c.y = tamanhotela.x + 50;
  tecla = WGetKey(w);
  if(!(tecla == 113 || tecla== 114 || tecla == 116 || tecla == 111))
    ok = 0;
  while(!ok){
    desenha(w, mapa, texturas, texto, tamanhotela, tamanhocelula, 0);
    tecla = WGetKey(w);
    if(tecla == 113 || tecla== 114 || tecla == 116 || tecla == 111)
      ok = 1;
  }
  return tecla;
}

char* mensagem_posicao(){
   return "Escolha a posicao inicial: ";
}

char* mensagem_posicao_invalida(){
  return "Posição inválida, entre com outra.";
}

char* mensagem_movimento(){
  return "Escolha para qual direcao se movimentar:";
}

char* mensagem_movimento_invalido(){
  return "Movimento invalido, talvez ha algo bloqueando";
}

void mensagem_turno(coord* coordenadas, Boat* atingidos, int modo, char caminho[]){
  int i;
  FILE* c;
  if(modo){
    c = fopen(caminho, "a+");
  }
  else
    c = stdout;
  fprintf(c, "\n");
  for(i = 0; i < 3; i++){
    fprintf(c, "Tiro %d acertou posicao %d, %d", i, coordenadas[i].x, coordenadas[i].y);
    switch(atingidos[i]->tipo){
      
    case 'C':
      fprintf(c, " onde havia um Cruzador\n");
      break;
    case 'S':
      fprintf(c, " onde havia um Submarino\n");
      break;
    case 'D':
      fprintf(c, " onde havia um Destroyer\n");
      break;
    case 'P':
      fprintf(c, " onde havia um Porta-Avião\n");
      break;
    case 'H':
      fprintf(c, " onde havia um Hidro-Aviao\n");
      break;
    case 'T':
      fprintf(c, " onde voce ja esteve\n");
      break;
    case 'B':
      fprintf(c, " onde você estava!\n");
      break;
    default:
      fprintf(c, " onde apenas havia água\n");
      break;
    }
  }
  fprintf(c, "\n");
  if(modo)
    fclose(c);
}
char* mensagem_final(int morreu){
   if(morreu){
     return "Voce perdeu, voce eh uma vergonha para sua familia pirata";
  }

  else{
    return "PARABENS Marinheiro !";
  }
}

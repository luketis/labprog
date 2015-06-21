#include "barco.h"
#include "Structs.h"
#include "combate.h"
#include "maphandling.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 512

int main(int argc, char *argv[]){
  Map mapa;
  Boat barco;
  Boat* barcos;
  coord* coordenadas;
  char movimento;
  int posicao;
  int acabou = 0;
  int OK = 0;
  char* pathArquivoI;
  char* pathArquivoE;
  int turnomod3 = 0;
  coord* turnos;
  coord tamanhotela;
  int tamanhocelula;
  int i;
  WINDOW* w;
  PIC texturas[50];
  int tecla;
  int tecla1;
  
  srand ((unsigned int) time(NULL));
  barco = (Boat) malloc(sizeof(Boat));
  turnos = (coord*) malloc(3*sizeof(coord));
  for(i = 0; i < 3; i++){
    turnos[i].x = -i;
    turnos[i].y = -i;
  }
  barco->alive = 1;
  barco->pos.x = -1;
  barco->pos.y = -1;
  barco->tipo = 'B';
   
  pathArquivoI = argv[1];
  pathArquivoE = argv[2];
  mapa = leia_mapa(pathArquivoI);

  w = init("Batalha Naval", mapa, texturas, "/texturas/00.xpm", &tamanhotela, &tamanhocelula);
  InitKBD(w);/*inicializa a leitura do teclado */
  desenha(w, mapa, texturas, mensagem_posicao(), tamanhotela, tamanhocelula, 1);
  posicao = get_inicio(w, mapa, texturas, tamanhotela, tamanhocelula); /*bloco para rodar ateh que a escolha da posicao inicial seja valida*/
  OK = posiciona_barco(mapa, posicao, barco);
  while(!acabou){ /*loop do jogo*/
    WClear(w);
    desenha(w, mapa, texturas, mensagem_movimento(), tamanhotela, tamanhocelula, 0);
    movimento = get_movimento(w, mapa, texturas, tamanhotela, tamanhocelula, "Use as setas para movimentar");/*pede para o usuario escolher o movimento do barco*/
    OK = rema_barco(mapa, barco, movimento);
    while(!OK){
      desenha(w, mapa, texturas, mensagem_movimento_invalido(), tamanhotela, tamanhocelula, 0);
      movimento = get_movimento(w, mapa, texturas, tamanhotela, tamanhocelula, mensagem_movimento_invalido());
      OK = rema_barco(mapa, barco, movimento);
    }
    coordenadas = dispara_tiros(mapa);
    barcos = identifica_alvo_atingido(coordenadas, mapa, barco);
    afunda_embarcacao(barcos, mapa);
    escreve_mapa_arquivo(mapa, 0, pathArquivoE, barcos, coordenadas);
    if(!barco->alive) /* verifica se o barco continua ileso, senao para o loop do jogo*/
      acabou = 1;
    else if(barco->pos.x == mapa->m -1) /*verifica se o barco chegou ao fim, se sim para o loop do jogo*/
      break;
    turnos[turnomod3].x = barco->pos.x;/*atualiza vetor que guarda as posicoes dos tres ultimos turnos*/
    turnos[turnomod3].y = barco->pos.y;
    turnomod3 = (turnomod3 + 1) % 3;
    if(turnos[0].x == turnos[1].x && turnos[0].x == turnos[2].x && turnos[0].y == turnos[1].y && turnos[0].y == turnos[2].y) /*verifica se o barco esta preso, se sim para o loop do jogo*/
      acabou = 1;
    free(barcos);
  }
  tecla1 = 0;
  while(tecla1 != 36){
    desenha(w, mapa, texturas, mensagem_final(acabou), tamanhotela, tamanhocelula, 1); /*Fim de jogo, espera ateh que o usuario queira sair*/
    tecla1 = WGetKey(w);
  }
  free(barco);
  free(coordenadas);
  free(mapa);
  apaga(w, texturas);
  return 0;
}


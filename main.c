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

int main(){
  Map mapa;
  Boat barco;
  Boat* barcos;
  coord* coordenadas;
  char movimento;
  int posicao;
  int acabou = 0;
  int OK = 0;
  char pathArquivoI[MAX];
  char pathArquivoE[MAX];
  int turnomod3 = 0;
  coord* turnos;
  int i;
  
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

  introducao(); /* mensagem de introducao */
  scanf(" %s", pathArquivoI); 
  scanf(" %s", pathArquivoE);
  mapa = leia_mapa(pathArquivoI);
  printf("\n");
  escreva_mapa_tela(mapa, 0);
  mensagem_posicao(); /*mensagem que pede para o jogador entrar com a posicao inicial*/
  scanf("%d" , &posicao);
  OK = posiciona_barco(mapa, posicao, barco); 
  while(!OK){   /*bloco para rodar ateh que a escolha da posicao inicial eh valida*/
    mensagem_posicao_invalida();
    scanf("%d", &posicao);
    OK = posiciona_barco(mapa, posicao, barco);    
  }
  
  while(!acabou){ /*loop do jogo*/
    escreva_mapa_tela(mapa, 1);
    mensagem_movimento(); /*pede para o usuario escolher o movimento do barco*/
    scanf(" %c", &movimento);
    rema_barco(mapa, barco, movimento);
    coordenadas = dispara_tiros(mapa);
    barcos = identifica_alvo_atingido(coordenadas, mapa, barco);
    escreva_mapa_tela(mapa, 1);
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
    mensagem_turno(coordenadas, barcos, 0, " "); /*apresenta para o usuario as informacoes dos tiros*/
    free(barcos);
  }
  escreva_mapa_tela(mapa, 0);
  mensagem_final(acabou); /*Apresenta para o usuario mensagem do fim de jogo*/
  free(barco);
  free(coordenadas);
  free(mapa);
				 
  return 0;
}


#include "Structs.h"
#include "afundador.h"

void afunda_destroyer(coord coordenadas, Map mapa){
  /* por simplicidade, renomeamos as coordenadas x e y da embacacao*/
  int a = coordenadas.x, b = coordenadas.y;

  if(a+1 < mapa->m && (mapa->map)[a+1][b] == 'D') 
    (mapa->map)[a+1][b] = '*';
	
  else if(a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'D') 
    (mapa->map)[a+1][b+1] = '*';
	
  else if (b+1 < mapa->n && (mapa->map)[a][b+1] == 'D') 
    (mapa->map)[a][b+1] = '*';
		
  else if (a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'D') 
    (mapa->map)[a-1][b+1] = '*';
		
  else if (a-1 >= 0 && (mapa->map)[a-1][b] == 'D') 
    (mapa->map)[a-1][b] = '*';
		
  else if (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'D')
    (mapa->map)[a-1][b-1] = '*';
	
  else if(b-1 >= 0 && (mapa->map)[a][b-1] == 'D') 
    (mapa->map)[a][b-1] = '*';
		
  else if(a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'D') 
    (mapa->map)[a+1][b-1] = '*';

}

void afunda_cruzador(coord coordenadas, Map mapa){

  int a = coordenadas.x, b = coordenadas.y;
  coord nova_coordenada;
  /*verificamos se esta' na horizontal*/
  if((a+1 < mapa->m && (mapa->map)[a+1][b] == 'C') || 
     (a-1 >= 0 && (mapa->map)[a-1][b] == 'C')){

    if(a+1 < mapa->m && (mapa->map)[a+1][b] == 'C') {
      (mapa->map)[a+1][b] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b;
      afunda_cruzador(nova_coordenada, mapa);
    }

    if (a-1 >= 0 && (mapa->map)[a-1][b] == 'C') {
      (mapa->map)[a-1][b] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b;
      afunda_cruzador(nova_coordenada, mapa);
    }

  }
  /*verificamos se esta' na vertical*/
  else if ((b+1 < mapa->n && (mapa->map)[a][b+1] == 'C') ||
	   (b-1 >= 0 && (mapa->map)[a][b-1] == 'C')) {

    if (b+1 < mapa->n && (mapa->map)[a][b+1] == 'C') {
      (mapa->map)[a][b+1] = '*';
      nova_coordenada.x = a;
      nova_coordenada.y = b+1;
      afunda_cruzador(nova_coordenada, mapa);
    }

    if(b-1 >= 0 && (mapa->map)[a][b-1] == 'C') {
      (mapa->map)[a][b-1] = '*';
      nova_coordenada.x = a;
      nova_coordenada.y = b-1;
      afunda_cruzador(nova_coordenada, mapa);
    }
  }

  else if ((a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'C') ||
	   (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'C')) {

    if (a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'C') {
      (mapa->map)[a+1][b+1] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b+1;
      afunda_cruzador(nova_coordenada, mapa);
    }

    if (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'C') {
      (mapa->map)[a-1][b-1] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b-1;
      afunda_cruzador(nova_coordenada, mapa);
    }
  }

  else if ((a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'C') ||
	   (a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'C')) {

    if (a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'C') {	
      (mapa->map)[a-1][b+1] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b+1;
      afunda_cruzador(nova_coordenada, mapa);
    }
			
    if (a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'C') {
      (mapa->map)[a+1][b-1] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b-1;
      afunda_cruzador(nova_coordenada, mapa);
    }
  }
}

void afunda_porta_aviao(coord coordenadas, Map mapa) {

  int a = coordenadas.x, b = coordenadas.y;
  coord nova_coordenada;
  /*verificamos se esta' na horizontal*/
  if((a+1 < mapa->m && (mapa->map)[a+1][b] == 'P') || 
     (a-1 >= 0 && (mapa->map)[a-1][b] == 'P')){

    if(a+1 < mapa->m && (mapa->map)[a+1][b] == 'P') {
      (mapa->map)[a+1][b] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b;
      afunda_porta_aviao(nova_coordenada, mapa);
    }

    if (a-1 >= 0 && (mapa->map)[a-1][b] == 'P') {
      (mapa->map)[a-1][b] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b;
      afunda_porta_aviao(nova_coordenada, mapa);
    }

  }
  /*verificamos se esta' na vertical*/
  else if ((b+1 < mapa->n && (mapa->map)[a][b+1] == 'P') ||
	   (b-1 >= 0 && (mapa->map)[a][b-1] == 'P')) {

    if (b+1 < mapa->n && (mapa->map)[a][b+1] == 'P') {
      (mapa->map)[a][b+1] = '*';
      nova_coordenada.x = a;
      nova_coordenada.y = b+1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }

    if(b-1 >= 0 && (mapa->map)[a][b-1] == 'P') {
      (mapa->map)[a][b-1] = '*';
      nova_coordenada.x = a;
      nova_coordenada.y = b-1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }
  }
  /* verificamos se está na diagonal principal*/
  else if ((a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'P') ||
	   (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'P')) {

    if (a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'P') {
      (mapa->map)[a+1][b+1] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b+1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }

    if (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'P') {
      (mapa->map)[a-1][b-1] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b-1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }
  }
  /*verificamos a outra diagonal*/
  else if ((a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'P') ||
	   (a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'P')) {

    if (a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'P') {	
      (mapa->map)[a-1][b+1] = '*';
      nova_coordenada.x = a-1;
      nova_coordenada.y = b+1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }
			
    if (a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'P') {
      (mapa->map)[a+1][b-1] = '*';
      nova_coordenada.x = a+1;
      nova_coordenada.y = b-1;
      afunda_porta_aviao(nova_coordenada, mapa);
    }
  }
}

void afunda_hidro_aviao(coord coordenadas, Map mapa) {
  int a=coordenadas.x, b=coordenadas.y;
  coord nova_coordenada;

  if(a+1 < mapa->m && (mapa->map)[a+1][b] == 'H') {
    (mapa->map)[a+1][b] = '*';
    nova_coordenada.x = a+1;
    nova_coordenada.y = b;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
	
  if(a+1 < mapa->m && b+1 < mapa->n && (mapa->map)[a+1][b+1] == 'H') {
    (mapa->map)[a+1][b+1] = '*';
    nova_coordenada.x = a+1;
    nova_coordenada.y = b+1;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
	
  if (b+1 < mapa->n && (mapa->map)[a][b+1] == 'H') {
    (mapa->map)[a][b+1] = '*';
    nova_coordenada.x = a;
    nova_coordenada.y = b+1;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
		
  if (a-1 >= 0 && b+1 < mapa->n &&(mapa->map)[a-1][b+1] == 'H') {
    (mapa->map)[a-1][b+1] = '*';
    nova_coordenada.x = a-1;
    nova_coordenada.y = b+1;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
		
  if (a-1 >= 0 && (mapa->map)[a-1][b] == 'H') {
    (mapa->map)[a-1][b] = '*';
    nova_coordenada.x = a-1;
    nova_coordenada.y = b;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
		
  if (a-1 >= 0 && b-1 >= 0 && (mapa->map)[a-1][b-1] == 'H') {
    (mapa->map)[a-1][b-1] = '*';
    nova_coordenada.x = a-1;
    nova_coordenada.y = b-1;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
	
  if(b-1 >= 0 && (mapa->map)[a][b-1] == 'H') {
    (mapa->map)[a][b-1] = '*';
    nova_coordenada.x = a;
    nova_coordenada.y = b-1;
    afunda_hidro_aviao(nova_coordenada, mapa);
  }
		
  if(a+1 < mapa->m && b-1 >= 0 && (mapa->map)[a+1][b-1] == 'H') {
    (mapa->map)[a+1][b-1] = '*';
    nova_coordenada.x = a+1;
    nova_coordenada.y = b-1;
    afunda_porta_aviao(nova_coordenada, mapa);
  }
}

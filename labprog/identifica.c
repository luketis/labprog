void identifica_alvo_atingido(coord coordenadas[3], char**mapa) {
	int i;
	for (i = 0; i<3; i++) {
		if (mapa[(coordenadas[i]).x][(coordenadas[i]).y] == '.') 	
			(mapa)[(coordenadas[i]).x][(coordenadas[i]).y] = '=';

		else if (mapa[(coordenadas[i]).x][(coordenadas[i]).y] == 'B')
			mapa[(coordenadas[i]).x][(coordenadas[i]).y] = '!';

		else if (mapa[(coordenadas[i]).x][(coordenadas[i]).y] == 'T')
			mapa[(coordenadas[i]).x][(coordenadas[i]).y] = '+';
		
		else 
			mapa[(coordenadas[i]).x][(coordenadas[i]).y] = '*';
	}
	
}	

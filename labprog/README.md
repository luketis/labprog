# labprog1
#estruturas:

	-Mapa: struct q vai conter uma array de caracteres de duas dimensoes,e dois ints; numero de linhas e numero de colunas.
	-Embarcacao: struct q vai conter um char que guarda a letra q representa o tipo de embarcacao, um int que representa o numero de quadrados que a embarcacao ocupa e um vetor que contem as coordenadas dos quadradinhos q a embarcacao ocupa
	-Coordenada: struct com dois ints, representando as coordenadas de algum quadrado da mmatriz
	
#obsevacoes:

	-eu estava pensando em pre-calcular todos os mapas possiveis e por em um arquivo de texto. Se formos fazer diferentes dificuldades, ai poderiam ser 3 arquivos. Entao tera uma funcao seleciona_mapa, q vai aleatoriamente escolher um numero. Esse numero sera transformado no numero da linha onde comeca a representacao de um mapa no arquivo. Entao a funcao leia_mapa vai ler esse arquivo a partir dessa linha, ateh o final da representacao do mapa no arquivo, e traduzir isso para a matriz na struct mapa.

	-Ponham observacoes e duvidas aqui

#funcoes:

	BLOCO MAPA_HANDLER.c /----------------------------------------------------------------/
	leia_mapa(String caminhoArquivo, Mapa mapa, int posicao)
		-le um arquivo a partir da linha 'posicao', a partir dos dados lidos gera-se o conteudo da mmatriz da struct mapa.

	escreva_mapa_tela(Mapa mapa, int modo)
		-le o conteudo da matriz da struct mapa e da um jeito de printar isso bunitinhu no terminal. Se modo==0, qr dizer q o jogo acabou de comecar, e o jogador vai ver o mapa pra decidir onde sera a posicao inicial do barco. Entao vai mostrar onde esta cada embarcacao. Se modo==1, nao se distinguem as embarcacoes de agua
	
	escreva_mapa_arquivo(Mapa mapa, String caminhoArquivo)
		-escreve o estado atual do mapa em um arquivo de output, acho q precisa ser bunitinho tbm


	BLOCO BARCO.c /--------------------------------------------------------------------------/

		rema_barco(int movimento, Mapa mapa)
		-dado o movimento que o jogdor deseja que o barco performe, essa funcao verifica se eh possivel realiza-lo. Se sim, entao ele modifica o mapa
		-retorna 0 se a posicao era valida, e -1 se invalida

	posiciona_barco(int col, Mapa mapa)
		-dado o numero da coluna que o jogador selecionou para ser a posicao inicial do barco, a funcao verifica se eh uma posicao valida. Se sim, modifica o mapa
		-retorna 0 se a posicao era valida, e -1 se invalida
	

	BLOCO INTERFACE.c /---------------------------------------------------------------------/

	introducao()
		-escreve um texto no terminal que apresenta o jogo para o jogador

	mensagem_final(int resultado)
		-A funcao deve escrever um texto no terminal informando o jogador do que aconteceu, baseado no resultad (morreu ou chegou ao final)
	

	BLOCO COMBATE.c /-------------------------------------------------------------------/
	
	coordenadas_tiros()
		-sorteia tres coordenadas distintas que serao as posicoes atingidas (acho que seria legal nao poder bombardear posicoes que ja foram bombardeadas)
		-retorna um vetor de coordenadas
	
	identifica_alvo_atingido(Coordenada coordenadas[3], Mapa mapa)
		-verifica se os tiros atingiram alguma coisa. Modifica o mapa nos lugares( exceto emmbarcacoes) que foram atingidos
		-retorna um vetor de coordenadas das emmbarcacoes atingidas ( nao precisa ter as coordenadas de toda a embarcacao, soh da parte atingida)

	afunda_embarcacao(Coordenada atingidas[3], Mapa mapa)
		-Para toda embarcacao, verifica no mapa o tipo de embarcadao atingida, e modifica no mapa todos os quadrados dessa embarcacao.

	dispara_tiros() 
		-chama as tres funcoes acima HSUAHUU, pelo menos eu acho

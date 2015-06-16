Nomes:
	Felipe Silva Felix 8941092
	Larissa de Oliveira Pentedado 8941338
	Lucas de Carvalho Dias 8941241

comando para compilar: make
comando para rodar: ./jogo
	
# MAC0211 EP2
#estruturas:

	-Map: struct q vai conter uma array de caracteres de duas dimensoes,e dois ints; numero de linhas e numero de colunas.
	-Boat: struct q vai conter um char que guarda a letra q representa o tipo de embarcacao, um int que representa o numero de quadrados que a embarcacao ocupa e um vetor que contem as coordenadas dos quadradinhos q a embarcacao ocupa
	-coord: struct com dois ints, representando as coordenadas de algum quadrado da mmatriz

#funcoes:

	BLOCO maphandling.c /----------------------------------------------------------------/
	leia_mapa
		-le um arquivo a partir da linha 'posicao', a partir dos dados lidos gera-se o conteudo da mmatriz da struct mapa.

	escreva_mapa_tela
		-le o conteudo da matriz da struct mapa e da um jeito de printar isso bunitinhu no terminal. Se modo==0, qr dizer q o jogo acabou de comecar, e o jogador vai ver o mapa pra decidir onde sera a posicao inicial do barco. Entao vai mostrar onde esta cada embarcacao. Se modo==1, nao se distinguem as embarcacoes de agua
	
	escreva_mapa_arquivo
		-escreve o estado atual do mapa em um arquivo de saida


	BLOCO barco.c /--------------------------------------------------------------------------/

		rema_barco
		-dado o movimento que o jogdor deseja que o barco performe, essa funcao verifica se eh possivel realiza-lo. Se sim, entao ele modifica o mapa
		-retorna 1 se a posicao era valida, e 0 se invalida

	posiciona_barco
		-dado o numero da coluna que o jogador selecionou para ser a posicao inicial do barco, a funcao verifica se eh uma posicao valida. Se sim, modifica o mapa
		-retorna 1 se a posicao era valida, e 0 se invalida
	

	BLOCO interface.c /---------------------------------------------------------------------/

	introducao
		-escreve um texto no terminal que apresenta o jogo para o jogador

	mensagem_final
		-A funcao deve escrever um texto no terminal informando o jogador do que aconteceu, baseado no resultad (morreu ou chegou ao final)
	

	BLOCO combate.c /-------------------------------------------------------------------/	
	
	identifica_alvo_atingido
		-verifica se os tiros atingiram alguma coisa. Modifica o mapa nos lugares( exceto emmbarcacoes) que foram atingidos
		-retorna um vetor de coordenadas das emmbarcacoes atingidas ( nao precisa ter as coordenadas de toda a embarcacao, soh da parte atingida)

	afunda_embarcacao
		-Para toda embarcacao, verifica no mapa o tipo de embarcadao atingida, e modifica no mapa todos os quadrados dessa embarcacao.

	dispara_tiros 
		-sorteia as coordenadas que serao atingidas pelos tiros e retorna-as

	BLOCO grafico.c /---------------------------------------------------------------/

	init
		-cria a janela com parametros baseados no tamanho da tela ( usando esse esquema http://surfingtroves.blogspot.com.br/2011/01/how-to-get-screen-resolution-in-linux-c.html)

	desenha
		-limpa a tela e depois chama as funcoes:
		       desenha_fundo
		       desenha_linhas
		       desenha_texto	
		       desenha_grid
		       desenha_embarcacoes

	desenha_fundo
		-desenha a parte debaixo da tela que serah a faixa onde aparecerao os textos

	desenha_texto
		-desenha o texto na faixa de texto

	desenha_grid
		-para cada celula do mapa, desenha a imagem referente ao conteudo dessa celula ( agua, tiro ou destrocos)
		-usa uma matriz de 1 ou 0, que indica quais celulas ja foram desenhadas( essencial or causa do desenho das embarcacoes. cada embarcacao eh uma soh imagem, entao ao encontrar uma embarcacao no mapa e pedir para desenha-la com a funcao desenha_embarcacao, a funcao serah obrigada a achar todos os pontos que essa embarcacao ocupa para poder achar o centro e definir qual rotacao usar, e desenharah toda a embarcacao de uma vez )

	desenha_embarcacao
		-identifica qual embarcacao deve ser desenhada e chama a respectiva funcao
		
	desenha_S
		-acha o centro e o tipo de rotacao da embarcacao e escolhe a PIC para desenhar no centro
	desenha_P
		-analoga

	desenha_C
		-analoga

	desenha_D
		-analoga

	desenha_H
		-analoga
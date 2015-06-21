FLAGS = -g -O0
LIBS = 
CC = gcc

jogo: main.o combate.o maphandling.o interface.o barco.o afundador.o grafico.o xwc.o
	$(CC) $(FLAGS) main.o combate.o maphandling.o interface.o barco.o afundador.o grafico.o xwc.o -lm -lXpm -lX11 -o jogo

main.o: main.c
	$(CC) $(FLAGS) -c main.c

barco.o: barco.c barco.h combate.h Structs.h
	$(CC) $(FLAGS) -c barco.c

maphandling.o: maphandling.c maphandling.h combate.h Structs.h
	$(CC) $(FLAGS) -c maphandling.c

interface.o: interface.c interface.h Structs.h xwc.o
	$(CC) $(FLAGS) -c interface.c

combate.o: combate.c afundador.c
	$(CC) $(FLAGS) -c combate.c 

afundador.o: afundador.c afundador.h Structs.h
	$(CC) $(FLAGS) -c afundador.c 

grafico.o: grafico.c xwc.o
	$(CC) $(FLAGS) -c grafico.c

clean:
	rm -f *.o
	rm -f jogo
	cp -f $PWD/xwc/xwc.o .

CFLAGS=-Wall -g  -I -g -O2



all : teste teste2 teste3

teste2 : teste2.o xwc.o 
	${CC} ${CFLAGS} -o teste2 teste2.o xwc.o  -lm -lXpm -lX11 

ifndef NOXPM
teste3 : teste3.o xwc.o 
	${CC} ${CFLAGS} -o teste3 teste3.o xwc.o  -lm -lXpm -lX11 
else
teste3 :
	echo Este programa só funciona com a biblioteca Xpm instalada
endif

teste : teste.o xwc.o 
	${CC} ${CFLAGS} -o teste  teste.o  xwc.o  -lm -lXpm -lX11 

xwc.o : xwc.c


clean: 
	rm -f *.o teste teste2 teste3 *~ Nose.xpm Tutti.xpm caca


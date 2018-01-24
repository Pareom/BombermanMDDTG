bomberman: bomberman.o libisentlib.a
	gcc -Wall bomberman.o -lSDL2main -lSDL2 -lSDL2_mixer -o bomberman libisentlib.a -lm -lglut -lGL -lX11 `sdl2-config --cflags --libs`

bomberman.o: bomberman.c Deplacement.h GestionBombes.h Affichage.h Structures.h GfxLib.h BmpLib.h ESLib.h Charge.h Save.h Robot.h
	gcc -Wall -c bomberman.c
	
libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o Affichage.o GestionBombes.o Deplacement.o Menu.o Robot.o Charge.o Save.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o Affichage.o GestionBombes.o Deplacement.o Menu.o Robot.o Charge.o Save.o
	ranlib libisentlib.a

Charge.o: Charge.c Structures.h Charge.h
	gcc -Wall -O2 -c Charge.c
Save.o: Save.c Structures.h Save.h
	gcc -Wall -O2 -c Save.c	
Menu.o: Menu.c Structures.h Menu.h BmpLib.h GfxLib.h Charge.h
	gcc -Wall -O2 -c Menu.c
Deplacement.o: Deplacement.c Structures.h Deplacement.h 
	gcc -Wall -O2 -c Deplacement.c
Robot.o: Robot.c Structures.h Affichage.h Robot.h 
	gcc -Wall -O2 -c Robot.c
GestionBombes.o: GestionBombes.c GfxLib.h Structures.h GestionBombes.h BmpLib.h ESLib.h
	gcc -Wall -O2 -c GestionBombes.c
Affichage.o: Affichage.c GfxLib.h Structures.h Affichage.h BmpLib.h
	gcc -Wall -O2 -c Affichage.c
	
	
BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c
ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c
ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c
GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c
SocketLib.o: SocketLib.c SocketLib.h
	gcc -Wall -O2 -c SocketLib.c
ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc -Wall -O2 -c ThreadLib.c
TortueLib.o: TortueLib.c TortueLib.h GfxLib.h
	gcc -Wall -O2 -c TortueLib.c
VectorLib.o: VectorLib.c VectorLib.h
	gcc -Wall -O2 -c VectorLib.c -msse3
WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc -Wall -O2 -c WavLib.c -Wno-unused-result
zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile
clean:
	rm -f *~ *.o
deepclean: clean
	rm -f bomberman exempleTortue libisentlib.a

all:tetris

tetris:make/tetris.o make/win.o
	g++ -o tetris make/tetris.o make/win.o

make/tetris.o:code/tetris.cpp
	g++ -o make/tetris.o -c code/tetris.cpp

make/win.o:code/win.cpp
	g++ -o make/win.o code/win.cpp


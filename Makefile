all:tetris

tetris:make/tetris.o make/win.o 
	g++ -o tetris make/tetris.o make/win.o -mwindows

make/tetris.o:code/tetris.cpp 
	g++ -c code/tetris.cpp -o make/tetris.o 
	
make/win.o:code/win.cpp
	g++ -c code/win.cpp -o make/win.o  -mwindows


all:tetris

tetris:make/tetris.o make/resources.o make/win.o 
	g++ -o tetris make/tetris.o make/resources.o make/win.o  -mwindows

#此处为资源文件编译!
make/resources.o:resources/resources.rc
	windres -i resources/resources.rc -o make/resources.o 

make/tetris.o:code/tetris.cpp 
	g++ -c code/tetris.cpp -o make/tetris.o 
	
make/win.o:code/win.cpp
	g++ -c code/win.cpp -o make/win.o  -mwindows



clean:
	del *.o *.exe

.PHONY:clean


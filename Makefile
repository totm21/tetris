
#反斜杠\ 可以在下一行接着写


#字符兼容问题 输入UTF-8 输出GBK   问题在于github是按照UTF-8来读取的 但window是按照GBK来读取的  
UTF_GBK :=-finput-charset=UTF-8 -fexec-charset=GBK

#编译时 库文件链接策略   默认是动态  静态请输入:make version=-static  
version := 

all:tetris

tetris:make/middleware/tetris.o make/middleware/resources.o make/middleware/json_reader.o \
	make/middleware/json_writer.o make/middleware/json_value.o make/middleware/win.o \
	make/middleware/register.o

	g++ $(UTF_GBK) $(version) -o make/tetris \
		make/middleware/tetris.o make/middleware/resources.o make/middleware/json_reader.o \
		make/middleware/json_writer.o make/middleware/json_value.o make/middleware/win.o \
		make/middleware/register.o  \
	 	-mwindows -llua54

#此处为资源文件编译!
make/middleware/resources.o:resources/resources.rc
	windres -i resources/resources.rc -o make/middleware/resources.o 

#此处为jsoncpp文件编译
make/middleware/json_reader.o:code/cpp/expands/json_reader.cpp
	g++ -c code/cpp/expands/json_reader.cpp -o make/middleware/json_reader.o

make/middleware/json_writer.o:code/cpp/expands/json_writer.cpp
	g++ -c code/cpp/expands/json_writer.cpp -o make/middleware/json_writer.o

make/middleware/json_value.o:code/cpp/expands/json_value.cpp
	g++ -c code/cpp/expands/json_value.cpp -o make/middleware/json_value.o
#此处jsoncpp文件编译结束

make/middleware/tetris.o:code/cpp/tetris.cpp 
	g++ $(UTF_GBK) -c code/cpp/tetris.cpp -o make/middleware/tetris.o 
	
make/middleware/win.o:code/cpp/win.cpp
	g++ $(UTF_GBK) -c code/cpp/win.cpp -o make/middleware/win.o

make/middleware/register.o:code/cpp/register.cpp
	g++ $(UTF_GBK) -c code/cpp/register.cpp -o make/middleware/register.o

clean:
	cd make/middleware && del *.o
	cd make && del *.exe

run:
	cd make && tetris.exe

.PHONY:clean run



#反斜杠\ 可以在下一行接着写


#字符兼容问题 输入UTF-8 输出GBK   问题在于github是按照UTF-8来读取的 但window是按照GBK来读取的  
UTF_GBK :=-finput-charset=UTF-8 -fexec-charset=GBK

#编译时 库文件链接策略   默认是动态  静态请输入:make version=-static  
version := 

all:tetris

tetris:make/tetris.o make/resources.o make/json_reader.o make/json_writer.o make/json_value.o make/win.o 
	g++ $(UTF_GBK) $(version) -o tetris make/tetris.o make/resources.o make/json_reader.o make/json_writer.o make/json_value.o make/win.o  -mwindows

#此处为资源文件编译!
make/resources.o:resources/resources.rc
	windres -i resources/resources.rc -o make/resources.o 

#此处为jsoncpp文件编译
make/json_reader.o:code/cpp/expands/json_reader.cpp
	g++ -c code/cpp/expands/json_reader.cpp -o make/json_reader.o

make/json_writer.o:code/cpp/expands/json_writer.cpp
	g++ -c code/cpp/expands/json_writer.cpp -o make/json_writer.o

make/json_value.o:code/cpp/expands/json_value.cpp
	g++ -c code/cpp/expands/json_value.cpp -o make/json_value.o
#此处jsoncpp文件编译结束

make/tetris.o:code/cpp/tetris.cpp 
	g++ $(UTF_GBK) -c code/cpp/tetris.cpp -o make/tetris.o 
	
make/win.o:code/cpp/win.cpp
	g++ $(UTF_GBK) -c code/cpp/win.cpp -o make/win.o


clean:
	del *.o *.exe

.PHONY:clean


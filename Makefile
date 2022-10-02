
#反斜杠\ 可以在下一行接着写


#字符兼容问题 输入UTF-8 输出GBK   问题在于github是按照UTF-8来读取的 但window是按照GBK来读取的  
UTF_GBK :=
#-finput-charset=UTF-8 -fexec-charset=GBK
#旧的解决方式是更改编译后的输出文件编码  现在的解决方式是更改控制台输出编码

#编译时 库文件链接策略   默认是动态  静态请输入:make version=-static  
version := 

#删除单个文件时使用  例如 make delete name=log.o 默认为make/middleware文件夹其他请自行调整(意义不大)
name := 

all:tetris

tetris:make/middleware/tetris.o make/middleware/resources.o make/middleware/json_reader.o \
	make/middleware/json_writer.o make/middleware/json_value.o \
	make/middleware/glad.o \
	make/middleware/win.o \
	make/middleware/register.o make/middleware/timer.o make/middleware/log.o \
	make/middleware/graphics.o \

	g++ $(version) -o make/tetris \
		make/middleware/tetris.o make/middleware/resources.o make/middleware/json_reader.o \
		make/middleware/json_writer.o make/middleware/json_value.o \
		make/middleware/glad.o \
		make/middleware/win.o \
		make/middleware/register.o make/middleware/timer.o make/middleware/log.o \
		make/middleware/graphics.o \
	 	-mwindows -llua54 -lglfw3 -lgdi32 -lopengl32

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

#此处为插件头文件编译
make/middleware/glad.o:code/cpp/expands/glad.c
	g++ -c code/cpp/expands/glad.c -o make/middleware/glad.o

#此处为结束

make/middleware/tetris.o:code/cpp/tetris.cpp 
	g++ $(UTF_GBK) -c code/cpp/tetris.cpp -o make/middleware/tetris.o 
	
make/middleware/win.o:code/cpp/win.cpp
	g++ $(UTF_GBK) -c code/cpp/win.cpp -o make/middleware/win.o

make/middleware/register.o:code/cpp/register.cpp
	g++ $(UTF_GBK) -c code/cpp/register.cpp -o make/middleware/register.o

make/middleware/timer.o:code/cpp/timer.cpp
	g++ $(UTF_GBK) -c code/cpp/timer.cpp -o make/middleware/timer.o

make/middleware/log.o:code/cpp/log.cpp
	g++ $(UTF_GBK) -c code/cpp/log.cpp -o make/middleware/log.o

make/middleware/graphics.o:code/cpp/graphics.cpp
	g++ $(UTF_GBK) -c code/cpp/graphics.cpp -o make/middleware/graphics.o

run:
	cd make && tetris.exe

clean:
	cd make/middleware && del *.o
	cd make && del *.exe

clean_o:
	cd make/middleware && del *.o

clean_log:
	cd data/log && del *.txt

#重新生成
remake:
	make clean
	make

delete:
	cd make/middleware && del $(name)

.PHONY:run clean clean_o remake delete clean_log


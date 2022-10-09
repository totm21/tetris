
#反斜杠\ 可以在下一行接着写


#字符兼容问题 输入UTF-8 输出GBK   问题在于github是按照UTF-8来读取的 但window是按照GBK来读取的  
UTF_GBK :=
#-finput-charset=UTF-8 -fexec-charset=GBK
#旧的解决方式是更改编译后的输出文件编码  现在的解决方式是更改控制台输出编码

#编译时 库文件链接策略   默认是动态  静态请输入:make version=-static  
version := 

#删除单个文件时使用  例如 make delete name=log.o 默认为make/middleware文件夹其他请自行调整(意义不大)
name := 

#发现了一些问题  重新编译时(删除全部中间件(.o)--重新编译)会同时删除插件支持中间件 我们不希望如此做(插件中间件大概率不会变--暂时没有魔改的想法  有也会自己重新写)
#所以引入路径的这个概念  也节省新增编译指令

#源码路径(cpp)
path_cpp := code/cpp/
#资源路径
path_resources := resources/
#插件路径
path_plugin := code/cpp/expands/
#中间件路径(非插件)
path_middle := make/middleware/
#中间件路径(插件)
path_middle_plugin := make/plugin/

all:tetris

#此处会非常长 所以规定每行最长三个!!!
tetris:$(path_middle)tetris.o $(path_middle)resources.o \
	$(path_middle_plugin)json_reader.o $(path_middle_plugin)json_writer.o $(path_middle_plugin)json_value.o \
	$(path_middle_plugin)glad.o \
	$(path_middle)define.o \
	$(path_middle)register.o $(path_middle)timer.o $(path_middle)log.o \
	$(path_middle)graphics.o $(path_middle)shader.o $(path_middle)template.o \

	g++ $(version) -o make/tetris \
		$(path_middle)tetris.o $(path_middle)resources.o \
		$(path_middle_plugin)json_reader.o $(path_middle_plugin)json_writer.o $(path_middle_plugin)json_value.o \
		$(path_middle_plugin)glad.o \
		$(path_middle)define.o \
		$(path_middle)register.o $(path_middle)timer.o $(path_middle)log.o \
		$(path_middle)graphics.o $(path_middle)shader.o $(path_middle)template.o \
	 	-mwindows -llua54 -lglfw3 -lgdi32 -lopengl32

#此处为资源文件编译!
$(path_middle)resources.o:$(path_resources)resources.rc
	windres -i $(path_resources)resources.rc -o $(path_middle)resources.o 
#资源文件 结束


#此处为插件头文件编译

#此处为jsoncpp 插件支持
$(path_middle_plugin)json_reader.o:$(path_plugin)json_reader.cpp
	g++ -c $(path_plugin)json_reader.cpp -o $(path_middle_plugin)json_reader.o

$(path_middle_plugin)json_writer.o:$(path_plugin)json_writer.cpp
	g++ -c $(path_plugin)json_writer.cpp -o $(path_middle_plugin)json_writer.o

$(path_middle_plugin)json_value.o:$(path_plugin)json_value.cpp
	g++ -c $(path_plugin)json_value.cpp -o $(path_middle_plugin)json_value.o
#jsoncpp 结束

#openGL glfw glad 插件支持
$(path_middle_plugin)glad.o:$(path_plugin)glad.c
	g++ -c $(path_plugin)glad.c -o $(path_middle_plugin)glad.o
#openGL 结束

#此处插件头编译结束


$(path_middle)tetris.o:$(path_cpp)tetris.cpp 
	g++ $(UTF_GBK) -c $(path_cpp)tetris.cpp -o $(path_middle)tetris.o 

$(path_middle)register.o:$(path_cpp)register.cpp
	g++ $(UTF_GBK) -c $(path_cpp)register.cpp -o $(path_middle)register.o

$(path_middle)timer.o:$(path_cpp)timer.cpp
	g++ $(UTF_GBK) -c $(path_cpp)timer.cpp -o $(path_middle)timer.o

$(path_middle)log.o:$(path_cpp)log.cpp
	g++ $(UTF_GBK) -c $(path_cpp)log.cpp -o $(path_middle)log.o

$(path_middle)graphics.o:$(path_cpp)graphics.cpp
	g++ $(UTF_GBK) -c $(path_cpp)graphics.cpp -o $(path_middle)graphics.o

$(path_middle)shader.o:$(path_cpp)shader.cpp
	g++ $(UTF_GBK) -c $(path_cpp)shader.cpp -o $(path_middle)shader.o

$(path_middle)template.o:$(path_cpp)template.cpp
	g++ $(UTF_GBK) -c $(path_cpp)template.cpp -o $(path_middle)template.o

$(path_middle)define.o:$(path_cpp)define.cpp
	g++ $(UTF_GBK) -c $(path_cpp)define.cpp -o $(path_middle)define.o

run:
	cd make && tetris.exe

clean_o:
	cd $(path_middle) && del *.o

clean_plugin:
	cd $(path_middle_plugin) && del *.o

clean_all:
	make clean_o
	make clean_plugin
	cd make && del *.exe

clean:
	cd $(path_middle) && del *.o
	cd make && del *.exe

clean_log:
	cd data/log && del *.txt

#重新生成(不包括插件)
remake:
	make clean
	make

#重新生成(包括插件)
remake_all:
	make clean_all
	make

delete:
	cd $(path_middle) && del $(name)

.PHONY:run clean_o clean_plugin clean_all clean clean_log remake delete  


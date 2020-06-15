# Set these paths to the appropriate locations on your machine
# before running 'mingw32-make'
INCLUDE_PATH = D:\Libraries\include
LIB_PATH = D:\Libraries\lib

build:
	g++ -w -std=c++14 -Wfatal-errors -static-libstdc++ \
	./src/*.cpp \
	-o test.exe \
	-I $(INCLUDE_PATH) \
	-L $(LIB_PATH) \
	-lmingw32 \
	-lSDL2main \
	-lSDL2

clean:
	del test.exe

run:
	test.exe
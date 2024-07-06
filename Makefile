TARGET=shooting.exe
CC=c++
FLAGS=-std=c++20 -g2 -Wall -Wextra -Werror -o $(TARGET)
INCPATH=-I./inc\
				-I./ext/SDL2/include
LIBPATH=-L./ext/SDL2/lib/x64 -lSDL2

INC=$(wildcard inc/*.h)
INC+=$(wildcard inc/*.hpp)

SRC=$(wildcard src/*.cc)
SRC+=$(wildcard src/*.cpp)

$(TARGET): Makefile $(INC) $(SRC)
	@$(CC) $(FLAGS) $(INCPATH) $(SRC) $(LIBPATH)
	@if not exist SDL2.dll powershell cp ext/SDL2/lib/x64/SDL2.dll SDL2.dll

all: $(TARGET)

re: clean all

clean:
	@if exist $(TARGET) del $(TARGET)
	@if exist SDL2.dll del SDL2.dll

.PHONY: all re clean

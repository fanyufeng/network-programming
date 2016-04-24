# Makefile

CC      = gcc
OBJ     = game.o game_basic.o game_process.o

CFLAGS  = -I ../libs

DIR_BIN = ../target

VPATH   = ../source : ../libs
TARGET1  = game 
#DIR_BIN = ./target

#TARGET1 = game
BIN_TARGET =${DIR_BIN}/${TARGET1}
 $(BIN_TARGET):	$(OBJ)
	$(CC) -o $@ $(OBJ)

%.o:%.c
	$(CC) $(CFLAGS) -c -g $<

game.o:game_global.h game_basic.h game_process.h


.PHONY:clean
clean:
	-rm -f target $(OBJ) $(BIN_TARGET)

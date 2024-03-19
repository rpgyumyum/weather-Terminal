OBJ_DIR := ./objs
CFLAGS := -Wall -Wextra

OBJS_todo := ./todo/todo-source.cpp
OBJS_weather := ./weather/main.cpp 
OBJS_nim := ./Nim-Game/nim.c ./Nim-Game/nim-algo.c


BIN_todo := todo
BIN_weather := weather
BIN_nim := nim

LIBS_todo :=
LIBS_weather := -lcurl -ljsoncpp
LIBS_nim := -lncurses -ltinfo

CC := g++
CC_nim := gcc



.PHONY: all todo weather nim clean
all: todo weather nim


todo:
	@echo "Compiling todo"
	mkdir -p ${OBJ_DIR}
	${CC} ${OBJS_todo} ${CFLAGS} -o ${OBJ_DIR}/${BIN_todo} ${LIBS_todo}

weather:
	@echo "Compiling weather"
	mkdir -p ${OBJ_DIR}
	${CC} ${OBJS_weather} ${CFLAGS} -o ${OBJ_DIR}/${BIN_weather} ${LIBS_weather}

nim:
	@echo "Compiling Nim"
	${CC_nim} ${OBJS_nim} ${CFLAGS} -o ${OBJ_DIR}/${BIN_nim} ${LIBS_nim}


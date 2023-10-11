OBJ_DIR := ./objs
CFLAGS := -Wall -Wextra

OBJS_todo := ./todo/todo-source.cpp
OBJS_weather := ./weather/main.cpp 


BIN_todo := todo
BIN_weather := weather

LIBS_todo :=
LIBS_weather := -lcurl -ljsoncpp

CC := g++



.PHONY: all todo weather clean
all: todo weather


todo:
	@echo "Compiling todo"
	mkdir -p ${OBJ_DIR}
	${CC} ${OBJS_todo} ${CFLAGS} -o ${OBJ_DIR}/${BIN_todo} ${LIBS_todo}

weather:
	@echo "Compiling weather"
	mkdir -p ${OBJ_DIR}
	${CC} ${OBJS_weather} ${CFLAGS} -o ${OBJ_DIR}/${BIN_weather} ${LIBS_weather}

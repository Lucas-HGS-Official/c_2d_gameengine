CC = clang
LANG_STD = -std=c99
COMPILER_FLAGS = -Wextra -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = src/*.c \
			src/game/*.c \
			libs/log_dot_c/*.c
LINKER_FLAGS = -llua -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

NAME = game_engine

###############################################

build:
	$(CC) $(LANG_STD) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(NAME)

run: build
	./$(NAME)

clean:
	rm $(NAME)

bear: clean
	bear -- make

CC = clang
LANG_STD = -std=c99
COMPILER_FLAGS = -Wextra -Wall -Wfatal-errors

INCLUDE_PATH_LIBS = -I"./libs/"
INCLUDE_PATH_ENGINE = -I"./src/components/" -I"./src/ECS" -I"./src/systems/"
INCLUDE_PATH = $(INCLUDE_PATH_LIBS) $(INCLUDE_PATH_ENGINE)

SRC_FILES_LIBS = libs/log_dot_c/*.c \
				 libs/darray/*.c
SRC_FILES_ENGINE = src/systems/*.c \
				   src/ECS/*.c \
				   src/components/*.c
SRC_FILES = src/*.c \
			src/game/*.c \
			$(SRC_FILES_LIBS) \
			$(SRC_FILES_ENGINE)

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

build:
	clang -std=c99 -Wextra -Wall -I"./libs/" src/*.c -llua5.4 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o gameengine

run: build
	./gameengine

clean:
	rm gameengine

bear: clean
	bear -- make

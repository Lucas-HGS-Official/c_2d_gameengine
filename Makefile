build:
	clang -std=c99 -Wextra -Wall src/*.c -llua5.4 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o gameengine

run: build
	./gameengine

clean:
	rm gameengine

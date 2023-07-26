all:
	clang -g src/*.c -Wall -Werror -lSDL2 -lSDL2_image -o bin/space-shooter.exe
	bin/./space-shooter.exe
  
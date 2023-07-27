all:
	clang -g src/*.c -Wall -Werror -lSDL2 -lSDL2_image -o bin/space-shooter.exe
	bin/./space-shooter.exe
check:
	valgrind  ./bin/space-shooter.exe                                                                           \
	--leak-check=full  -s    --leak-check=full --show-reachable=yes --show-leak-kinds=all     
  
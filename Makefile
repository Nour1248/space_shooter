all:
	clang -g src/*.c -Wall -Werror				\
	-lSDL2-2.0    -lSDL2_image  -lSDL2_mixer	\
	-I lib/includes/							\
	-L lib/soS/									\
	-o bin/space-shooter.out								
	# -fsanitize=address							\
	ASAN_OPTIONS=detect_leaks=1 bin/./space-shooter.out
check:
	valgrind  ./bin/space-shooter.out                                                             \
	--leak-check=full  -s --show-reachable=yes --show-leak-kinds=all --track-origins=yes

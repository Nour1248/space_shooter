dbg:
	clang -o1 -g src/*.c -Wall -Werror								\
	-lSDL2-2.0    -lSDL2_image  -lSDL2_mixer						\
	-I lib/includes/												\
	-L lib/soS/														\
	-fsanitize=address -fno-omit-frame-pointer						\
	-o bin/space-shooter.out								
	bin/./space-shooter.out

release:
	clang  -o3 src/*.c 										 		\
	-lSDL2-2.0    -lSDL2_image  -lSDL2_mixer						\
	-I lib/includes/												\
	-L lib/soS/														\
	-o bin/space-shooter.out								
	bin/./space-shooter.out
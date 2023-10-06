project( 'SPACE SHOOTER' ,'c' )
deps = [ dependency('SDL2'), dependency('SDL2_image'), dependency('SDL2_mixer'), dependency('glib-2.0') ]
src = [
    'src/app.c',
    'src/audio.c',
    'src/draw.c',
    'src/input.c',
    'src/lib_init.c',
    'src/main.c'
]
executable( 'space_shooter' ,sources: src ,dependencies: deps ,c_args : '-g' )
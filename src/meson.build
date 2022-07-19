openal = dependency('openal')
sources = [
    'main.c',
    'sound.h',
    'sound.c',
    'term.h',
    'term.c',
    'socket.h',
    'socket.c',
    'alloc.h',
    'alloc.c'
]

executable('out', sources, dependencies: [openal], c_args: ['-lm'], link_args: ['-lm'])

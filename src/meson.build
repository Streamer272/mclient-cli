openal = dependency('openal')
sources = [
    'main.c',
    'sound.h',
    'sound.c',
]

executable('out', sources, dependencies: [openal], c_args: ['-lm'], link_args: ['-lm'])

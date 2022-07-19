#include "sound.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <AL/al.h>
#include <AL/alc.h>

ALCdevice *openal_output_device;
ALCcontext *openal_output_context;



int check_error(const char *given_label) {
    ALenum al_error;
    al_error = alGetError();

    if (AL_NO_ERROR != al_error) {
        printf("ERROR - %s  (%s)\n", alGetString(al_error), given_label);
        return al_error;
    }

    return 0;
}

void init_al() {
    const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

    openal_output_device = alcOpenDevice(defname);
    openal_output_context = alcCreateContext(openal_output_device, NULL);
    alcMakeContextCurrent(openal_output_context);
}

void exit_al() {
    alcMakeContextCurrent(NULL);
    alGetError();
    alcDestroyContext(openal_output_context);
    alcCloseDevice(openal_output_device);
}

void play(float seconds) {
    ALuint internal_buffer;
    ALuint streaming_source;

    alGenBuffers(1, &internal_buffer);
    check_error("failed call to alGenBuffers");

    float freq = 500.f;
    unsigned sample_rate = 44100;
    double my_pi = 3.14159;
    size_t buf_size = seconds * sample_rate;
    short *samples = malloc(sizeof(short) * buf_size);

    int i = 0;
    for (; i < buf_size; ++i) {
        samples[i] = 32760 * sin((2.f * my_pi * freq) / sample_rate * i);
    }

    alBufferData(internal_buffer, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
    check_error("populating alBufferData");

    free(samples);

    alGenSources(1, &streaming_source);
    alSourcei(streaming_source, AL_BUFFER, internal_buffer);
    alSourcePlay(streaming_source);

    ALenum current_playing_state;
    do {
        alGetSourcei(streaming_source, AL_SOURCE_STATE, &current_playing_state);
        check_error("alGetSourcei AL_SOURCE_STATE");
    } while (AL_PLAYING == current_playing_state);

    alSourceStopv(1, &streaming_source);
    alSourcei(streaming_source, AL_BUFFER, 0);

    alDeleteSources(1, &streaming_source);
    alDeleteBuffers(16, &streaming_source);
    alGetError();
}

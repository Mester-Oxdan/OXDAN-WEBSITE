#include <portaudio.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (1024)
#define INITIAL_BUFFER_SIZE (SAMPLE_RATE * 10)

#pragma warning(disable : 4996)

// Define global variables
PaStream* stream;
int record_state;
int16_t* recorded_data;
int num_recorded_frames = 0;
int buffer_size = INITIAL_BUFFER_SIZE;

// Callback functions
static int record_callback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    const int16_t* in_data = (const int16_t*)inputBuffer;
    (void)outputBuffer; /* Prevent unused variable warning. */
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;

    if (record_state) {
        // Check if we need to expand the buffer
        if (num_recorded_frames + framesPerBuffer > buffer_size) {
            buffer_size *= 2;  // Double the buffer size
            recorded_data = (int16_t*)realloc(recorded_data, buffer_size * sizeof(int16_t));
            if (!recorded_data) {
                //cerr << "Error: Failed to allocate memory for recording data." << endl;
                printf("\033[0;31m");
                printf("\n");
                printf("(!ERROR!)");
                printf("\033[0;37m");
                printf(" = ");
                printf("\033[0;32m");
                cout << "(!Error: " << "Failed to allocate memory for recording data" << "!)\n";
                printf("\033[0;37m");
                return paAbort;
            }
        }

        // Copy the incoming data to the buffer
        memcpy(recorded_data + num_recorded_frames, in_data, framesPerBuffer * sizeof(int16_t));
        num_recorded_frames += framesPerBuffer;
    }

    return 0;
}

// Function to start recording
int start_recording() {
    record_state = 1;
    return 0;
}

// Function to stop recording
int stop_recording() {
    record_state = 0;
    return 0;
}

// Function to save the recorded data to a wav file
int save_to_wav(const char* filename) {
    FILE* fp;
    int n;

    fp = fopen(filename, "wb");
    if (!fp) return -1;

    // Write wav header
    fwrite("RIFF", 1, 4, fp);
    n = num_recorded_frames * 2 + 36;
    fwrite(&n, 4, 1, fp);
    fwrite("WAVEfmt ", 1, 8, fp);
    n = 16;
    fwrite(&n, 4, 1, fp);
    n = 1;
    fwrite(&n, 2, 1, fp);
    n = 1;
    fwrite(&n, 2, 1, fp);
    n = SAMPLE_RATE;
    fwrite(&n, 4, 1, fp);
    n = SAMPLE_RATE * 2;
    fwrite(&n, 4, 1, fp);
    n = 2;
    fwrite(&n, 2, 1, fp);
    n = 16;
    fwrite(&n, 2, 1, fp);
    fwrite("data", 1, 4, fp);
    n = num_recorded_frames * 2;
    fwrite(&n, 4, 1, fp);
    fwrite(recorded_data, 2, num_recorded_frames, fp);
    fclose(fp);

    return 0;
}

// Main function
int dictaphone_start()
{
    cout << "\n\033[0;31mPress 'Esc' for exit\033[0;37m" << endl;

    PaStreamParameters inputParameters;
    PaError err;

    // Allocate memory for recorded data
    recorded_data = (int16_t*)malloc(SAMPLE_RATE * 10 * sizeof(int16_t));  // Allocate memory for 10 seconds
    if (!recorded_data) return -1;

    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError) return -1;

    // Open input stream
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        record_callback,
        NULL
    );
    if (err != paNoError) return -1;

    // Start recording
    err = Pa_StartStream(stream);
    if (err != paNoError) return -1;

    start_recording();
    cout << "\033[0;33m[!] Recording Started!\033[0;37m" << endl;

    // Recording loop
    while (true) {
        if (_kbhit() && _getch() == 27) {  // Check if ESC is pressed
            stop_recording();
            break;
        }
        Pa_Sleep(100);  // Sleep for 100 ms to avoid busy-waiting
    }

    cout << "\033[0;32m[!] Recording Finished!\033[0;37m" << endl;

    // Stop recording
    err = Pa_CloseStream(stream);
    if (err != paNoError) return -1;

    // Terminate PortAudio
    err = Pa_Terminate();
    if (err != paNoError) return -1;

    // Save recorded data to a wav file
    save_to_wav("output_recorded_voice.wav");

    // Free allocated memory
    free(recorded_data);
    check_start_start();
}


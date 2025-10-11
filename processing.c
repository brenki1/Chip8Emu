#include "processing.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PIXEL_RATIO 10



//uau, variaveis globais!
uint8_t delayTimer;
pixel pixels[32][64];
extern bool drawFlag;


void SetDelay(uint8_t i) {
    delayTimer = i;
}

uint8_t GetDelay() {
    return delayTimer;
}

// void DrawCall(const bool screen[][64]) {
//     for(int i = 0; i < 32; ++i) {
//         for(int j = 0; j < 64; ++j) {
//             pixels[i][j].active = screen[i][j];
//         }
//     }
// }


void SetUpPixels() {
    for(int i = 0; i < 32; ++i) {
        for(int j = 0; j < 64; ++j) {
            pixels[i][j].active = 0;
            pixels[i][j].size.x = PIXEL_RATIO;
            pixels[i][j].size.y = PIXEL_RATIO;
            pixels[i][j].pos.x = PIXEL_RATIO * (float) j;
            pixels[i][j].pos.y = PIXEL_RATIO * (float) i;
            //if(i == 0 && j == 8) exit(-2);
        }
    }
}




void CPULoop() {
    // const float instructionsPerFrame = 500;
    // float timer = 1.0f / instructionsPerFrame;
    const int keymap[16] = {
        KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_A, KEY_S, KEY_D, KEY_F,
        KEY_Z, KEY_X, KEY_C, KEY_V
    };
    const int qtdInstrucoes = 5;
    while(!WindowShouldClose()) {
        if(delayTimer > 0) delayTimer -= GetFrameTime();
        for(int i = qtdInstrucoes; i > 0; --i) {
            Cycle(pixels);
        }

        BeginDrawing();
        for(int i = 0; i < 32; ++i) {
                for(int j = 0; j < 64; ++j) {
                    if(pixels[i][j].active) {
                        DrawRectangleV(pixels[i][j].pos, pixels[i][j].size, YELLOW);
                    }
                }
            }
        ClearBackground(BLACK);
        EndDrawing();
        for(int i = 0; i < 16; ++i) {
            if(IsKeyUp(keymap[i])) ClearKey(i);
            else ReadKey(i);
        }
    }
}






void StartProcessing(char *rom) {
    InitMemory();
    LoadRom(rom);
    SetUpPixels();
    char windowName[100] = "CHIP8 Emulator: ";
    strcat(windowName, rom);
    InitWindow(64 * PIXEL_RATIO, 32 * PIXEL_RATIO, windowName);
    SetTargetFPS(120);
    CPULoop();
    CloseWindow();
}
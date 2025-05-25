#include "processing.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

#define PIXEL_RATIO 20



//uau, variaveis globais!
uint8_t delayTimer;
pixel pixels[32][64];


void SetDelay(uint8_t i) {
    delayTimer = i;
}

uint8_t GetDelay() {
    return delayTimer;
}

void DrawCall(const bool screen[][64]) {
    for(int i = 0; i < 32; ++i) {
        for(int j = 0; j < 64; ++j) {
            pixels[i][j].active = screen[i][j];
        }
    }
}


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
    float instructionsPerSec = 500;
    float timer = 1.0f / instructionsPerSec;
    while(!WindowShouldClose()) {
        if(timer <= 0) {
            Cycle(pixels);
            timer = 1.0f / instructionsPerSec;
        }


        timer -= GetFrameTime();
        if(delayTimer >= 0) delayTimer -= GetFrameTime();
        printf("%d\n", delayTimer);
        ClearBackground(BLACK);
        BeginDrawing();
//            ClearBackground(BLACK);
            for(int i = 0; i < 32; ++i) {
                for(int j = 0; j < 64; ++j) {
                    if(pixels[i][j].active) {
                        //printf("\nQUE (%d, %d) -> %d ?!\n\n", i, j, pixels[i][j].active);
                        DrawRectangleV(pixels[i][j].pos, pixels[i][j].size, WHITE);
                    }
                }
            }
        EndDrawing();


    }

}






void StartProcessing(char *rom) {
    InitMemory();
    LoadRom(rom);
    SetUpPixels();
    InitWindow(64 * PIXEL_RATIO, 32 * PIXEL_RATIO, "test");
    SetTargetFPS(60);
    CPULoop();
}
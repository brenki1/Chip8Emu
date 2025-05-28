#include "processing.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

#define PIXEL_RATIO 10



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
    const float instructionsPerSec = 10e8;
    float timer = 1.0f / instructionsPerSec;
    while(!WindowShouldClose()) {


        timer -= GetFrameTime();
        if(delayTimer >= 0) delayTimer -= GetFrameTime();
        printf("%d\n", delayTimer);
        // Input


        // acho que tem como melhorar isso aqui
        switch (GetKeyPressed()) {
            case KEY_ONE: {
                ReadKey(0x0);
                break;
            }

            case KEY_TWO: {
                ReadKey(0x1);
                break;
            }

            case KEY_THREE: {
                ReadKey(0x2);
                break;
            }

            case KEY_FOUR: {
                ReadKey(0x3);
                break;
            }

            case KEY_Q: {
                ReadKey(0x4);
                break;
            }

            case KEY_W: {
                ReadKey(0x5);
                break;
            }

            case KEY_E: {
                ReadKey(0x6);
                break;
            }

            case KEY_R: {
                ReadKey(0x7);
                break;
            }

            case KEY_A: {
                ReadKey(0x8);
                break;
            }

            case KEY_S: {
                ReadKey(0x9);
                break;
            }

            case KEY_D: {
                ReadKey(0xA);
                break;
            }

            case KEY_F: {
                ReadKey(0xB);
                break;
            }

            case KEY_Z: {
                ReadKey(0xC);
                break;
            }

            case KEY_X: {
                ReadKey(0xD);
                break;
            }

            case KEY_C: {
                ReadKey(0xE);
                break;
            }

            case KEY_V: {
                ReadKey(0xF);
                break;
            }

            default: {
                break;
            }

        }

        Cycle(pixels);
        if(timer <= 0) {
            timer = 1.0f / instructionsPerSec;
        }


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
        //ClearKeys();
    }

}






void StartProcessing(char *rom) {
    InitMemory();
    LoadRom(rom);
    SetUpPixels();
    InitWindow(64 * PIXEL_RATIO, 32 * PIXEL_RATIO, "test");
    SetTargetFPS(960);
    CPULoop();
}
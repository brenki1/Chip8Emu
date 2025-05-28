#ifndef CHIP8_CPU_H

#define CHIP8_CPU_H

#include <stdint.h>
#include "processing.h"

void LoadRom(char *filePath);
void InitMemory();
void DumpRam();
void Cycle(pixel video[32][64]);
void ReadKey(int key);
void ClearKeys();

#endif //CHIP8_CPU_H

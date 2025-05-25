#ifndef UAI_PROCESSING_H
#define UAI_PROCESSING_H
#include <stdint.h>
#include <raylib.h>


typedef struct {
    Vector2 size;
    Vector2 pos;
    _Bool active;
} pixel;
//pra mostrar grafico faz igual o outro la e troca de acordo

void StartProcessing(char*);
void SetDelay(uint8_t i);
uint8_t GetDelay();
void DrawCall(const bool[][64]);


#endif //UAI_PROCESSING_H

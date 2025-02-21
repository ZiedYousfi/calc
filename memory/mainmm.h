#ifndef MAINMM_H
#define MAINMM_H

#include "../libs.h"
#include "../types.h"
#include "opsmm.h"

typedef struct MainMM {
    char** stringArray;
    int stringCount;
    operationList** listArray;
    int listCount;
} MemoryManager;

MemoryManager* createMainMM(void);
void trackString(MemoryManager* manager, char* str);
void trackList(MemoryManager* manager, operationList* list);
void releaseMainMM(MemoryManager* manager);

#endif

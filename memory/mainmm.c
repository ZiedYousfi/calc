#include "mainmm.h"

MemoryManager* createMainMM(void) {
    MemoryManager* manager = malloc(sizeof(MemoryManager));
    if (manager) {
        manager->stringArray = NULL;
        manager->stringCount = 0;
        manager->listArray = NULL;
        manager->listCount = 0;
    }
    return manager;
}

void trackString(MemoryManager* manager, char* str) {
    if (!manager || !str)
        return;

    char** newArray =
        realloc(manager->stringArray,
                ((size_t)manager->stringCount + 1) * sizeof(char*));
    if (newArray) {
        manager->stringArray = newArray;
        manager->stringArray[manager->stringCount++] = str;
    }
}

void trackList(MemoryManager* manager, operationList* list) {
    if (!manager || !list)
        return;

    operationList** newArray =
        realloc(manager->listArray,
                ((size_t)manager->listCount + 1) * sizeof(operationList*));
    if (newArray) {
        manager->listArray = newArray;
        manager->listArray[manager->listCount++] = list;
    }
}

void releaseMainMM(MemoryManager* manager) {
    if (!manager)
        return;

    if (manager->stringArray) {
        for (int i = 0; i < manager->stringCount; i++) {
            free(manager->stringArray[i]);
        }
        free(manager->stringArray);
    }

    if (manager->listArray) {
        for (int i = 0; i < manager->listCount; i++) {
            if (manager->listArray[i]) {
                freeOperationList(manager->listArray[i]);
            }
        }
        free(manager->listArray);
    }

    manager->stringArray = NULL;
    manager->listArray = NULL;
    manager->stringCount = 0;
    manager->listCount = 0;

    free(manager);
}

#include "memory/mainmm.h"
#include "utils/oputils.h"
#include "utils/sutils.h"

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    bool exit = false;
    MemoryManager* memManager = createMainMM();
    char* ee;
    operationList* elements;
    operationList* prevElements;
    int i = 0;

    while (!exit) {
        i++;

        printf("User input : ");
        ee = userInput();

        if (!ee) {
            printf("err : ee");
            releaseMainMM(memManager);
            return 1;
        }
        trackString(memManager, ee);

        exit = strcmp(ee, "exit") == 0;

        if (exit) {
            break;
        }

        elements =
            (i > 0) ? getElements(ee, prevElements) : getElements(ee, NULL);
        prevElements = elements;

        if (!elements || !prevElements) {
            printf("err : elements");
            releaseMainMM(memManager);
            return 1;
        }
        trackList(memManager, elements);
        trackList(memManager, prevElements);

        int numOps = elements->size;

        printf("%d\n", numOps);
    }

    releaseMainMM(memManager);
    return 0;
}

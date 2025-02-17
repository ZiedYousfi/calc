#include <stdio.h>
#include <stdlib.h>

#include "calcutils.h"

int main() {
    printf("User input : ");
    char* ee = userInput();

    if (!ee) {
        printf("err : ee");
        return 1;
    }

    operationList* elements = getElements(ee);

    if (!elements) {
        printf("err : elements");
        return 1;
    }

    printf("%d", elements->size);
    free(ee);
    freeOperationList(elements);
    return 0;
}

#include "calcutils.h"

void test() {
    operationList* elements = getElements("12+21+31");

    if (!elements) {
        printf("err : elements");
        return;
    }

    printf("%d", elements->size);
    freeOperationList(elements);
}

int main() {
    setbuf(stdout, NULL);
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

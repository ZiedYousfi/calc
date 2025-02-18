#include "oputils.h"

operationList* createOperationList() {
    operationList* list = malloc(sizeof(operationList));
    if (!list)
        return NULL;

    list->capacity = 2;
    list->size = 0;
    list->operations = malloc(sizeof(operation) * list->capacity);

    return list;
}

int addOperation(operationList* list, operation op) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        operation* temp =
            realloc(list->operations, sizeof(operation) * list->capacity);
        if (!temp) {
            return 1;
        }
        list->operations = temp;
    }

    list->operations[list->size++] = op;
    return 0;
}

void freeOperationList(operationList* list) {
    free(list->operations);
    free(list);
    return;
}

const operators ops[] = {
    {"add", "+"}, {"subtract", "-"}, {"multiply", "*"}, {"divide", "/"}};

int getOp(char* input) {
    int numOps = sizeof(ops) / sizeof(operators);

    for (int i = 0; i < numOps; i++) {
        if (strcmp(input, ops[i].opRep) == 0) {
            return i;
        }
    }

    printf("Aucun opérateur correspondant trouvé\n");
    printf("=== Fin getOp ===\n");
    return -1;
}


#include "opsmm.h"

operationList* createOperationList(void) {
    operationList* list = malloc(sizeof(operationList));
    if (!list)
        return NULL;

    list->capacity = 2;
    list->size = 0;
    list->operations = malloc(sizeof(operation) * (size_t)list->capacity);

    return list;
}

int addOperation(operationList* list, operation op) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        operation* temp = realloc(list->operations,
                                  sizeof(operation) * (size_t)list->capacity);
        if (!temp) {
            return 1;
        }
        list->operations = temp;
    }

    list->operations[list->size++] = op;
    return 0;
}

void freeOperationList(operationList* list) {
    if (!list) {
        return;
    }

    if (list->operations) {
        free(list->operations);
        list->operations = NULL;  // Set to NULL after freeing
    }

    free(list);
    return;
}

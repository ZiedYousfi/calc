#ifndef OPUTILS_H
#define OPUTILS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double_t firstNum;
    char op;
    double_t secNum;
    bool useFirstNumber;
} operation;

typedef struct {
    operation* operations;
    int size;
    int capacity;
} operationList;

operationList* createOperationList();
int addOperation(operationList* list, operation op);
void freeOperationList(operationList* list);

#endif

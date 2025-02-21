#ifndef TYPES_H
#define TYPES_H

#include "libs.h"

typedef struct {
    double_t firstNum;
    char* op;
    double_t secNum;
    bool useFirstNumber;
} operation;

typedef struct {
    operation* operations;
    int size;
    int capacity;
} operationList;

typedef struct {
    char* name;
    char* opRep;
} operators;

#endif

#ifndef OPUTILS_H
#define OPUTILS_H

#include "../libs.h"
#include "../memory/opsmm.h"
#include "../ops/constants.h"
#include "../types.h"

int getOp(char* input);
bool isOp(char* input, int pos);
operationList* getElements(char* input, operationList* prevOpList /* = NULL */);

#endif

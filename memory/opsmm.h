#ifndef OPSMM_H
#define OPSMM_H

#include "../libs.h"
#include "../types.h"

operationList* createOperationList(void);
int addOperation(operationList* list, operation op);
void freeOperationList(operationList* list);

#endif

#include "calcutils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oputils.h"

char* userInput() {
    int inputSize = 1;
    char* input = malloc(sizeof(char) * inputSize);
    int character, loopIt = 0;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (loopIt >= inputSize - 1) {
            inputSize *= 2;
            input = realloc(input, (sizeof(char) * inputSize));
            if (!input) {
                printf("Erreur de réallocation\n");
                return NULL;
            }
        }
        input[loopIt++] = (char)character;
    }
    input[loopIt] = '\0';
    printf("%n", &loopIt);
    return input;
}

operationList* getElements(char* input) {
    operationList* output = createOperationList();
    if (!output)
        return NULL;

    int numberOfOp = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
            input[i] == '/') {
            numberOfOp++;
        }
    }

    int* opPositions = malloc(sizeof(int) * numberOfOp);
    if (!opPositions) {
        freeOperationList(output);
        return NULL;
    }

    int opIndex = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
            input[i] == '/') {
            opPositions[opIndex++] = i;
            printf("op à %d\n", opPositions[opIndex - 1]);
        }
    }

    printf("Nombre d'opérations: %d\n", numberOfOp);

    int lastOpChecked = 0;

    int j = 0;

    for (int i = 0; i <= numberOfOp; i++) {
        operation tempop = {NAN, '\0', NAN, false};

        if (tempop.useFirstNumber || lastOpChecked == 0) {
            int j = 0;
        } else {
            int j = opPositions[i + 1];
        }

        char* numberStr = malloc(sizeof(char));
        if (!numberStr) {
            free(opPositions);
            freeOperationList(output);
            return NULL;
        }

        // Déclarer d'abord la taille
        int size =
            (j > 0) ? opPositions[j] - opPositions[j - 1] : opPositions[j];
        numberStr = realloc(numberStr, sizeof(char) * size + 1);
        if (!numberStr) {
            free(opPositions);
            freeOperationList(output);
            return NULL;
        }
        // Définir la position de début
        int startPos = (j > 0) ? opPositions[j - 1] : 0;

        // Copier la sous-chaîne
        strncpy(numberStr, &input[startPos], size);
        numberStr[size] = '\0';  // Assurer la terminaison

        if (tempop.useFirstNumber || lastOpChecked == 0) {
            if (isnan(tempop.firstNum)) {
                tempop.firstNum = atof(numberStr);
            } else {
                tempop.secNum = atof(numberStr);
            }
            tempop.useFirstNumber = true;
        } else {
            tempop.secNum = atof(numberStr);
        }
        lastOpChecked++;
        printf("firstnum est %f\n", tempop.firstNum);
        printf("secnum est %f\n", tempop.secNum);
        if (addOperation(output, tempop) != 0) {
            freeOperationList(output);
            return NULL;
        }
        free(numberStr);
    }

    return output;
}

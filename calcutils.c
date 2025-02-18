#include "calcutils.h"

#include <stdio.h>

#include "oputils.h"

void removeChar(char* str, char toRemove) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        if (*src != toRemove) {
            *dst = *src;
            dst++;
        }
    }
    *dst = '\0';
}

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
            printf("opPos %d : %d\n", opIndex - 1, opPositions[opIndex - 1]);
        }
    }

    printf("Nombre d'opérations: %d\n", numberOfOp);

    int lastOpChecked = 0;

    char* numberStr = malloc(sizeof(char));
    if (!numberStr) {
        free(opPositions);
        freeOperationList(output);
        return NULL;
    }

    operation tempop = {NAN, '\0', NAN, false};

    int j = 0;

    for (int i = 0; i <= numberOfOp; i++) {
        printf("\n--- Début itération %d ---\n", i);
        if (!isnan(tempop.secNum)) {
            tempop = (operation){NAN, '\0', NAN, false};
            printf("Réinitialisation de tempop\n");
        }

        j = (i > 1) ? i - 1 : 0;
        printf("Nombre suivant: j initialisé à %d\n", j);

        int size = (i > 1) ? opPositions[j] - opPositions[j - 1]
                           : (opPositions[j]) + 1;
        printf("Taille calculée pour le nombre: %d\n", size);

        numberStr = realloc(numberStr, sizeof(char) * (size + 1));
        printf("Réallocation de numberStr pour %d caractères\n", size + 1);

        if (!numberStr) {
            printf("ERREUR: Échec de l'allocation mémoire\n");
            free(opPositions);
            freeOperationList(output);
            return NULL;
        }
        int startPos = (i > 0) ? opPositions[j] : 0;
        printf("Extraction du nombre à partir de %s pour startPos : %d\n",
               &input[startPos], startPos);

        strncpy(numberStr, &input[startPos], size);
        numberStr[size] = '\0';
        printf("Nombre extrait (taille %d): %s\n", size, numberStr);

        if (i < numberOfOp) {
            char opStr[2] = {input[opPositions[i]], '\0'};

            int opPos = getOp(opStr);

            if (opPos >= 0) {
                tempop.op = ops[opPos].opRep[0];
            } else {
                printf("Erreur: Opérateur non reconnu\n");
            }
        }

        removeChar(numberStr, tempop.op);

        if (lastOpChecked == 0) {
            if (isnan(tempop.firstNum)) {
                tempop.firstNum = atof(numberStr);
                printf("Attribution du premier nombre: %f\n", tempop.firstNum);
            } else {
                tempop.secNum = atof(numberStr);
                printf("Attribution du second nombre: %f\n", tempop.secNum);
                lastOpChecked++;
            }
            tempop.useFirstNumber = true;
        } else {
            tempop.secNum = atof(numberStr);
            printf("Attribution du second nombre: %f\n", tempop.secNum);
            lastOpChecked++;
        }
        printf("lastOpChecked incrémenté à %d\n", lastOpChecked);
        printf("État de tempop - firstNum: %f, op : %c, secNum: %f\n",
               tempop.firstNum, tempop.op, tempop.secNum);

        if (!tempop.useFirstNumber) {
            if (addOperation(output, tempop) != 0) {
                freeOperationList(output);
                return NULL;
            }
            printf("Opération ajoutée avec succès\n");
        }

        printf("--- Fin itération %d ---\n", i);
    }

    free(numberStr);

    return output;
}

#include "calcutils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

    int opPosToUseSize = numberOfOp * 3;

    int* opPosToUse = malloc(sizeof(int) * opPosToUseSize);
    if (!opPosToUse)
        return NULL;
    printf("\nDébut allocation opPosToUse pour %d opérations\n",
           opPosToUseSize);

    for (int i = 0; i < opPosToUseSize - (numberOfOp % opPosToUseSize) + 1;
         i++) {
        printf("\n--- Itération %d ---\n", i);
        printf("opIndex actuel: %d\n", opIndex);

        int j = i + 1;

        if (i >= opIndex) {
            opPosToUse[j] = opIndex - 1;
            printf("i >= opIndex: opPosToUse[%d] = %d\n", j, opIndex);
        } else {
            opPosToUse[j] = i;
            printf("i < opIndex: opPosToUse[%d] = %d\n", j, i);
        }

        printf("Valeur stockée dans opPosToUse[%d] = %d\n", j, opPosToUse[j]);

        // Vérification des bornes
        if (opPosToUse[j] < 0 || opPosToUse[j] > numberOfOp) {
            printf("ERREUR: Tentative d'accès invalide à opPositions[%d]\n",
                   opPosToUse[j]);
            printf("numberOfOp = %d, index demandé = %d\n", numberOfOp,
                   opPosToUse[j]);
            // Ici vous pourriez gérer l'erreur
        } else {
            printf("Accès valide à opPositions[%d] = %d\n", opPosToUse[j],
                   opPositions[opPosToUse[j]]);
        }
    }
    printf("\nFin de l'initialisation de opPosToUse\n");

    int j = 0;

    for (int i = 0; i <= numberOfOp; i++) {
        printf("\n--- Début itération %d ---\n", i);
        if (!tempop.secNum) {
            operation tempop = {NAN, '\0', NAN, false};
            printf("Réinitialisation de tempop\n");
        }


            j = (i > 0) ? opPosToUse[i] : opPosToUse[i - 1];
            printf("Nombre suivant: j initialisé à %d\n", j);


        int size =
            (i > 0) ? opPositions[j + 1] - opPositions[j] : opPositions[j + 1];
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
        printf("État de tempop - firstNum: %f, secNum: %f\n", tempop.firstNum,
               tempop.secNum);

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

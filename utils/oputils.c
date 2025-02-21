#include "oputils.h"

int getOp(char* input) {
    int numOps = OPS_COUNT;

    for (int i = 0; i < numOps; i++) {
        if (strcmp(input, ops[i].opRep) == 0) {
            return i;
        }
    }

    printf("Aucun opérateur correspondant trouvé\n");
    printf("=== Fin getOp ===\n");
    return -1;
}

bool isOp(char* input, int pos) {
    int numOps = OPS_COUNT;

    for (int i = 0; i < numOps; i++) {
        size_t opRepSize = strlen(ops[i].opRep);
        char opStr[opRepSize + 1];
        strncpy(opStr, &input[pos], opRepSize);
        opStr[opRepSize] = '\0';
        if (strcmp(ops[i].opRep, opStr) == 0)
            return true;
    }
    return false;

    perror("bug?????");
    return NULL;
}

operationList* getElements(char* input, operationList* prevOpList) {
    operationList* output;

    if (!prevOpList) {
        output = createOperationList();
        if (!output)
            return NULL;
    } else {
        output = prevOpList;
    }

    int numberOfOp = 0, opIndex = 0, j = 0, lastOpChecked = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isOp(input, i)) {
            numberOfOp++;
        }
    }

    int* opPositions = calloc((size_t)numberOfOp, sizeof(int));
    if (!opPositions) {
        freeOperationList(output);
        return NULL;
    }

    for (int i = 0; input[i] != '\0'; i++) {
        if (isOp(input, i)) {
            opPositions[opIndex++] = i;
            printf("opPos %d : %d\n", opIndex - 1, opPositions[opIndex - 1]);
        }
    }

    if (opIndex == 0) {
        freeOperationList(output);
        free(opPositions);
        perror("no ops found");
        return NULL;
    }

    printf("Nombre d'opérations: %d\n", numberOfOp);

    if (!opPositions) {
        freeOperationList(output);
        return NULL;
    }

    char* numberStr = malloc(sizeof(char));
    if (!numberStr) {
        free(opPositions);
        freeOperationList(output);
        return NULL;
    }

    operation tempop = {NAN, "\0", NAN, false};

    for (int i = 0; i <= numberOfOp; i++) {
        printf("\n--- Début itération %d ---\n", i);
        if (!isnan(tempop.secNum)) {
            tempop = (operation){NAN, "\0", NAN, false};
            printf("Réinitialisation de tempop\n");
        }

        j = (i > 1) ? i - 1 : 0;
        printf("Nombre suivant: j initialisé à %d\n", j);

        int size =
            (i > 1) ? opPositions[j] - opPositions[j - 1] : (opPositions[j]);
        printf("Taille calculée pour le nombre: %zu\n", (size_t)size);

        numberStr = realloc(numberStr, sizeof(char) * ((size_t)size + 1));
        printf("Réallocation de numberStr pour %zu caractères\n",
               (size_t)size + 1);

        if (!numberStr) {
            printf("ERREUR: Échec de l'allocation mémoire\n");
            free(opPositions);
            freeOperationList(output);
            return NULL;
        }
        int startPos = (lastOpChecked > 0) ? opPositions[j] + 1 : 0;
        printf("Extraction du nombre à partir de %s pour startPos : %d\n",
               &input[startPos], startPos);

        strncpy(numberStr, &input[startPos], (size_t)size);
        numberStr[size] = '\0';
        printf("Nombre extrait (taille %d): %s\n", size, numberStr);

        if (i < numberOfOp) {
            char opStr[2] = {input[opPositions[i]], '\0'};

            int opPos = getOp(opStr);

            if (opPos >= 0) {
                tempop.op = ops[opPos].opRep;
            } else {
                printf("Erreur: Opérateur non reconnu\n");
            }
        }
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
        printf("État de tempop - firstNum: %f, op : %s, secNum: %f\n",
               tempop.firstNum, tempop.op, tempop.secNum);

        if (!isnan(tempop.secNum)) {
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

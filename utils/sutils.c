#include "sutils.h"

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

char* userInput(void) {
    size_t inputSize = 1;
    char* input = malloc(sizeof(char) * inputSize);
    int character, loopIt = 0;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (loopIt >= (int)inputSize - 1) {
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

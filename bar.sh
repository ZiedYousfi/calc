#!/bin/bash

# Formate tous les fichiers .c et .h avec clang-format
find . -name "*.c" -o -name "*.h" | xargs clang-format -i

# Compile tous les fichiers .c en un exécutable nommé 'calc'
C_FILES=$(find . -name "*.c")
clang -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra -Wpedantic -Wconversion -Wshadow -o calc $C_FILES

# Exécute le programme
./calc

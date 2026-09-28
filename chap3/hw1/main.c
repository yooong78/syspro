#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 100
#define NUM_LINES 5

int main() {
    char lines[NUM_LINES][MAXLINE];
    char temp[MAXLINE];
    int count = 0;

    while (count < NUM_LINES) {
        if (fgets(lines[count], MAXLINE, stdin) != NULL) {
            lines[count][strcspn(lines[count], "\n")] = '\0';
            count++;
        }
    }

    for (int i = 0; i < NUM_LINES - 1; i++) {
        for (int j = 0; j < NUM_LINES - 1 - i; j++) {
            if (strlen(lines[j]) < strlen(lines[j + 1])) {
                copy(lines[j], temp);
                copy(lines[j + 1], lines[j]);
                copy(temp, lines[j + 1]);
            }
        }
    }

    for (int i = 0; i < NUM_LINES; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

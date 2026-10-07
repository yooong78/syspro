#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char savedText[100][256];
    char buf;
    int line = 0, col = 0;
    char select[100];

    if (argc < 2) {
        fprintf(stderr, "How to use : %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
        } else {
            savedText[line][col++] = buf;
        }
    }
    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", line);
    printf("You can choose 1 ~ %d Line\n", line);
    printf("Pls 'Enter' the line to select : ");

    if (scanf("%s", select) != 1) {
        exit(3);
    }

    if (strcmp(select, "*") == 0) {
        for (int i = 0; i < line; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (strchr(select, '-') != NULL) {
        int start, end;
        sscanf(select, "%d-%d", &start, &end);
        for (int i = start; i <= end; i++) {
            if (i >= 1 && i <= line) {
                printf("%s\n", savedText[i - 1]);
            }
        }
    } else if (strchr(select, ',') != NULL) {
        char *token = strtok(select, ",");
        while (token != NULL) {
            int num = atoi(token);
            if (num >= 1 && num <= line) {
                printf("%s\n", savedText[num - 1]);
            }
            token = strtok(NULL, ",");
        }
    } else {
        int num = atoi(select);
        if (num >= 1 && num <= line) {
            printf("%s\n", savedText[num - 1]);
        }
    }

    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char savedText[100][256];
    char buf;
    int line = 0, col = 0;

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

    for (int i = line - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    exit(0);
}

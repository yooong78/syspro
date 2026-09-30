#include <stdio.h>
#include <stdlib.h>
#include "student.h"

/* save student records to a binary file using struct */
int main(int argc, char *argv[])
{
    struct student rec;
    FILE *fp;
    int score;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "wb");
    printf("%-9s %-7s %-4s\n", "StudentID", "Name", "Score");

    while (scanf("%d %19s %d", &rec.id, rec.name, &score) == 3) {
        rec.score = (short)score;
        fwrite(&rec, sizeof(rec), 1, fp);
    }

    fclose(fp);
    exit(0);
}


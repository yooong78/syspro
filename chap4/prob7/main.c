#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[]) 
{
    struct student rec;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        return 1; 
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "File Open Error\n");
        return 2;
    }

    printf("-----------------------------------\n");
    printf("%-9s %-7s %-4s\n", "StudentID", "Name", "Score"); 
    printf("-----------------------------------\n");

    while (fscanf(fp, "%d %s %hd", &rec.id, rec.name, &rec.score) == 3) {
        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    }

    printf("-----------------------------------\n");
    fclose(fp);
    return 0;
}

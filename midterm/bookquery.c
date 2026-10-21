#include <stdio.h> 
#include "bookcreate.c"
int main(int argc, char* argv[]) 
{ 
struct student rec;
FILE *fp;
if (argc != 2) {
fprintf(stderr, "How to use: %s FileName\n", argv[0]);
return 1; 
}
fp = fopen(argv[1], "w");
printf("%-9s %-7s %-4s\n", "id", "bookname", "author", "year", "numofborrow", "borrow"); 
while (scanf("%d %s %d %s %d %s", &rec.id, rec.bookname, &rec.author,rec.year, rec.numofborrow, rec.borrow)==6) 
fprintf(fp, "%d %s %d %s %d %s", rec.id, rec.bookname, rec.author, rec.year, rec.numofborrow, rec.borrow);
fclose(fp);
return 0;
}

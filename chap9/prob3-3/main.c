#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int child, pid, status;
    pid = fork();
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s:실행 불가\n", argv[1]);
        exit(1);
    } else if (pid > 0) {
        child = wait(&status);
        printf("[%d] child process %d end \n", getpid(), pid);
        printf("\tend code %d \n", status >> 8);
    } else {
        perror("fork error");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARG 64
#define MAXLINE 1024

int main() {
    char line[MAXLINE];
    char *args[MAXARG];

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        // 개행 문자 제거
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;

        int bg = 0;
        int i = 0;
        char *saveptr;
        char *token = strtok_r(line, " \t", &saveptr);

        while (token != NULL && i < MAXARG - 1) {
            if (strcmp(token, "&") == 0) {
                bg = 1;
            } else {
                args[i++] = token;
            }
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;
        if (strcmp(args[0], "exit") == 0) break;

        printf("[%d] Parent process start\n", getpid());
        int pid = fork();

        if (pid == 0) {
            if (bg) {
                printf("[%d] child process start\n", getpid());
            }
            execvp(args[0], args);
            exit(1);
        } else if (pid > 0) {
            int status;
            int child = wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                if (bg) {
                    printf("[%d] child process end %d\n", getpid(), child);
                }
                printf("SUCCESS\n\n");
            } else {
                printf("Parent process end\n");
                printf("Exit\n");
                break;
            }
        } else {
            perror("fork error");
        }
    }
    return 0;
}

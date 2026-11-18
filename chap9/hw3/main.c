#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

void execute_cmd(char *cmd) {
    char *args[MAXARG];
    char *infile = NULL, *outfile = NULL;
    int bg = 0;
    int i = 0;

    // 1. 후면 실행(&) 확인 및 제거
    char *amp = strchr(cmd, '&');
    if (amp != NULL) {
        bg = 1;
        *amp = '\0';
    }

    // 2. 토큰 분리 및 입출력 리디렉션(<, >) 파싱
    char *saveptr;
    char *token = strtok_r(cmd, " \t\n", &saveptr);
    while (token != NULL && i < MAXARG - 1) {
        if (strcmp(token, ">") == 0) {
            outfile = strtok_r(NULL, " \t\n", &saveptr);
        } else if (strcmp(token, "<") == 0) {
            infile = strtok_r(NULL, " \t\n", &saveptr);
        } else {
            args[i++] = token;
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }
    args[i] = NULL;

    if (args[0] == NULL) return;
    if (strcmp(args[0], "exit") == 0) exit(0);

    // 3. 자식 프로세스 생성 및 실행
    pid_t pid = fork();
    if (pid == 0) {
        if (outfile != NULL) {
            int fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if (fd < 0) { perror("open outfile"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (infile != NULL) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) { perror("open infile"); exit(1); }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(args[0], args);
        fprintf(stderr, "%s: command not found\n", args[0]);
        exit(1);
    } else if (pid > 0) {
        if (!bg) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[Background] PID: %d\n", pid);
        }
    } else {
        perror("fork failed");
    }
}

int main() {
    char line[MAXLINE];
    while (1) {
        printf("[shell] ");
        fflush(stdout);
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        // 세미콜론(;) 기준 순차 실행 처리
        char *saveptr;
        char *cmd = strtok_r(line, ";\n", &saveptr);
        while (cmd != NULL) {
            execute_cmd(cmd);
            cmd = strtok_r(NULL, ";\n", &saveptr);
        }
    }
    return 0;
}

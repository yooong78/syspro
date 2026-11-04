#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-e[VAR]] [-u] [-g] [-i] [-p]\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char opt = argv[i][1];
            switch (opt) {
                case 'e':
                    if (argv[i][2] != '\0') {
                        // -eNAME 형태로 인자가 붙어서 넘어온 경우
                        char *val = getenv(&argv[i][2]);
                        if (val)
                            printf("%s = %s\n", &argv[i][2], val);
                    } else if (i + 1 < argc && argv[i+1][0] != '-') {
                        // -e NAME 형태로 띄어쓰기하여 넘어온 경우
                        char *val = getenv(argv[i+1]);
                        if (val)
                            printf("%s = %s\n", argv[i+1], val);
                        i++; // 다음 인자 건너뛰기
                    } else {
                        // 환경변수 이름이 없으면 모든 환경변수 출력
                        for (char **ptr = environ; *ptr != NULL; ptr++) {
                            printf("%s\n", *ptr);
                        }
                    }
                    break;

                case 'u':
                    printf("My Realistic User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
                    printf("My Valid User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
                    break;

                case 'g':
                    printf("My Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
                    printf("My Valid Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
                    break;

                case 'i':
                    printf("my process number : [%d]\n", getpid());
                    break;

                case 'p':
                    printf("my parent's process number : [%d]\n", getppid());
                    break;

                default:
                    fprintf(stderr, "Unknown option: %s\n", argv[i]);
                    break;
            }
        }
    }

    return 0;
}

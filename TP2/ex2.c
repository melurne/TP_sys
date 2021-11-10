#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t son = fork();
    if (son != 0) {
        printf("father: PID = %d, PPID = %d\n", getpid(), getppid());
        waitpid(son);
    }
    else {
        pid_t grand_son = fork();
        if (grand_son == 0) {
            sleep(2);
            printf("grand son PID = %d, PPID = %d\n", getpid(), getppid());
        }
        else {
            printf("son: PID = %d, PPID = %d\n", getpid(), getppid());
            waitpid(grand_son);
            sleep(2);
        }
        
    }
}
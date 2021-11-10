#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t son = fork();
    if (son != 0) {
        pid_t son2 = fork();
        if (son2 == 0){
            sleep(4);
            printf("son: PID = %d, PPID = %d\n", getpid(), getppid());
        }
        else {
            printf("father: PID = %d, PPID = %d\n", getpid(), getppid());
            
        }
        waitpid(son);
        waitpid(son2);
    }
    else {
        sleep(2);
        printf("son: PID = %d, PPID = %d\n", getpid(), getppid());
    }
}
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/shm.h> 
#include <fcntl.h>

#define BUFFER_LEN 80

int main() {
    int fd[2];
    pid_t son;
    char* buffer = malloc(sizeof(char)*BUFFER_LEN);

    char* cmd1 = "grep '|gayant| ~/TP_sys/printaccounting'";
    char* args1[2] = {"\"|gayant|\"", "~/TP_sys/printaccounting", (char*)NULL};
    char* cmd2 = "cut -f2 -d\\|";

    pipe(fd);

    son = fork();

    if (son == 0) {
        close(fd[0]);
        dup(fd);
        execve("/usr/bin/grep", args1, NULL);
        //write(fd[1], buffer, BUFFER_LEN);
        exit(0);
    }    
    else {
        close(fd[1]);
        dup(fd);
        FILE* output = fopen("/tmp/liste", "w");
        execl("/usr/bin/cut", "|", "2", (char*)NULL);
        //read(fd[0], buffer, BUFFER_LEN);

        

    }
}
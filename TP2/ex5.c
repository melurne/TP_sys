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

int main() {
    char* fichier = malloc(sizeof(char)*10);
    fgets(fichier, 10, stdin);
    pid_t son = fork();

    if (son == 0) {
        
    }

}
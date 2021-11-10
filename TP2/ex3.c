#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signum) {
    printf("Programm stopped by signal %d\n", signum);
    exit(0);
}

int main() {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    while (1) {
    }
}
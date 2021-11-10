#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signum) {
    sigignore(SIGQUIT);
    printf("Programm paused by %d\n", signum);
    sigrelse(SIGQUIT);
    sleep(10);
}

int main() {
    struct sigaction action;
    action.sa_handler = sig_handler;
    sigaction(SIGINT, &action, NULL);
    while (1) {
        printf("running\n");
    }
}
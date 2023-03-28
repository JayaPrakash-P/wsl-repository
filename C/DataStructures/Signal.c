#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void signal_handler(int signo) {
    printf("Received signal %d\n", signo);
}

int main() {
    sigset_t mask;
    struct sigaction sa;
    int i;

    // Set up the signal handler
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    for (int sig = 1; sig <= SIGRTMAX; ++sig) {
        // this might return -1 and set errno, but we don't care
        sigaction(sig, &sa, NULL);
    }

    // Block the SIGINT signal
    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    // Loop forever, waiting for signals
    for (i = 0; i < 200 ; i++) {
        printf("Loop iteration %d\n", i);
        sleep(1);
        if(i==100)
        {
            if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) {
                perror("sigprocmask");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}

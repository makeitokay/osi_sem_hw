#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile pid_t senderPid;
volatile sig_atomic_t bits[32];
volatile sig_atomic_t count = 0;

void receiveHandler(int signal) {
    int bit = signal == SIGUSR1 ? 0 : 1;
    bits[count] = bit;
    count++;
    kill(senderPid, SIGUSR1);
}

void finishHandler(int signal) {
    int number = 0;
    for (int i = 0; i < 32; i++) {
        if (bits[i] == 1) {
            number |= (1 << i);
        }
    }
    printf("Received number: %d", number);
    exit(0);
}

int main() {
    int pid = getpid();
    printf("Process ID: %d\n", pid);

    printf("Sender PID: ");
    scanf("%d", &senderPid);

    signal(SIGUSR1, receiveHandler);
    signal(SIGUSR2, receiveHandler);
    signal(SIGINT, finishHandler);

    while (1) {
        if (count == 32) {
            break;
        }
    }

    return 0;
}
//
// Created by makeitokay on 03.06.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t flag = 0;

void signalHandler(int signal) {
    flag = 1;
}

void sendBinarySignal(int pid, int bit) {
    flag = 0;
    int signalType = bit == 0 ? SIGUSR1 : SIGUSR2;
    kill(pid, signalType);

    while (flag == 0) {
    }
}

int main() {
    signal(SIGUSR1, signalHandler);

    int processId = getpid();
    printf("Process ID: %d\n", processId);

    int receiverPid;
    printf("Receiver PID: ");
    scanf("%d", &receiverPid);

    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    for (int i = 0; i < 32; i++) {
        int bit = (number >> i) & 1;
        sendBinarySignal(receiverPid, bit);
    }

    kill(receiverPid, SIGINT);

    return 0;
}
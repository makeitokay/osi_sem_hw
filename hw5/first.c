//
// Created by makeitokay on 04.06.2023.
//

#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

const int SIZE = 5000;

int main(int argc, char** argv) {
    char buffer[SIZE];

    char* first_fifo_name = argv[1];
    char* second_fifo_name = argv[2];

    createFifo(first_fifo_name);
    createFifo(second_fifo_name);

    printf("Первый процесс: отправляем сообщение в первый канал.\n");
    strcpy(buffer, "Message from the first process");

    int first_fd = getWriteonlyFifo(first_fifo_name);

    writeToFd(first_fd, buffer, SIZE);

    closeFd(first_fd);

    char second_buffer[SIZE];

    printf("Первый процесс: считываем данные из второго канала и выводим в консоль.\n");

    int second_fd = getReadonlyFifo(second_fifo_name);

    readFromFd(second_fd, second_buffer, SIZE);

    printf("FROM SECOND PROCESS: %s\n", second_buffer);

    closeFd(second_fd);

    return 0;
}
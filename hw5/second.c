//
// Created by makeitokay on 04.06.2023.
//

#include "utils.h"
#include <stdio.h>
#include <string.h>

const int SIZE = 5000;

int main(int argc, char** argv) {
    char buffer[SIZE];

    char* first_fifo_name = argv[1];
    char* second_fifo_name = argv[2];

    createFifo(first_fifo_name);
    createFifo(second_fifo_name);

    printf("Второй процесс: считываем данные из первого канала и выводим в консоль.\n");

    int first_fd = getReadonlyFifo(first_fifo_name);

    readFromFd(first_fd, buffer, SIZE);

    printf("FROM FIRST PROCESS: %s\n", buffer);

    closeFd(first_fd);

    int second_fd = getWriteonlyFifo(second_fifo_name);

    printf("Второй процесс: отправляем сообщение во второй канал.\n");
    strcpy(buffer, "Message from the second process");

    writeToFd(second_fd, buffer, SIZE);

    closeFd(second_fd);


    return 0;
}
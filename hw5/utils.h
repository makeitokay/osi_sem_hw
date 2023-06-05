//
// Created by makeitokay on 04.06.2023.
//

#ifndef OSI_SEM_HW_HW5_UTILS_H_
#define OSI_SEM_HW_HW5_UTILS_H_

void readFromFile(char filename[], char result[]);
void writeToFile(char filename[], char content[]);
void closeFd(int fd);
void readFromFd(int fd, char output[], int size);
void writeToFd(int fd, char content[], int size);

void createFifo(char name[]);
int getReadonlyFifo(char name[]);
int getWriteonlyFifo(char name[]);

#endif  // OSI_SEM_HW_HW5_UTILS_H_

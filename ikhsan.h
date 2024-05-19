#ifndef IKHSAN_H
#define IKHSAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

void readFileToQueue(Queue *q);
void displayPembeli(Queue *q);
void dequeue(Queue *q);
void updateFile(Queue *q);
void copyFileContents(const char *sourceFile, const char *destinationFile);
void deleteTempFile(const char *filename);
void removeFromQueue(Queue *q);

#endif
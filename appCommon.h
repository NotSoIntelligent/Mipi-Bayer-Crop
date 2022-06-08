/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rawProcess.h"

/* MACROS */
#define SUCCESS 0
#define FAIL -1
#define BYTE 8

/* Common used Function prototypes */
int getNum (char *str);
void printUsage ();
int processArgs (struct imageInfo *imgData, int argc, char *argv[], char **filename);
void freeIfValid(void **ptr);
void fcloseIfValid(FILE **fp);

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void newDisease(char *name, char *diseaseDesc);

extern void copyDisease(char *name1, char *name2);

extern void changeDesc(char *name, int n, char *diseaseDesc);

extern void printDesc(char *name, int n);

extern void deletePatientData(char *name);

extern void freeAll();
#endif /* STRUCTURE_H */

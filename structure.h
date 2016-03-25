#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void newDisease(char *name1, char *diseaseDesc);

extern void copyDisease(char *name1, char *name2);

extern void changeDesc(char *name1, int n, char *diseaseDesc);

extern void printDesc(char *name1, int n);

extern void deletePatientData(char *name1);

extern void freeAll();

extern int diseasesNumber();
#endif /* STRUCTURE_H */

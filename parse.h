#ifndef PARSE_H
#define PARSE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE 100000

enum Input {NEW_DISEASE, COPY_DISEASE, DESC_CHANGE, DESC_PRINT, DEL_PATIENT_DATA, END_OF_INPUT};

typedef struct inputData {
	enum Input inputType;
	char *name1;
	char *name2;
	char *diseaseDesc;
	int nr;
} InputData;

extern InputData readData(void);
#endif /* PARSE_H */

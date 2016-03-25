#include "structure.h"

/* TYPE DEFINITIONS */

typedef struct disease{
	int counter;
	char *description;
} Disease;

typedef struct diseaseList {
	Disease *lastDisease;
	struct diseaseList *prevDisease;
} DiseaseList;

typedef struct patient {
	char *name;
	int diseasesNr;
	DiseaseList *diseases;
} Patient;

typedef struct patientList {
	Patient first;
	struct patientList *next;
} PatientList;

/* REQUIRED DATA */
int diseaseCounter = 0;

PatientList *patients;

/* AUXILIARY FUNCTIONS */

static void freeDisease(Disease *dis) {
	diseaseCounter--;
	free(dis->description);
	free(dis);
	return;
}

static void freeDiseaseList(DiseaseList *disList) {
	disList->lastDisease->counter--;
	if (disList->lastDisease->counter == 0) {
		freeDisease(disList->lastDisease);
	}
	if (disList->prevDisease != NULL) {
		freeDiseaseList(disList->prevDisease);
	}
	free(disList);
	return;
}

static void freePatient(Patient *pat) {
	if (pat->diseases != NULL)
		freeDiseaseList(pat->diseases);
	pat->diseasesNr = 0;
	pat->diseases = NULL;
	return;
}

static void freePatientList(PatientList *patList) {
	freePatient(&(patList->first));
	free(patList->first.name);
	if (patList->next != NULL) {
		freePatientList(patList->next);
	}
	free(patList);
	return;
}

void freeAll() {
	freePatientList(patients);
	return;
}

int diseasesNumber() {
	return diseaseCounter;
}

/* REQUIRED FUNCTIONS */

void newDisease(char *name1, char *diseaseDesc) {
	diseaseCounter++;
	PatientList **iter = &patients;
	Disease *temp = (Disease*) malloc(sizeof(Disease));
	DiseaseList *tempList = (DiseaseList*) malloc(sizeof(DiseaseList));
	temp->counter = 1;
	temp->description = (char*) malloc(sizeof(char) * (strlen(diseaseDesc) + 1));
	strcpy(temp->description, diseaseDesc);
	//printf("%s\n", temp->description);
	tempList->lastDisease = temp;
	while(*iter != NULL) {
		if (strcmp((*iter)->first.name, name1) == 0) {
			tempList->prevDisease = (*iter)->first.diseases;
			(*iter)->first.diseases = tempList;
			(*iter)->first.diseasesNr++;
			printf("OK\n");
			return;
		}
		iter = &((*iter)->next);
	}
	*iter = (PatientList*) malloc(sizeof(PatientList));
	Patient tempPat;
	tempPat.name = (char*) malloc(sizeof(char) * (strlen(name1) + 1));
	strcpy(tempPat.name, name1);
	tempPat.diseasesNr = 1;
	tempList->prevDisease = NULL;
	tempPat.diseases = tempList;
	(*iter)->first = tempPat;
	(*iter)->next = NULL;
	printf("OK\n");
	return;
}

void printDesc(char *name1, int n) {
	PatientList *iter = patients;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name1) == 0) {
			if (n > iter->first.diseasesNr) {
				printf("IGNORED\n");
				return;
			}
			n = iter->first.diseasesNr - n;
			DiseaseList *tempList = iter->first.diseases;
			while(n != 0) {
				tempList = tempList->prevDisease;
				n--;
			}
			printf("%s\n", tempList->lastDisease->description);
			return;
		}
		iter = iter->next;		
	}
	printf("IGNORED\n");
	return;
}

void copyDisease(char *name1, char *name2) {
	PatientList **iter = &patients;
	Patient *pat1 = NULL, *pat2 = NULL;
	Disease *temp = NULL;
	DiseaseList *tempList = NULL;
	while((*iter) != NULL) {
		if (strcmp((*iter)->first.name, name1) == 0) {
			pat1 = &((*iter)->first);
		} else if (strcmp((*iter)->first.name, name2) == 0) {
			pat2 = &((*iter)->first);
		}
		iter = &((*iter)->next);
	}
	if (pat2 == NULL) {
		printf("IGNORED\n");
		return;
	} else if (pat2->diseases == NULL) {
		printf("IGNORED\n");
		return;
	}
	if (pat1 == NULL) {
		*iter = (PatientList *) malloc(sizeof(PatientList));
		pat1 = &((*iter)->first);
		pat1->name = (char *) malloc(sizeof(char) * (strlen(name1) + 1));
		strcpy(pat1->name, name1);
		pat1->diseases = NULL;
		pat1->diseasesNr = 0;
		(*iter)->next = NULL;
	}
    tempList = (DiseaseList *) malloc(sizeof(DiseaseList));
	pat1->diseasesNr++;
	temp = pat2->diseases->lastDisease;
	temp->counter++;
	tempList->lastDisease = temp;
	tempList->prevDisease = pat1->diseases;
	pat1->diseases = tempList;
	printf("OK\n");
	return;
}

void changeDesc(char *name1, int n, char *diseaseDesc) {
	PatientList *iter = patients;
	Disease *temp = NULL;
	DiseaseList **tempList = NULL;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name1) == 0) {
			if (n > iter->first.diseasesNr) {
				printf("IGNORED\n");
				return;
			}
			diseaseCounter++;
			n = iter->first.diseasesNr - n;
			tempList = &(iter->first.diseases);
			temp = (Disease *) malloc(sizeof(Disease));
			temp->counter = 1;
			temp->description = (char *) malloc(sizeof(char) * (strlen(diseaseDesc) + 1));
			strcpy(temp->description, diseaseDesc);
			while(n != 0) {
				tempList = &((*tempList)->prevDisease);
				n--;
			}
			(*tempList)->lastDisease->counter--;
			if ((*tempList)->lastDisease->counter == 0) {
				freeDisease((*tempList)->lastDisease);
			}
			(*tempList)->lastDisease = temp;
			printf("OK\n");
			return;
		}
		iter = iter->next;
	}
	printf("IGNORED\n");
	return;
}

void deletePatientData(char *name1) {
	PatientList *iter = patients;
	
	while(iter != NULL) {
		if (strcmp(iter->first.name, name1) == 0) {
			freePatient(&(iter->first));
			printf("OK\n");
			return;
		}
		iter = iter->next;
	}
	printf("IGNORED\n");
	return;
}

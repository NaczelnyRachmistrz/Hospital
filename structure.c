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
PatientList *patients;

int diseaseCounter = 0;

/* AUXILIARY FUNCTIONS */

static void freeDisease(Disease *dis) {
	free(dis->description);
	free(dis);
	return;
}

static void freePatient(Patient *pat) {
	return;
}

void freeAll() {
	return;
}

/* REQUIRED FUNCTIONS */

void newDisease(char *name, char *diseaseDesc) {
	diseaseCounter++;
	PatientList **iter = &patients;
	Disease *temp = (Disease*) malloc(sizeof(Disease));
	DiseaseList *tempList = (DiseaseList*) malloc(sizeof(DiseaseList));
	temp->counter = 1;
	temp->description = (char*) malloc(sizeof(char) * strlen(diseaseDesc));
	strcpy(temp->description, diseaseDesc);
	tempList->lastDisease = temp;
	while(*iter != NULL) {
		if (strcmp((*iter)->first.name, name) == 0) {
			tempList->prevDisease = (*iter)->first.diseases;
			(*iter)->first.diseases = tempList;
			(*iter)->first.diseasesNr++;
			return;
		}
		iter = &((*iter)->next);
	}
	*iter = (PatientList*) malloc(sizeof(PatientList));
	Patient tempPat;
	tempPat.name = (char*) malloc(sizeof(char) * strlen(name));
	strcpy(tempPat.name, name);
	tempPat.diseasesNr = 1;
	tempList->prevDisease = NULL;
	tempPat.diseases = tempList;
	(*iter)->first = tempPat;
	(*iter)->next = NULL;
	printf("OK\n");
	return;
}

void printDesc(char *name, int n) {
	PatientList *iter = patients;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name) == 0) {
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
	PatientList *iter = patients;
	Patient *pat1, *pat2;
	Disease *temp;
	DiseaseList *tempList;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name1) == 0) {
			pat1 = &(iter->first);
		} else if (strcmp(iter->first.name, name2) == 0) {
			pat2 = &(iter->first);
		}
		iter = iter->next;
	}
	if (pat1 == NULL || pat2 == NULL) {
		printf("IGNORED\n");
		return;
	} else if (pat2->diseases == NULL) {
		printf("IGNORED\n");
		return;
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

void changeDesc(char *name, int n, char *diseaseDesc) {
	PatientList *iter = patients;
	Disease *temp;
	DiseaseList *tempList;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name) == 0) {
			if (n > iter->first.diseasesNr) {
				printf("IGNORED\n");
				return;
			}
			diseaseCounter++;
			n = iter->first.diseasesNr - n;
			tempList = iter->first.diseases;
			temp = (Disease *) malloc(sizeof(Disease));
			temp->counter = 1;
			temp->description = (char *) malloc(sizeof(char) * strlen(diseaseDesc));
			strcpy(temp->description, diseaseDesc);
			while(n != 0) {
				tempList = tempList->prevDisease;
				n--;
			}
			tempList->lastDisease->counter--;
			if (tempList->lastDisease->counter == 0) {
				diseaseCounter--;
				freeDisease(tempList->lastDisease);
			}
			tempList->lastDisease = temp;
			return;
		}
		iter = iter->next;
	}
	if (temp == NULL)
		printf("IGNORED\n");
	return;
}

void deletePatientData(char *name) {
	return;
}

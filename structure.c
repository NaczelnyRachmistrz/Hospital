#include "structure.h"

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

PatientList *patients = NULL;

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

void newDisease(char *name, char *diseaseDesc) {
	PatientList *iter = patients;
	Disease *temp = (Disease*) malloc(sizeof(Disease));
	DiseaseList *tempList = (DiseaseList*) malloc(sizeof(DiseaseList));
	temp->counter = 1;
	temp->description = (char*) malloc(sizeof(char) * strlen(diseaseDesc));
	strcpy(temp->description, diseaseDesc);
	tempList->lastDisease = temp;
	while(iter != NULL) {
		if (strcmp(iter->first.name, name) == 0) {
			tempList->prevDisease = iter->first.diseases;
			iter->first.diseases = tempList;
			iter->first.diseasesNr++;
			return;
		}
		iter = iter->next;
	}
	iter = (PatientList*) malloc(sizeof(PatientList));
	Patient tempPat;
	tempPat.name = (char*) malloc(sizeof(char) * strlen(name));
	strcpy(tempPat.name, name);
	tempPat.diseasesNr = 1;
	tempList->prevDisease = NULL;
	tempPat.diseases = tempList;
	iter->first = tempPat;
	iter->next = NULL;
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
			DiseaseList *temp = iter->first.diseases;
			while(n != 0) {
				temp = temp->prevDisease;
				n--;
			}
			printf("%s\n", temp->lastDisease->description);
			return;
		}
		iter = iter->next;		
	}
	printf("IGNORED\n");
	return;
}

void copyDisease(char *name1, char *name2) {
	return;
	};

void changeDesc(char *name, int n, char *diseaseDesc) {
	return;
	};

void deletePatientData(char *name) {
	return;
}

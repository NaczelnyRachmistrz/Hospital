#include "structure.h"
#include "parse.h"

void freeInput(InputData *a) {
	if (a->name1 != NULL) {
		free(a->name1);
		a->name1 = NULL;
	}
	if (a->name2 != NULL) {
		free(a->name2);
		a->name2 = NULL;
	}
	if (a->diseaseDesc != NULL) {
		free(a->diseaseDesc);
		a->diseaseDesc = NULL;
	}
	free(a);
	return;
}

bool flag = 0;

int main(int argc, char **argv) {
	if (argc >= 3) {
		printf("ERROR\n");
		return 1;
	} else if (argc == 2) {
		if (strcmp("-v", argv[1]) != 0) {
			printf("ERROR\n");
			return 1;
		}
		flag = 1;
	}
	while(1) {
		InputData *cos = readData();
	//	printf("%d %d %s %s %s\n", cos->inputType, cos->nr, cos->name1, cos->name2, cos->diseaseDesc);
		if (cos == NULL)
			break;
		switch((int) cos->inputType) {
			case NEW_DISEASE:
 				newDisease(cos->name1, cos->diseaseDesc);
 				break;
			case COPY_DISEASE:
				copyDisease(cos->name1, cos->name2);
				break;
			case DESC_CHANGE:
				changeDesc(cos->name1, cos->nr, cos->diseaseDesc);
				break;
			case DESC_PRINT:
				printDesc(cos->name1, cos->nr);
				break;
			case DEL_PATIENT_DATA:
				deletePatientData(cos->name1);
				break;
		}
		//printf("%d %d %s %s %s\n", cos->inputType, cos->nr, cos->name1, cos->name2, cos->diseaseDesc);
		freeInput(cos);
		if (flag) {
			fprintf(stderr, "DESCRIPTIONS: %d\n", diseasesNumber());
		}
	}
	freeAll();
	return 0;
}

#include "structure.h"
#include "parse.h"

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
		InputData cos = readData();
		if (cos.inputType == END_OF_INPUT) {
			break;
		}
		
		switch((int) cos.inputType) {
			case NEW_DISEASE:
 				newDisease(cos.name1, cos.diseaseDesc);
 				free(cos.diseaseDesc);
 				break;
			case COPY_DISEASE:
				copyDisease(cos.name1, cos.name2);
				free(cos.name2);
				break;
			case DESC_CHANGE:
				changeDesc(cos.name1, cos.nr, cos.diseaseDesc);
				free(cos.diseaseDesc);
				break;
			case DESC_PRINT:
				printDesc(cos.name1, cos.nr);
				break;
			case DEL_PATIENT_DATA:
				deletePatientData(cos.name1);
				break;
		}
		free(cos.name1);
		if (flag) {
			fprintf(stderr, "DESCRIPTIONS: %d\n", diseasesNumber());
		}
	}
	freeAll();
	return 0;
}

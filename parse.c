#include "parse.h"

static void ignoreSpace() {
	char a;
	scanf("%c", &a);
	return;
}

InputData readData() {
	char *operationType, *name1, *disease, *name2;
	int n;
	InputData ret = {0,NULL,NULL,NULL,0};
	operationType = (char*) malloc(sizeof(char) * 40);
	
	if (scanf("%s", operationType) == EOF) {
		free(operationType);
		ret.inputType = END_OF_INPUT;
		return ret;
	}
	
	name1 = (char*) malloc(sizeof(char) * MAX_LINE);
	scanf("%s", name1);
	ret.name1 = name1;
	
	if (strcmp(operationType, "NEW_DISEASE_ENTER_DESCRIPTION") == 0) {
		ret.inputType = NEW_DISEASE;
		disease = (char*) malloc(sizeof(char) * MAX_LINE);
		ignoreSpace();
		scanf ("%[^\n]%*c", disease);
		ret.diseaseDesc = disease;
	} else if (strcmp(operationType, "NEW_DISEASE_COPY_DESCRIPTION") == 0) {
		ret.inputType = COPY_DISEASE;
		name2 = (char*) malloc(sizeof(char) * MAX_LINE);
		scanf("%s", name2);
		ret.name2 = name2;
	} else if (strcmp(operationType, "CHANGE_DESCRIPTION") == 0) {
		ret.inputType = DESC_CHANGE;
		disease = (char*) malloc(sizeof(char) * MAX_LINE);
		scanf("%d", &n);
		ignoreSpace();
		scanf("%[^\n]%*c", disease);
		ret.nr = n;		
		ret.diseaseDesc = disease;
	} else if (strcmp(operationType, "PRINT_DESCRIPTION") == 0) {
		ret.inputType = DESC_PRINT;
		scanf("%d", &n);
		ret.nr = n;
	} else if (strcmp(operationType, "DELETE_PATIENT_DATA") == 0) {
		ret.inputType = DEL_PATIENT_DATA;
	}
	
	free(operationType);
	return ret;
}

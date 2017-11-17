#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define CHECK_GENERATED_DATA

//#define N_ELEMENTS 1048576	// 2^20
//#define N_ELEMENTS 1024		// 2^10
#define N_ELEMENTS 32		// 2^5

#define FILE_NAME_PREFIX  "ENTIRELY_RANDOM"

typedef struct {
	unsigned int key; float score; double other; char name[16];
} ELEMENT;
#define ELEMENT_KEY(x) ((x)->key)

void main() {
	unsigned scale_factor_uint = UINT_MAX >> 2;
	float scale_factor_flt = 90.0f;

	int n;
	char file_name[32];
	FILE *fp;

	ELEMENT element;

	n = N_ELEMENTS; // n is the number of data elements to be written
	sprintf(file_name, "%s_%d.binary", FILE_NAME_PREFIX, n);

	fprintf(stdout, "^^^ UNIT_MAX = %u\n", UINT_MAX);
	fprintf(stdout, "^^^ RAND_MAX = %u\n\n", RAND_MAX);

	if ((fp = fopen(file_name, "wb")) == NULL) {
		fprintf(stderr, "Error: cannot open the binary file %s for writing...\n", file_name);
		exit(-1);
	}

	fwrite(&n, sizeof(int), 1, fp);
	srand((int)time(NULL));

	for (int i = 0; i < n; i++) {
		//
		// For more efficient read/write operations, use a buffer of proper size!!!
		//
		element.key = (unsigned int)((((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) *
			(((float)rand()) / RAND_MAX) * (float)scale_factor_uint);
		element.score = ((float)rand()) / RAND_MAX * scale_factor_flt + 10.0f;
		element.other = 3.141592653589793; // dummy value
		strcpy(element.name, "abcdefghijklmno");  // dummy value

		fwrite(&element, sizeof(ELEMENT), 1, fp);
	}
	fclose(fp);

#ifdef CHECK_GENERATED_DATA
	if ((fp = fopen(file_name, "rb")) == NULL) {
		fprintf(stderr, "Error: can not open the binary file %s for reading...\n", file_name);
		exit(-1);
	}
	fread(&n, sizeof(int), 1, fp);
	fprintf(stdout, "*** Number of elements = %d\n", n);

	for (int i = 0; i < n; i++) {
		fread(&element, sizeof(ELEMENT), 1, fp);
		fprintf(stdout, "  i = %6d: (%11u, %5.1f, %17.14f, %s)\n", i, ELEMENT_KEY(&element), element.score, element.other, element.name);
	}
	fclose(fp);
#endif
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#pragma warning(disable: 4996)
//#define CHECK_GENERATED_DATA

//#define debug
//#define N_ELEMENTS 1048576	// 2^20
//#define N_ELEMENTS 262144		// 2^18
//#define N_ELEMENTS 65536		// 2^16
//#define N_ELEMENTS 16384		// 2^14
//#define N_ELEMENTS 4096		// 2^12
//#define N_ELEMENTS 1024		// 2^10

#define N_ELEMENTS 256// 2^5
//1024, 4096, 16384, 65536, 262144, 1048576,
//#define FEW_SWAP
#define ENT
//#define DESCENDING


#define FILE_NAME_PREFIX  "ENTIRELY_RANDOM"
//#define FILE_NAME_PREFIX  "DESCENDING"
//#define FILE_NAME_PREFIX  "FEW_SWAP"
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
	
	if ((fp = fopen(file_name, "wb")) == NULL ) {
		fprintf(stderr, "Error: cannot open the binary file %s for writing...\n", file_name);
		exit(-1);
	}

	fwrite(&n, sizeof(int), 1, fp);
	srand((int)time(NULL));


	for (int i = 0; i < n; i++) {
		//
		// For more efficient read/write operations, use a buffer of proper size!!!
		//

#ifdef FEW_SWAP
		element.key = (unsigned int)(i);
#endif // FEW_SWAP
#ifdef ENT
		element.key = (unsigned int)((((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) *
			(((float)rand()) / RAND_MAX) * (float)scale_factor_uint);
#endif // ENT
#ifdef DESCENDING
		element.key = (unsigned int)(n-1-i);
#endif // DESCENDING



		element.score = ((float)rand()) / RAND_MAX * scale_factor_flt + 10.0f;
		element.other = 3.141592653589793; // dummy value
		strcpy(element.name, "abcdefghijklmno");  // dummy value
		fwrite(&element, sizeof(ELEMENT), 1, fp);
	}
	fclose(fp);

#ifdef FEW_SWAP
	FILE *fp2;
	fp = fopen(file_name, "r+b");
	if ((fp2 = fopen(file_name, "r+b")) == NULL) {
		fprintf(stderr, "Error: cannot open the binary file %s for writing...\n", file_name);
		exit(-1);
	}


	int t = (int)sqrt(n);
	for (int i = 0; i < t; i++) {
		unsigned int iter = (unsigned int)rand() % (N_ELEMENTS - t);
		unsigned int iter2 = iter+ (unsigned int)rand() % (t);
		ELEMENT temp1, temp2;
		fseek(fp, sizeof(int) + iter * sizeof(ELEMENT), SEEK_SET);
		fseek(fp2, sizeof(int) + iter2 * sizeof(ELEMENT), SEEK_SET);
		fread(&temp1, sizeof(ELEMENT), 1, fp);
		fread(&temp2, sizeof(ELEMENT), 1, fp2);
		fseek(fp, sizeof(int)+iter * sizeof(ELEMENT), SEEK_SET);
		fseek(fp2, sizeof(int) + iter2 * sizeof(ELEMENT), SEEK_SET);
		fwrite(&temp2, sizeof(ELEMENT), 1, fp);
		fwrite(&temp1, sizeof(ELEMENT), 1, fp2);
#ifdef debug
		fseek(fp, sizeof(int) + iter * sizeof(ELEMENT), SEEK_SET);
		fseek(fp2, sizeof(int) + iter2 * sizeof(ELEMENT), SEEK_SET);
		fread(&temp1, sizeof(ELEMENT), 1, fp);
		fread(&temp2, sizeof(ELEMENT), 1, fp2);
		fseek(fp, sizeof(int) + iter * sizeof(ELEMENT), SEEK_SET);
		fseek(fp2, sizeof(int) + iter2 * sizeof(ELEMENT), SEEK_SET);
#endif
	}
	fclose(fp2);
#endif // FEW_SWAP


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
#include "my_types.h"
#include <stdlib.h>

int keys_compare(const void *a, const void *b) {
	ELEMENT *rec_a, *rec_b;
	if ( ((ELEMENT*)a)->key > ((ELEMENT*)a)->key )
		return 1;
	else if (((ELEMENT*)a)->key < ((ELEMENT*)a)->key)
		return -1;
	else
		return 0;
}

int QSORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise

	qsort(data + left, right-left+1, sizeof(ELEMENT), keys_compare);
	return 1;
}
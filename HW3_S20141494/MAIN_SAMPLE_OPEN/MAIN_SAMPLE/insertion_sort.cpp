#include <stdio.h>
#include <string.h>
#include "my_types.h"

int INSERTION_SORT(ELEMENT data[], int left, int right) {
	int i, j,size=0;
	ELEMENT temp;
	if (data == NULL||left<0)return 0;

	for (i = left+1; i <= right ; i++)
	{
		temp = data[i];
		for (j = i - 1,size=0; data[j].key > data[i].key && j >= left; j--, size++);
		memcpy(&data[j + 2], &data[j + 1],sizeof(ELEMENT)* size);
		memcpy(&data[j + 1], &temp, sizeof(ELEMENT));
	}

	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	return 1;
}
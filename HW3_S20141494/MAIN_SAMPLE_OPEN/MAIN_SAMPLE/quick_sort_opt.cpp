#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_types.h"
#define ELEMENT_SWAP(a,b) {ELEMENT temp;memcpy(&temp,&a,sizeof(ELEMENT));memcpy(&a,&b,sizeof(ELEMENT));memcpy(&b,&temp,sizeof(ELEMENT));}
#define MIN(a,b) (((a)<(b))?(a):(b))
inline int pivot_select(ELEMENT*, int, int);

int pivot_select(ELEMENT *data, int left, int right) {
	return MIN(data[left].key, data[(left + right) / 2].key) ^ MIN(data[(left + right) / 2].key, data[right].key) ^ MIN(data[left].key, data[right].key);

}
int QUICK_SORT_OPT(ELEMENT data[], int left, int right) {


	if (right - left + 1 < 50) {
		INSERTION_SORT(data, left, right);
		return 1;
	}
	int i = left, j = right;
	ELEMENT temp;
	int pivot = pivot_select(data, left, right);


	while (i <= j) {
		while (data[j].key > pivot)
			j--;
		while (data[i].key < pivot)
			i++;
		if (i <= j) {
			ELEMENT_SWAP(data[i], data[j]);
			i++;
			j--;
		}
	};

	if (left < j)
		QUICK_SORT_OPT(data, left, j);
	if (i < right)
		QUICK_SORT_OPT(data, i, right);
	return 1;

}
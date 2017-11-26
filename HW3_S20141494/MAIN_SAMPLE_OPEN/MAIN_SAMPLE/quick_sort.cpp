#include <stdio.h>
#include <math.h>
#include "my_types.h"
#define ELEMENT_SWAP(a,b) {ELEMENT temp;temp=a;a=b;b=temp;}
#define MIN(a,b) (((a)<(b))?(a):(b))
inline int pivot_select(ELEMENT*,int,int);

int pivot_select(ELEMENT *data, int left, int right) {
	return MIN(data[left].key, data[(left + right) / 2].key) ^ MIN(data[(left + right) / 2].key, data[right].key) ^ MIN(data[left].key, data[right].key);
}


int QUICK_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	int i = left, j = right;
	ELEMENT temp;
	int pivot = pivot_select(data,left,right);

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
		QUICK_SORT(data, left, j);
	if (i < right)
		QUICK_SORT(data, i, right);
	return 1;
}


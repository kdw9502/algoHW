#include <stdio.h>
#include <algorithm>
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
	int size = right - left + 1,pivot;
	ELEMENT temp;
	int i, j;
	pivot = pivot_select(data, left, right);
	if (left > right) return 0;
	for (i=left, j=right; i<j; )
	{
		for (; data[i].key <= pivot; i++);
		for (; data[j].key > pivot; j--);
		if (i < j)ELEMENT_SWAP(data[i],data[j]);
	}
	
	ELEMENT_SWAP(data[left], data[j]);
	QUICK_SORT(data,left,j-1);
	QUICK_SORT(data, j+1, right);
	return 1;
}
#include <stdio.h>

#include "my_types.h"
#define ELEMENT_SWAP(a,b) {ELEMENT temp;temp=a;a=b;b=temp;}
void heapify(ELEMENT data[], int left,int right, int i)
{
	int size = right - left + 1;

	int left_child = left+ 2 * i + 1; 
	int right_child =left+ 2 * i + 2;  
	int max =left+ i;
	if (left_child <=right && data[left_child].key > data[max].key)
		max = left_child;
	if (right_child <=right && data[right_child].key > data[max].key)
		max = right_child;

	if (max != left+i)
	{
		ELEMENT_SWAP(data[left+i], data[left+max]);
		heapify(data, left,right, max);
	}
}


int HEAP_SORT(ELEMENT data[], int left, int right) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;
	int size = right - left + 1,i;

	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(data, left,right, i);

	for (int i = right; i >= left; i--)
	{
		ELEMENT_SWAP(data[left], data[i]);
		heapify(data, left,right, 0);
	}
	return 1;
}

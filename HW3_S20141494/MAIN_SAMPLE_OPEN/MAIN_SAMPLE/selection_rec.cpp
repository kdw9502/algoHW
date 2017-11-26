#include <stdio.h>
#include <stdlib.h>
#include "my_types.h"
#include <Math.h>
#include <string.h>
int find_index(ELEMENT data[], int left, int right, unsigned int value) {
	
	int i;
	for (i = left; i <=right; i++) {
		if (data[i].key == value) return i;
	}
	return -1;

}

int copy_sort(ELEMENT data[], int left, int right, int k, int *index) {
	ELEMENT* copy;
	int size = (right-left + 1);
	copy = (ELEMENT*)malloc(sizeof(ELEMENT)*size);
	memcpy(copy, &data[left], sizeof(ELEMENT)*size);
	INSERTION_SORT(copy, 0, right-left);
	*index = find_index(data, left, right, copy[k-1].key);
	if (*index<0) return 0;
	return 1;
}

int SELECTION_REC(ELEMENT data[], int left, int right, int k, int *index) {
	// must return 1 if the function finishes normally or return 0 otherwise
	//	return 0;

	int size = right - left + 1;
	int i;
	int median_index;
	ELEMENT* copy;
	ELEMENT* subsetS1;
	ELEMENT* subsetS2;
	ELEMENT* subsetS3;
	ELEMENT* subsetM;
	if (size < 50) {
		copy_sort(data, left, right, k,index);

		return 1;
	}
	copy = (ELEMENT*)malloc(sizeof(ELEMENT)*size);
	subsetS1 = (ELEMENT*)malloc(sizeof(ELEMENT)*size);
	subsetS2 = (ELEMENT*)malloc(sizeof(ELEMENT)*size);
	subsetS3 = (ELEMENT*)malloc(sizeof(ELEMENT)*size);
	subsetM= (ELEMENT*)malloc(sizeof(ELEMENT)*(size/5));
	int sizeS1 = 0, sizeS2 = 0, sizeS3 = 0,sizeM=0;
	int indexS1, indexS2, indexS3,indexM;
	memcpy(copy, &data[left], sizeof(ELEMENT)*size);
	sizeM = size / 5;
	for (i = 0; i < size/5 ; i++)
	{
		INSERTION_SORT(copy, left + 5 * i, left + 5 * i+4);
		memcpy(&subsetM[i],&copy[5 * i + 2],sizeof(ELEMENT));
	}
	INSERTION_SORT(copy, left + 5 * i, right);
	
	SELECTION_REC(subsetM,0,size/5-1,ceil(sizeM/2.0),&indexM);
	median_index = find_index(data,left,right,subsetM[indexM].key);

	for (i = left; i <= right; i++) {
		if (data[median_index].key > data[i].key)memcpy(&subsetS1[sizeS1++], &data[i], sizeof(ELEMENT));
		else if(data[median_index].key == data[i].key)memcpy(&subsetS2[sizeS2++], &data[i], sizeof(ELEMENT));
		else memcpy(&subsetS3[sizeS3++], &data[i], sizeof(ELEMENT));
	}

	if (sizeS1 >= k) {
		SELECTION_REC(subsetS1, 0, sizeS1 - 1, k, &indexS1);
		*index=find_index(data, left, right, subsetS1[indexS1].key);
	}
	else if (sizeS1 + sizeS2 >= k) *index = find_index(data,left,right,data[median_index].key);
	else {
		SELECTION_REC(subsetS3, 0, sizeS3 - 1, k - sizeS1 - sizeS2, &indexS3);
		*index = find_index(data, left, right, subsetS3[indexS3].key);
	}
	
	free(copy);
	free(subsetS1); free(subsetS2); free(subsetS3),free(subsetM);
	

	if (index < 0 || right<*index||*index<left)return 0;
	return 1;
}

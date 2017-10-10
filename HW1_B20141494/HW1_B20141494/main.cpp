#include "main.h"

void merge_sort(item_type *A, int left, int right) {
	int middle;
	if (left < right) {
		middle = (left + right) / 2;
		merge_sort(A, left, middle);
		merge_sort(A, middle + 1, right);
		merge(A, left, middle, right);
	}
}

void merge(item_type *A, int left, int middle, int right) {

	int i, i_left, i_right;
	memcpy(buffer + left, A + left, sizeof(item_type)*(right - left + 1));
	i_left = left;
	i_right = middle + 1;
	i = left;
	while ((i_left <= middle) && (i_right <= right)) {
		if (buffer[i_left] < buffer[i_right])
			A[i++] = buffer[i_left++];
		else {
			A[i++] = buffer[i_right++];
			count += middle - i_left + 1;
		}
	}
	while (i_left <= middle)
		A[i++] = buffer[i_left++];
	while (i_right <= right)
		A[i++] = buffer[i_right++];
}


int main() {
	FILE* config = fopen("Data_B/HW1_IC_config.txt", "rb");
	int data[NSIZE_MAX] = { 0 }, nsize;
	char in_string[NAME_LENGTH_MAX], out_string[NAME_LENGTH_MAX], algo_string[NAME_LENGTH_MAX], temp[NAME_LENGTH_MAX];
	FILE *in_file, *out_file;

	while (fscanf(config, "%s %s", &in_string, &out_string) == 2) {
		strcat(strcpy(temp, "Data_B/"), in_string); //temp="Data_b/filename" 
		in_file = fopen(temp, "rb");
		/*
		// fseek,ftell로 n의 사이즈를 구한다. 그후 fread로 data입력
		fseek(in_file, 0, SEEK_END);
		nsize = ftell(in_file) / DATA_BYTE;
		rewind(in_file);
		*/
		fread(&nsize, DATA_BYTE, 1, in_file);
		fread(data, DATA_BYTE, nsize, in_file);
		buffer = (item_type*)malloc(sizeof(item_type)*nsize);
		merge_sort(data, 0, nsize - 1);

		strcat(strcpy(temp, "Data_B/"), out_string); //temp="Data_b/filename" 
		out_file = fopen(temp, "w");
		fprintf(out_file, "%d\n%d", nsize, count);
		count = 0;
		fclose(out_file);
	}
	fclose(config);
}

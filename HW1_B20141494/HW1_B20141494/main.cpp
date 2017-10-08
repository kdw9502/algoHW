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
item_type *buffer;
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
			count += middle - i_left+1;
		}
	}
	while (i_left <= middle)
		A[i++] = buffer[i_left++];
	while (i_right <= right)
		A[i++] = buffer[i_right++];
}

int count = 0;
int main() {
	FILE* config = fopen("../Data_A/HW1_MSS_config.txt", "r");
	int data[NSIZE_MAX] = {0}, nsize;
	char in_string[NAME_LENGTH_MAX], out_string[NAME_LENGTH_MAX], algo_string[NAME_LENGTH_MAX], temp[NAME_LENGTH_MAX];
	FILE *in_file, *out_file;

	while (!fscanf(config, "%s %s %s", &in_string, &out_string, &algo_string)) {
		strcat(strcpy(temp, "../Data_a/"), in_string); //temp="../Data_a/filename" 
		in_file = fopen(temp, "rb");

		/* fseek,ftell로 n의 사이즈를 구한다. 그후 fread로 data입력 */
		fseek(in_file, 0, SEEK_END);
		nsize = ftell(in_file) / DATA_BYTE;
		rewind(in_file);
		fread(data, DATA_BYTE, nsize, in_file);

		merge_sort(data, 0, nsize - 1);

		strcat(strcpy(temp, "../Data_a/"), out_string); //temp="../Data_a/filename" 
		out_file = fopen(temp, "w");
		fprintf(out_file,"%d\n%d",nsize,count);
		count = 0;
	}
}
#include "main.h"

/*스트링을 enum 값으로*/
algotype str2type(char* in) {
	if (IS_SAME(in, "A1"))return A1;
	else if (IS_SAME(in, "A2")) return A2;
	else if (IS_SAME(in, "A3")) return A3;
}
/*시행*/
struct result_set execute(algotype type, int *data, int nsize) {
	if (type == A1) return exeA1(data, nsize);
	if (type == A2) return exeA2(data, nsize);
	if (type == A3) return exeA3(data, nsize);
}
/*알고리즘 A1*/
struct result_set exeA1(int *data, int nsize)
{
	chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	struct result_set result;
	result.start = -1;
	result.end = -1;
	int ThisSum, MaxSum, i, j;
	MaxSum = 0;
	for (i = 0; i < nsize; i++)
	{
		ThisSum = 0;
		for (j = i; j < nsize; j++)
		{
			ThisSum += data[j];
			if (ThisSum > MaxSum) {
				MaxSum = ThisSum;
				result.start = i;
				result.end = j;
			}
		}
	}
	result.sum = MaxSum;
	chrono::duration<double> sec = chrono::system_clock::now() - clock_start;
	result.time = sec.count();
	return result;
}
/*알고리즘 A2*/
struct result_set exeA2(int *data, int nsize)
{
	chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	struct result_set result;
	result = nlognMaxSum(data, 0, nsize - 1);

	chrono::duration<double> sec = chrono::system_clock::now() - clock_start;
	result.time = sec.count();
	return result;
}
struct result_set nlognMaxSum(int *data, int left, int right) {
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int middle, i, MaxSum;
	struct result_set result, left_result, right_result;
	if (left == right)
		if (data[left] > 0) {
			result.sum = data[left];
			result.start = result.end = left;
			return result;
		}
		else {
			result.sum = 0;
			result.start = result.end = -1;
			return result;
		}
		middle = (left + right) / 2;
		left_result = nlognMaxSum(data, left, middle);
		right_result = nlognMaxSum(data, middle + 1, right);
		MaxLeftSum = left_result.sum;
		MaxRightSum = right_result.sum;

		MaxLeftBorderSum = 0; LeftBorderSum = 0;
		for (i = middle; i >= left; i--)
		{
			LeftBorderSum += data[i];
			if (LeftBorderSum > MaxLeftBorderSum) {
				MaxLeftBorderSum = LeftBorderSum;
				result.start = i;
			}
		}
		MaxRightBorderSum = 0; RightBorderSum = 0;
		for (i = middle + 1; i <= right; i++)
		{
			RightBorderSum += data[i];
			if (RightBorderSum > MaxRightBorderSum) {
				MaxRightBorderSum = RightBorderSum;
				result.end = i;
			}
		}
		MaxSum = max(max(MaxLeftSum, MaxRightSum), MaxLeftBorderSum + MaxRightBorderSum);
		if (MaxSum == MaxLeftSum)
			result = left_result;
		else if (MaxSum == MaxRightSum)
			result = right_result;
		else {
			result.sum = MaxLeftBorderSum + MaxRightBorderSum;
		}
		return result;
}
/*알고리즘 A3*/
struct result_set exeA3(int *data, int nsize)
{
	struct result_set result;
	int ThisSum, MaxSum, j, left=-1;
	ThisSum = MaxSum = 0;
	chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	for (j = 0; j < nsize; j++)
	{
		ThisSum += data[j];
		if (ThisSum > MaxSum) {
			MaxSum = ThisSum;
			result.start = left;
			result.end = j;
		}
		else if (ThisSum < 0) {
			ThisSum = 0;
			left = j + 1;

		}
	}
	chrono::duration<double> sec = chrono::system_clock::now() - clock_start;
	result.time = sec.count();
	result.sum = MaxSum;
	if (MaxSum == 0)result.start = result.end = -1;
	return result;
}

int main() {
	FILE* config = fopen("Data_A/HW1_MSS_config.txt", "r");
	int data[NSIZE_MAX] = {0}, nsize;
	char in_string[NAME_LENGTH_MAX], out_string[NAME_LENGTH_MAX], algo_string[NAME_LENGTH_MAX], temp[NAME_LENGTH_MAX];
	FILE *in_file, *out_file;
	algotype type;
	while (fscanf(config, "%s %s %s", &in_string, &out_string, &algo_string)==3) {
		strcat(strcpy(temp, "Data_a/"), in_string); //temp="../Data_a/filename" 
		in_file = fopen(temp, "rb");
		type = str2type(algo_string);
		/* fseek,ftell로 n의 사이즈를 구한다. 그후 fread로 data입력 */
		fseek(in_file, 0, SEEK_END);
		nsize = ftell(in_file) / DATA_BYTE;
		rewind(in_file);
		fread(data, DATA_BYTE, nsize, in_file);

		result_set result = execute(type, data, nsize);
		strcat(strcpy(temp, "Data_a/"), out_string); //temp="../Data_a/filename" 
		out_file = fopen(temp, "w");
		fprintf(out_file, "%d\n%d\n%d\n%d %d\n%.5f", nsize, type, result.sum, result.start, result.end, result.time);
		fclose(out_file);
	}
	fclose(config);
}
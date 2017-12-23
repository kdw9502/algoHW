#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#define MAX(a,b) {(a>b)?a:b}
#define MIN(a,b) {(a>b)?b:a}
#define P1
#define P2
#define P3

#ifdef P1
void problem1(int len, char* string, FILE* fp_w){
	int **mat;
	int i, sl, j, len_lps;
	mat = (int**)malloc(sizeof(int*)*(len));
	for (i = 0; i < len; i++)mat[i] = (int*)malloc(sizeof(int)*(len));

	for (i = 0; i < len; i++)mat[i][i] = 1;



	for (sl = 2; sl <= len; sl++)
	{
		for (i = 0; i<len - sl + 1; i++)
		{
			j = i + sl - 1;
			if (string[i] == string[j] && sl == 2)
				mat[i][j] = 2;
			else if (string[i] == string[j])
				mat[i][j] = mat[i + 1][j - 1] + 2;
			else
				mat[i][j] = MAX(mat[i][j - 1], mat[i + 1][j]);
		}
	}

	for(i=0;i<len;i++)
		for(j=0;j<len;j++)mat[j][i]=mat[i][j];
	fprintf(fp_w,"%d\n",len_lps=mat[0][len-1]);
	char *lps = new char[len_lps + 1];
	lps[len_lps] = 0;
	for (i = 0,j=len-1; i<len&&j>0;) {
		if (string[i] == string[j])
		{
			lps[len_lps - 1] = string[i];
			i++;
			j--;
			len_lps--;
		}
		else if (mat[i][j-1]<mat[i+1][j])
			i++;
		else
			j--;
	}
	fprintf(fp_w, "%s\n", lps);



}
#endif
#ifdef P2
void problem2(int len, char* string, FILE* fp_w) {
	int **mat, ***record;
	int i, sl, j, len_lps;
	mat = (int**)malloc(sizeof(int*)*(len));
	for (i = 0; i < len; i++)mat[i] = (int*)malloc(sizeof(int)*(len));

	for (i = 0; i < len; i++)mat[i][i] = 1;



	for (sl = 2; sl <= len; sl++)
	{
		for (i = 0; i<len - sl + 1; i++)
		{
			j = i + sl - 1;
			if (string[i] == string[j] && sl == 2)
				mat[i][j] = 2;
			else if (string[i] == string[j])
				mat[i][j] = mat[i + 1][j - 1] + 2;
			else
				mat[i][j] = MAX(mat[i][j - 1], mat[i + 1][j]);
		}
	}

	for (i = 0; i<len; i++)
		for (j = 0; j<len; j++)mat[j][i] = mat[i][j];
	fprintf(fp_w, "%d\n", len_lps = mat[0][len - 1]);
	char *lps = new char[len_lps + 1];
	lps[len_lps] = 0;
	for (i = 0, j = len - 1; i<len&&j>0;) {
		if (string[i] == string[j])
		{
			lps[len_lps - 1] = string[i];
			i++;
			j--;
			len_lps--;
		}
		else if (mat[i][j - 1]<mat[i + 1][j])
			i++;
		else
			j--;
	}
	fprintf(fp_w, "%s\n", lps);



}
#endif


int main() {
	_mkdir("20141494_OUTPUT");
#ifdef P1
	FILE *fp_r=fopen("input-3-1.txt", "r");
	FILE *fp_w=fopen("20141494_OUTPUT/output-3-1.txt", "w");
	int N;
	fscanf(fp_r,"%d", &N);
	fprintf(fp_w, "%d\n", N);
	for (int i = 0; i < N; i++)
	{
		int len;		
		fscanf(fp_r,"%d",&len);
		char *string = new char[len];
		fscanf(fp_r,"%s",string);
		problem1(len,string,fp_w);
	}
	fclose(fp_r);fclose(fp_w);
#endif

#ifdef P2
	FILE *fp_r = fopen("input-3-2.txt", "r");
	FILE *fp_w = fopen("20141494_OUTPUT/output-3-2.txt", "w");
	int N;
	fscanf(fp_r, "%d", &N);
	fprintf(fp_w, "%d\n", N);
	for (int i = 0; i < N; i++)
	{
		int len;
		fscanf(fp_r, "%d", &len);
		char *string = new char[len];
		fscanf(fp_r, "%s", string);
		problem2(len, string, fp_w);
	}
	fclose(fp_r); fclose(fp_w);
#endif


}
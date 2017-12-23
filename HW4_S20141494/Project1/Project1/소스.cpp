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



	for (sl = 2; sl <= len; sl++)//sl =substring len
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
	int **mat;
	int **pal;
	int i, sl, j, k;
	mat = (int**)malloc(sizeof(int*)*(len)); //minimum cut i to j matrix
	for (i = 0; i < len; i++)mat[i] = (int*)malloc(sizeof(int)*(len));
	for (i = 0; i < len; i++)mat[i][i] = 0;
	pal = (int**)malloc(sizeof(int*)*(len));
	for (i = 0; i < len; i++)pal[i] = (int*)malloc(sizeof(int)*(len));
	for (i = 0; i < len; i++)pal[i][i] = 1;
	int mincut;
	for (sl = 2; sl <= len; sl++) //sl = substring lenth
	{

		for (i = 0; i<len - sl + 1; i++) // i+sl<len+1
		{
			j = i + sl - 1; //end of string index
			if (sl == 2) {
				(string[i] == string[j]) ? pal[i][j] = 1 : pal[i][j] = 0;
			}
			else
				((string[i] == string[j]) && pal[i + 1][j - 1]) ? pal[i][j] = 1 : pal[i][j] = 0;
			mat[i][j] = INT_MAX;
			if (pal[i][j] == 1)
				mat[i][j] = 0;
			else
			{
				for (k = i; k <= j - 1; k++)
					mat[i][j] = MIN(mat[i][j], mat[i][k] + mat[k + 1][j] + 1);
			}
		}
	}
	fprintf(fp_w, "%d\n",  (mincut= mat[0][len - 1])+1);

	for (int i = 0; i < len;) {
		int max = i;

		for (j = i; j < len; j++) {
			if(pal[i][j])
			max = (max < j)?j:max;

		}
		for(int k=i;k<=max;k++)
			fprintf(fp_w, "%c", string[k]);
		fprintf(fp_w, "\n");
		i = max+1;
	}


}
#endif


int main() {
	_mkdir("20141494_OUTPUT");
	FILE *fp_r;
	FILE *fp_w;
	int N;
#ifdef P1
	fp_r=fopen("input-3-1.txt", "r");
	fp_w=fopen("20141494_OUTPUT/output-3-1.txt", "w");

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
	fp_r = fopen("input-3-2.txt", "r");
	fp_w = fopen("20141494_OUTPUT/output-3-2.txt", "w");
	
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
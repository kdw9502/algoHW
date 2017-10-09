#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define NAME_LENGTH_MAX 128
#define NSIZE_MAX 0x1000000
#define DATA_BYTE 4

#define IS_SAME(a,b) (strcmp(a,b)?0:1)
using namespace std;

typedef enum algotype { A0,A1, A2, A3 } algotype;
struct result_set {
	int sum;
	int start, end;
	double time;
};
algotype str2type(char* in);
struct result_set execute(algotype type, int *data, int nsize);
struct result_set exeA1(int *data, int nsize);
struct result_set exeA2(int *data, int nsize);
struct result_set exeA3(int *data, int nsize);
struct result_set nlognMaxSum(int *data, int left, int right);

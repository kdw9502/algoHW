#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define NAME_LENGTH_MAX 128
#define NSIZE_MAX 0x100000
#define DATA_BYTE 4

typedef int item_type;
void merge_sort(item_type *A, int left, int right);
void merge(item_type *A, int left, int middle, int right);
int count = 0;
item_type *buffer;
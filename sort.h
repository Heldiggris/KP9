#ifndef _SORT_H_
#define _SORT_H_
#define STR_SIZE 128


typedef struct _Key
{
    char first[8];
    int second;
} Key;

typedef struct _Row
{
    Key key;
    char str[STR_SIZE];
} Row;

void printTable(Row *arr, int size);
int binSearch(Row *arr, int size, Key *key);
void sort(Row *arr, int size);
void scramble(Row *arr, int size);
void reverse(Row *arr, int size);

void getRow(FILE *stream, char *str, int size);
void swapRows(Row *r1, Row *r2);
int comparator(Key *k1, Key *k2);
int isEqualKeys(Key *k1, Key *k2);
int randomAB(int a, int b);
int isSorted(Row *a, int size);
#endif
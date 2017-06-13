#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

void printTable(Row *a, int size)
{
    int i;

    printf("+---------+------------------------------------------------+\n");
    printf("|   Ключ  |                    Значение                    |\n");
    printf("+---------+------------------------------------------------+\n");

    for (i = 0; i < size; i++)
        printf("|%4s %4d|%48s|\n", a[i].key.first, a[i].key.second, a[i].str);

    printf("+---------+------------------------------------------------+\n");
}

int binSearch(Row *arr, int size, Key *key)
{
    int start = 0, end = size - 1, mid;

    if (size <= 0)
        return -1;

    while (start < end)
    {
        mid = start + (end - start) / 2;

        if (isEqualKeys(&arr[mid].key, key))
            return mid;
        else if (comparator(&arr[mid].key, key))
            start = mid + 1;
        else
            end = mid;
    }
    
    if (isEqualKeys(&arr[end].key, key))
        return end;

    return -1;
}

void sort(Row *arr, int size)
{
    int i, j, step;
    Row tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = arr[i];
            for (j = i; j >= step; j -= step)
            {
                if (comparator(&tmp.key, &arr[j - step].key)) {
                    arr[j] = arr[j - step];
                }
                else
                    break;
            }
            arr[j] = tmp;
        }
}

void scramble(Row *arr, int size)
{
    int i, j, k;

    srand((unsigned int)time(0));

    for (k = 0; k < size; k++)
    {
        i = randomAB(0, size - 1);
        j = randomAB(0, size - 1);

        swapRows(&arr[i], &arr[j]);
    }
}

void reverse(Row *arr, int size)
{
    int i, j;

    for (i = 0, j = size - 1; i < j; i++, j--)
        swapRows(&arr[i], &arr[j]);
}

void getRow(FILE *stream, char *str, int size)
{
    int cnt = 0, ch;

    while ((ch = getc(stream)) != '\n' && cnt < size - 1)
        str[cnt++] = ch;

    str[cnt] = '\0';
}

void swapRows(Row *r1, Row *r2)
{
    Row tmp;

    tmp = *r1;
    *r1 = *r2;
    *r2 = tmp;
}

int comparator(Key *k1, Key *k2)
{
    if (strcmp(k1->first, k2->first) == 0)
        return k1->second <= k2->second;

    return strcmp(k1->first, k2->first) <= 0;
}

int isEqualKeys(Key *k1, Key *k2)
{
    return strcmp(k1->first, k2->first) == 0 && k1->second == k2->second;
}

int randomAB(int a, int b)
{
    return a + rand() % (b - a + 1);
}

int isSorted(Row *a, int size)
{
    int i;

    for (i = 0; i < size - 1; i++)
        if (!comparator(&a[i].key, &a[i + 1].key))
            return 0;

    return 1;
}
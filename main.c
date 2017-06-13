#include <stdio.h>
#include <string.h>
#include "sort.h"

int main(int argc, char const *argv[])
{
    const int N = 128;
    int i, cnt;
    char ch;
    Row arr[N];
    Key key;

    if (argc != 2) {
        printf("Неверно заданы параметры\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Ошибка при открытии файла\n");
        return 0;
    }

    i = 0;

    while (i < N && fscanf(file, "%s %d", arr[i].key.first, &arr[i].key.second) == 2)
    {
        fscanf(file, "%c", &ch);
        getRow(file, arr[i].str, sizeof(arr[i].str));

        i++;
    }

    fclose(file);

    cnt = i;
    char action[4];
    do
    {
        printf("Меню\n");
        printf("1) Печать\n");
        printf("2) Двоичный поиск\n");
        printf("3) Сортировка\n");
        printf("4) Перемешивание\n");
        printf("5) Реверс\n");
        printf("6) Выход\n");
        printf("Выберите действие\n");
        scanf("%3s", action);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(action, "1")) {
            printTable(arr, cnt);
        } else if (!strcmp(action, "2")) {
            if (!isSorted(arr, cnt))
                printf("Ошибка. Таблица не отсортирована\n");
            else
            {
                printf("Введите ключ: ");
                scanf("%s %d", key.first, &key.second);

                i = binSearch(arr, cnt, &key);

                if (i > -1)
                    printf("Найдена строка: %s\n", arr[i].str);
                else
                    printf("Строка с таким ключом не найдена\n");
            }
        } else if (!strcmp(action, "3")) {
            sort(arr, cnt);
        } else if (!strcmp(action, "4")) {
            scramble(arr, cnt);
        } else if (!strcmp(action, "5")) {
            reverse(arr, cnt);
        } else if (!strcmp(action, "6")) {
            break;
        } else {
            printf("\nТакого пункта нет\n\n");
        }
    } while (1);
    return 0;
}


// Я решил через Quick Sort на С

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100  // Максимальная длина строки

// Функция сравнения для qsort
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Функция для чтения данных из файла
char **read_input(const char *filename, int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d\n", n);  // Читаем количество элементов
    char **arr = (char**)malloc((*n) * sizeof(char*));
    if (!arr) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *n; i++) {
        arr[i] = (char*)malloc(MAX_LEN * sizeof(char));
        if (!arr[i]) {
            perror("Memory allocation failed");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        fgets(arr[i], MAX_LEN, file);
        arr[i][strcspn(arr[i], "\n")] = 0;  // Убираем символ новой строки
    }

    fclose(file);
    return arr;
}

// Функция для записи результата в файл
void write_output(const char *filename, char **arr, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s\n", arr[i]);
    }

    fclose(file);
}

// Главная функция
int main() {
    int n;
    char **arr = read_input("input.txt", &n);

    qsort(arr, n, sizeof(char*), compare_strings);  // Используем qsort для сортировки строк

    write_output("output.txt", arr, n);

    // Освобождаем память
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    // ВОТ ЭТО ИМБА, А НЕ ВЕДРА

    return 0;
}

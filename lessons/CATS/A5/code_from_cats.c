#include <stdio.h>
#include <stdlib.h>

// Структура для хранения задачи
typedef struct {
    int id;       // Номер задачи
    int time;     // Время на решение задачи
} Task;

// Функция для сравнения задач по времени (по убыванию)
int compare_tasks(const void* a, const void* b) {
    Task* task1 = (Task*)a;
    Task* task2 = (Task*)b;
    return task2->time - task1->time;
}

int main() {
    // Открываем входной файл
    FILE* input_file = fopen("c.in", "r");
    if (!input_file) {
        perror("Failed to open input file");
        return 1;
    }

    // Считываем количество задач
    int N;
    fscanf(input_file, "%d", &N);

    // Считываем время для каждой задачи
    Task* tasks = (Task*)malloc(N * sizeof(Task));
    if (!tasks) {
        perror("Failed to allocate memory");
        fclose(input_file);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        tasks[i].id = i + 1; // Нумерация задач начинается с 1
        fscanf(input_file, "%d", &tasks[i].time);
    }

    fclose(input_file);

    // Сортируем задачи по времени (по возрастанию)
    qsort(tasks, N, sizeof(Task), compare_tasks);

    // Открываем выходной файл
    FILE* output_file = fopen("c.out", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(tasks);
        return 1;
    }

    // Выводим номера задач в отсортированном порядке
    for (int i = 0; i < N; i++) {
        fprintf(output_file, "%d", tasks[i].id);
        if (i != N - 1) {
            fprintf(output_file, " ");
        }
    }

    fclose(output_file);
    free(tasks);

    return 0;
}
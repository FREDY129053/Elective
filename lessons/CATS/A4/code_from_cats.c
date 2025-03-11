#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double height;
} Soldier;

long long merge_and_count(Soldier *arr, Soldier *temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long swaps = 0;

    while (i <= mid && j <= right) {
        if (arr[i].height >= arr[j].height) {
            temp[k++] = arr[i++];
        } else {
            swaps += (mid - i + 1);
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) arr[i] = temp[i];

    return swaps;
}

long long merge_sort_and_count(Soldier *arr, Soldier *temp, int left, int right) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    long long swaps = 0;

    swaps += merge_sort_and_count(arr, temp, left, mid);
    swaps += merge_sort_and_count(arr, temp, mid + 1, right);
    swaps += merge_and_count(arr, temp, left, mid, right);

    return swaps;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int n;
    fscanf(file, "%d", &n);
    
    Soldier *arr = malloc(n * sizeof(Soldier));
    Soldier *temp = malloc(n * sizeof(Soldier));
    if (!arr || !temp) {
        perror("Memory allocation error");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        char name[256];
        fscanf(file, "%lf %s", &arr[i].height, name);
    }
    fclose(file);

    long long swaps = merge_sort_and_count(arr, temp, 0, n - 1);

    file = fopen("output.txt", "w");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%lld\n", swaps);
    fclose(file);

    free(arr);
    free(temp);
    
    return 0;
}

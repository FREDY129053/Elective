#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функция быстрой сортировки (Quick Sort)
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[right]; // Опорный элемент (берем последний)
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]); // Перемещаем опорный элемент на свое место

    int pivotIndex = i + 1;
    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
}

// Функция для вычисления минимального времени разгрузки всех самолётов
int min_time_to_unload_all_planes(int n, int l, vector<int>& flight_times) {
    quickSort(flight_times, 0, n - 1); // Сортируем массив

    int current_time = 0;

    for (int flight_time : flight_times) {
        current_time = max(current_time, flight_time) + l;
    }

    return current_time;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, l;
    input >> n >> l;

    vector<int> flight_times(n);
    for (int i = 0; i < n; i++) {
        input >> flight_times[i];
    }

    int result = min_time_to_unload_all_planes(n, l, flight_times);

    output << result << "\n";

    input.close();
    output.close();

    return 0;
}

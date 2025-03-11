#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Функция перемены элементов
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(vector<int> &vec, int low, int high) {

    // Выбираем послдений элемент как pivot
    int pivot = vec[high];

    // Индекс элемента непосредственно перед последним элементом
    // Используется при смене элементов
    int i = (low - 1);

    // cout << "i = " << i << endl;

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Ставит pivot в свою позицию
    swap(vec[i + 1], vec[high]);

    // Возвращаем точку разделения
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {

        // pi - pivot элемент, он уже в правильном месте стоит
        int pi = partition(vec, low, high);

        cout << "pi = " << pi << endl;

        // Отдельно сортируем правый и левый подмассивы
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {
    vector<int> vec = {9, 8, 9, 9, 6, 4, -1};
    int n = vec.size();

    // Вызов быстрой сортировки
    quickSort(vec, 0, n - 1);

    for (auto i : vec) {
        cout << i << " ";
    }
    return 0;
}
## Merge Sort

Merge sort - алгоритм сортировки, использующий принцип "разделяй и властвуй". Он делит массив на подмассивы и сортирует каждый по отдельности, в итоге, формируя отсортированный массив.

![alt text](https://www.programiz.com/sites/tutorial2program/files/merge-sort-example_0.png)

| **Время работы** |    **Значение**     |
| :--------------: | :-----------------: |
|      Лучшее      | $O(n\times log_2n)$ |
|      Худшее      | $O(n\times log_2n)$ |
|     Среднее      | $O(n\times log_2n)$ |

Самым важной функцие в этой сортировке является **merge**(объединение). Данная функция принимает два подмассива и объединяет их в один отсортированный подмассив.

Этапы:
- Сначала вычисляем среднюю точку массива.
- Затем разделяем весь массив на равные части, используя эту среднюю точку.
- Для обоих подмассивов снова вычисляем среднюю точку.
- Далее разделяем эти два подмассива еще на две половины, пока не будет достигнут атомарный (одноэлементный) подмассив, после чего дальнейшее разделение станет невозможным.
- Начинаем объединять элементы снова, используя процесс объединения.
- В процессе объединения сравниваем элементы для каждого списка, а затем объединяем их в другой список в упорядоченном виде.

Картинки для понимания:
- Исходный массив
![alt text](https://favtutor.com/resources/images/uploads/mceu_34573520321687944867321.png)

- Находим середину массива и делим на 2 подмассива
![alt text](https://favtutor.com/resources/images/uploads/mceu_55965821531687944883953.png)

- Повторяем предыдущий пункт, пока каждый подмассив не станет одним элементом
![alt text](https://favtutor.com/resources/images/uploads/mceu_8444842941687944898528.png)

- Формируем отсортированные подмассивы путем объединения
![alt text](https://favtutor.com/resources/images/uploads/mceu_9916660651687944916761.png)

- Получив 2 **отсортированных** подмассива, объединяем их в один общий
![alt text](https://favtutor.com/resources/images/uploads/mceu_29834981461687944937593.png)

### Реализация на С++
1. Базовая реализация
```C++
#include <iostream>
#include <vector>

// Функция слияния двух отсортированных подмассивов
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Создаём временные массивы
    std::vector<int> leftArr(leftSize);
    std::vector<int> rightArr(rightSize);

    // Копируем данные во временные массивы
    for (int i = 0; i < leftSize; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < rightSize; i++) rightArr[i] = arr[mid + 1 + i];

    // Индексы для слияния
    int i = 0, j = 0, k = left;

    // Сливаем обратно в основной массив
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы
    while (i < leftSize) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Функция рекурсивной сортировки слиянием
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "Исходный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Отсортированный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
```

2. Реализация с уменьшением памяти.

В базовой реализации в функции merge создаем каждый раз новые подмассивы, вместо этого можно использовать один подмассив и передавать его ссылку.

```C++
#include <iostream>
#include <vector>

// Функция слияния двух отсортированных подмассивов
void merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    // Сливаем две половины в temp
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    // Копируем оставшиеся элементы из левой половины
    while (i <= mid) temp[k++] = arr[i++];

    // Копируем оставшиеся элементы из правой половины
    while (j <= right) temp[k++] = arr[j++];

    // Копируем отсортированные элементы обратно в arr
    for (int p = left; p <= right; p++) arr[p] = temp[p];
}

// Рекурсивная функция сортировки слиянием
void mergeSort(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    std::vector<int> temp(arr.size());  // Временный массив

    std::cout << "Исходный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    mergeSort(arr, temp, 0, arr.size() - 1);

    std::cout << "Отсортированный массив: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
```
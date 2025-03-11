## Quick Sort

Quick sort - алгоритм сортировки, который использует подход "разделяй и властвуй". Это быстрый(quick) и самый, наверное, популярный алгоритм сортировки. Использует рекурсию

| **Время работы** |    **Значение**     |
| :--------------: | :-----------------: |
|      Лучшее      | $O(n\times log_2n)$ |
|      Худшее      |      $O(n^2)$       |
|     Среднее      |     $O(log_2n)$     |

Основные этапы:

1. Делим массив на 2 подмассива, **на основе опорного элемента**(pivot).
   Pivot выбирается из массива.

При разделении массива элемент pivot должен быть расположен таким образом, чтобы элементы, меньшие, чем pivot, находились с левой стороны, а элементы, превышающие pivot, - с правой стороны от pivot.

2. 2 подмассива опять делим на подмассивы, пока каждый из них не будет состоять из **одного** элемента.

3. Все элементы отсортированы и формируется итоговый массив.

### Детальное рассмотрение алгоритма

1.  **Выбор pivot элемента.** Куча вариаций сортировки, куча вариантов выбор опорного элемента. Берем последний элемент массива и все.
    ![Выбор pivot элемента](https://www.programiz.com/sites/tutorial2program/files/quick-sort-0.1_0.png)

2.  **Перестройка массива.** Переставляем элементы массива так, чтобы элементы меньшие, чем pivot были слева, а большие справа.
    ![Перестройка массива](https://www.programiz.com/sites/tutorial2program/files/quick-sort-0.2_0.png)
    Как делать перестройку?

    1. Указатель фиксируется на pivot элементе. Pivot элемент сравнивается со всеми элементами с начала
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-first-step.png)

    2. Элемент элемент больше pivot, второй указатель устанавливается на этот элемент
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-second-step.png)

    3. Теперь pivot сравнивается дальше. Если найден элемент мешьне pivot, то он заменяется на больший, найденный ранее
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-third-step.png)

    4. Процесс повторяется, чтобы установить следующий элемент большего размера в качестве второго указателя. И заменить его другим элементом меньшего размера
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-fourth-step.png)

    5. Процесс продолжается до тех пор, пока не будет достигнут предпоследний элемент
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-fifth-step.png)

    6. В итоге, pivot меняется со вторым указателем
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-partition-sixth-step.png)

3.  **Деление подмассивов**. Для каждого подмассива выбирается свой pivot элемент и шаг 2 повторяется
    ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort_1.png)

### Пример

Отсортировать массив {8, 7, 6, 1, 0, 9, 2}

Картинки для понимания:

- Сортирвка правого подмассива
  ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-working.png)

- Сортировка левого подмассива
  ![alt text](https://www.programiz.com/sites/tutorial2program/files/quick-sort-1.png)

### Реализация на С++

```C++
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

```

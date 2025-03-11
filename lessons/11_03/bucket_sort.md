## Bucket Sort

Сортировка по ведрам - метод сортировки, который позволяет поделить элементы на некоторые группы или **ведра**.

После того, как все элементы положены в ведра, используем любой метод сортировки(Quick, Bubble и т.д.) в каждом ведре.

В конечном итоге, все отсортированные ведра собираются вместе, получая отсортированную последовательность.

"При карманной сортировке предполагается, что входные данные равномерно распределены на отрезке $[0, 1)$." - Wikipedia

Приемущества:

- Эффективен для равномерно распределенных данных
- Понятен в реализации
- Эффективно обрабатывает большие наборы данных

Недостатки:

- Не подходит для данных, которые сильно искажены или имеют высокий разброс
- Производительность сортировки зависит от выбора количества ведер и распределения входных данных

| **Время работы** | **Значение** |
| :--------------: | :----------: |
|      Лучшее      |   O(n + k)   |
|      Худшее      |   $O(n^2)$   |
|     Среднее      |     O(n)     |

![Визуализация работы](https://www.programiz.com/sites/tutorial2program/files/Bucket_2.png)

### Пример

Надо отсортировать массив {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51}

1. **Дан массив.**
   ![Массив](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0.1_0.png)

2. **Создаем n ведер(например 10).**
   ![Ведра](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0_0.png)

3. **Заполняем ведра. **
   ![Заполняем ведра](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0.2_0.png)

Чтобы узнать индекс ведра для каждого элемента массива, нужно умножить его на n и конвертировать в int.

Пример для 0.23:

- n = 10
- $0.23 \times 10 = 2.3$
- 2.3 в inte $\approx$ 2
- 0.23 попадет в ведро с индексом 2

Остальные числа по такому же принципу попадут в свои ведра:
![Готовые ведра](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0.3_0.png)

4. **Сортируем каждое ведро.**
   ![Отсортированные ведра](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0.4_0.png)

5. **Объединяем все ведра в один массив.**
   ![Объединение](https://www.programiz.com/sites/tutorial2program/files/Bucket-sort-0.5_0.png)

### Реализация на С++

1. Реализация сортировки чисел от 0 до 1

```C++
#include <iostream>
#include <vector>
#include <algorithm>

void bucketSort(std::vector<double>& arr) {
    int n = arr.size();
    if (n <= 1) return; // Нечего сортировать

    // Создаём n пустых корзин
    std::vector<std::vector<double>> buckets(n);

    // Распределяем элементы по корзинам
    for (double num : arr) {
        int bucketIndex = num * n; // Индекс корзины
        buckets[bucketIndex].push_back(num);
    }

    // Сортируем каждую корзину
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }

    // Собираем элементы обратно в массив
    int index = 0;
    for (const auto& bucket : buckets) {
        for (double num : bucket) {
            arr[index++] = num;
        }
    }
}

int main() {
    std::vector<double> arr = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};

    std::cout << "Исходный массив: ";
    for (double num : arr) std::cout << num << " ";
    std::cout << "\n";

    bucketSort(arr);

    std::cout << "Отсортированный массив: ";
    for (double num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}

```

2. Реализация сортировки целых чисел

```C++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(vector<int>& nums, int bucketSize) {
    if (nums.empty())
        return;

    // Находим минимальный и максимальный элемент
    int minValue = *min_element(nums.begin(), nums.end());
    int maxValue = *max_element(nums.begin(), nums.end());

    // Инициализация ведер
    int numBuckets = (maxValue - minValue) / bucketSize + 1;
    vector<vector<int>> buckets(numBuckets);

    // Разделяем данные по ведрам
    for (int num : nums) {
        int bucketIndex = (num - minValue) / bucketSize;
        buckets[bucketIndex].push_back(num);
    }

    // Сортируем каждое ведро и соединяем в массив
    nums.clear();
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        nums.insert(nums.end(), bucket.begin(), bucket.end());
    }
}

// Применение
int main() {
    vector<int> data = {42, 32, 33, 52, 37, 47, 51};
    bucketSort(data, 5);
    for (int num : data) {
        cout << num << " ";
    }
    // Вывод: 32 33 37 42 47 51 52
    return 0;
}
```

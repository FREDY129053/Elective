// Не совсем перевод конечно)
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для разделения массива
int partition(vector<string>& arr, int low, int high) {
    string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Функция быстрой сортировки
void quickSort(vector<string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bucketSortString(vector<string>& arr) {
    if (arr.empty())
        return;

    // Создаем пустые ведра для букв A-Z
    vector<vector<string>> buckets(26);

    for (const string& str : arr) {
        // Нужно получить индекс корзины, в который будем складывать все строки для каждой буквы
        // Поскольку все символы большие буквы, то, по ASCII таблице, нужно вычитать 65(т.к. А = 65 в таблице -> в 0 ведро = А - 65) 
        int bucketIndex = int(str[0]) - 65;
        // Заполняем соответствующее ведро строками
        buckets[bucketIndex].push_back(str);
    }

    // Очищаем массив перед его заполнением
    arr.clear();

    // Сортируем каждое ведро и добавляем его элементы обратно в массив
    for (vector<string>& bucket : buckets) {
        if (!bucket.empty()) {
            quickSort(bucket, 0, bucket.size() - 1);
            arr.insert(arr.end(), bucket.begin(), bucket.end());
        }
    }
}

int main() {
    ifstream input("input.txt");
    if (!input) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    int N;
    input >> N;

    vector<string> data(N);
    for (int i = 0; i < N; i++) {
        input >> data[i];
    }
    input.close();

    bucketSortString(data);
    
    // Вывод в файл сами сделайте
    for (const string& str : data) {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}

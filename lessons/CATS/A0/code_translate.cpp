#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main() {
    std::ifstream Open("input.txt");

    // Считываем кол-во фонарей
    int count_of_lamp;
    Open >> count_of_lamp;

    // Создаем массивы
    std::vector<int> distance_from_start(count_of_lamp);
    std::vector<int> height_of_each_lamp(count_of_lamp);
    std::vector<double> uchastok_of_light(count_of_lamp * 2);
    std::vector<int> answer(100, 0);

    // Считываем расстояние от начала и высоту фонарей
    for (int i = 0; i < count_of_lamp; i++) {
        Open >> distance_from_start[i] >> height_of_each_lamp[i];
    }

    // Заполняем массив участков освещения
    for (int i = 0; i < count_of_lamp; i++) {
        uchastok_of_light[i * 2] = distance_from_start[i] - static_cast<double>(height_of_each_lamp[i]);
        uchastok_of_light[i * 2 + 1] = distance_from_start[i] + static_cast<double>(height_of_each_lamp[i]);
    }

    // Подсчет количества фонарей, освещающих каждую точку
    for (int i = 0; i < 100; ++i) {
        int count = 0;
        for (size_t j = 1; j < uchastok_of_light.size(); j += 2) {
            double start = uchastok_of_light[j - 1], stop = uchastok_of_light[j];
            if (i >= start && i < stop) {
                count++;
            }
        }
        answer[i] = count;
    }

    for (int i : answer) {
        std::cout << i << " ";  // Выводим ответ в консоль
    }

    Open.close();
    std::ofstream Close("output.txt");

    // Нахождение максимального значения в answer
    int max = -1;
    for (int i = 0; i < 100; i++) {
        if (answer[i] > max)
            max = answer[i];
    }
    Close << max;

    Close.close();

    return 0;
}

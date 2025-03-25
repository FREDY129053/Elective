#include <iostream>
#include <fstream>
#include <vector>
// #include <map>
#include <algorithm>

using namespace std;

int main() {
  ifstream input("c.in");
  ofstream output("c.out");

  int n;
  input >> n;

  vector<int> times(n);
  for (int i = 0; i < n; i++) {
    input >> times[i];
  }

  // Создаем map и заполняем ее. Ключ - номер задачи, значение - время на ее решение
  // map<int, int> tasks;  
  // for (int i = 0; i < n; i++) {
  //   tasks[i + 1] = times[i];
  // }

  /*
    У map нет возможности сортировки через std::sort. 
    Вместо это предлагают формировать массив для сортировки по данным из map или использовать другие методы, но это сложнее. 

    Поэтому сразу реализуем массив, который, по сути, реализует map, НО пригодный для сортировки
  */
  vector<pair<int, int>> tasks;
  for (int i = 0; i < n; i++) {
    tasks.push_back(make_pair(i + 1, times[i]));
  }

  // Сортируем массив по убыванию путем использования lambda-функции для сравнения пары векторов.
  sort(tasks.begin(), tasks.end(), [](const auto &a, const auto &b) { return a.second > b.second; });

  // Вывод map для дебага
  // for (auto& t : tasks) {
  //   cout << t.first << " " << t.second << endl;
  // }

  // Выводим задачи в нужном порядке(ключи map)
  for (auto& t : tasks) {
    output << t.first << " ";
  }

  input.close();
  output.close();

  return 0;
}
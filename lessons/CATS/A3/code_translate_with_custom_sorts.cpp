/* 
  Я не знаю можно ли вам использовать стандартный sort, который оптимизирован и очень хорош
  Вот тут про него написано в начале: https://habr.com/ru/articles/867176/

  Но я попросил GPT сделать Quick Sort для всех сортировок из файла с перегрузкой std::sort

  P.S. Я бы доказывал преподу, что важнее знать перегрузки std::sort, чем писать сортировки самому)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <string>

using namespace std;

// Quick Sort для сортировки попыток по времени отправки
void quickSortAttempts(vector<tuple<int, int, int, int>>& arr, int left, int right) {
    if (left >= right) return;
    
    int pivot = get<2>(arr[(left + right) / 2]); // pivot — время отправки
    int i = left, j = right;

    while (i <= j) {
        while (get<2>(arr[i]) < pivot) i++;
        while (get<2>(arr[j]) > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSortAttempts(arr, left, j);
    if (i < right) quickSortAttempts(arr, i, right);
}

// Quick Sort для сортировки команд по (решённые задачи, штрафное время, номер команды)
void quickSortTeams(vector<pair<int, unordered_map<string, int>>>& arr, int left, int right) {
    if (left >= right) return;

    auto pivot = arr[(left + right) / 2];
    int pivotSolved = pivot.second.at("solved");
    int pivotTime = pivot.second.at("total_time");
    int pivotID = pivot.first;

    int i = left, j = right;

    while (i <= j) {
        while (make_tuple(-arr[i].second.at("solved"), arr[i].second.at("total_time"), arr[i].first) <
               make_tuple(-pivotSolved, pivotTime, pivotID)) i++;
        while (make_tuple(-arr[j].second.at("solved"), arr[j].second.at("total_time"), arr[j].first) >
               make_tuple(-pivotSolved, pivotTime, pivotID)) j--;
        
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSortTeams(arr, left, j);
    if (i < right) quickSortTeams(arr, i, right);
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int C, N;
    input >> C >> N;

    vector<tuple<int, int, int, int>> attempts(N); // (team_id, problem_id, submit_time, is_accepted)
    for (int i = 0; i < N; i++) {
        int ci, pi, ti, ri;
        input >> ci >> pi >> ti >> ri;
        attempts[i] = make_tuple(ci, pi, ti, ri);
    }

    // Сортируем попытки по времени отправки
    quickSortAttempts(attempts, 0, N - 1);

    // Инициализируем информацию о командах
    unordered_map<int, unordered_map<string, int>> teams;
    for (int i = 1; i <= C; i++) {
        teams[i] = {{"solved", 0}, {"total_time", 0}};
    }

    // Обрабатываем попытки
    for (const auto& [ci, pi, ti, ri] : attempts) {
        auto& team = teams[ci];

        if (ri == 1) {
            if (team.find(to_string(pi)) == team.end()) {
                team[to_string(pi)] = ti;
                team["solved"]++;
                team["total_time"] += ti + team[to_string(pi) + "_wrong"] * 1200;
            }
        } else {
            team[to_string(pi) + "_wrong"]++;
        }
    }

    // Преобразуем вектор команд
    vector<pair<int, unordered_map<string, int>>> sorted_teams(teams.begin(), teams.end());

    // Сортируем команды по (решённые задачи, штрафное время, номер команды)
    quickSortTeams(sorted_teams, 0, sorted_teams.size() - 1);

    // Записываем результат
    for (const auto& [team_id, _] : sorted_teams) {
        output << team_id << " ";
    }
    output << "\n";

    return 0;
}

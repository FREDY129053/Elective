#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>

// Оптимизация для поиска соседей. Без нее просто проход по массиву всему и все, что валиться на тесте №58
int bisect_left(const std::vector<int>& arr, int x) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int find_nearest_exit(int pos, const std::vector<int>& exits_cords, const std::unordered_map<int, int>& people_count, int k) {
    int idx = bisect_left(exits_cords, pos);
    int left_exit = (idx > 0) ? exits_cords[idx - 1] : -1;
    int right_exit = (idx < exits_cords.size()) ? exits_cords[idx] : -1;

    if (left_exit != -1 && people_count.at(left_exit) < k) {
        return left_exit;
    }
    if (right_exit != -1 && people_count.at(right_exit) < k) {
        return right_exit;
    }
    return -1;
}

std::vector<char> redistribute_people(
    std::vector<char>& plan, 
    const std::vector<int>& exits_cords, 
    std::unordered_map<int, int>& people_on_exits, 
    int k
  ) {
    std::vector<int> overfilled, underfilled;

    // Распределяем выходы на переполненные и не заполненные
    for (const auto& t : people_on_exits) {
        int exit_pos = t.first;
        int count = t.second;
        if (count > k) {
            overfilled.push_back(exit_pos);
        } else if (count < k) {
            underfilled.push_back(exit_pos);
        }
    }

    // Сортируем, т.к. входы подаются сортированными
    std::sort(overfilled.begin(), overfilled.end());
    std::sort(underfilled.begin(), underfilled.end());

    if (overfilled.empty()) {
        return plan;  // Already correct plan
    }

    for (int exit_pos : overfilled) {
        // Считаем сколько людей "лишних" на выходе
        int excess = people_on_exits[exit_pos] - k;
        // Перестраиваем план
        for (size_t i = 0; i < plan.size(); ++i) {
            if (plan[i] == 'L' || plan[i] == 'R') {
                if (find_nearest_exit(i + 1, exits_cords, people_on_exits, k) == exit_pos) {
                    int new_exit = find_nearest_exit(i + 1, underfilled, people_on_exits, k);
                    if (new_exit != -1) {
                        plan[i] = (new_exit < i + 1) ? 'L' : 'R';
                        people_on_exits[exit_pos]--;
                        people_on_exits[new_exit]++;
                        excess--;
                        if (people_on_exits[new_exit] == k) {
                            underfilled.erase(std::remove(underfilled.begin(), underfilled.end(), new_exit), underfilled.end());
                        }
                    }
                    if (excess == 0) {
                        break;
                    }
                }
            }
        }
    }

    // Финальная проверка, что ВСЕ элементы people_on_exits не переполнены(all_of)
    return (std::all_of(people_on_exits.begin(), people_on_exits.end(), [k](const auto& pair) { return pair.second <= k; })) ? plan : std::vector<char>{'N', 'O'};
}

int main() {
    std::ifstream infile("input.txt");
    int n, m, k;
    infile >> n >> m >> k;

    std::vector<int> exits_cords(m);
    for (int i = 0; i < m; ++i) {
        infile >> exits_cords[i];
    }
    // Сортируем кординаты(на всякий случай)
    std::sort(exits_cords.begin(), exits_cords.end());

    std::vector<char> plan(n, ' ');
    for (int exit_pos : exits_cords) {
        plan[exit_pos - 1] = 'X';
    }

    std::unordered_map<int, int> people_on_exits;
    for (int exit_cord : exits_cords) {
        people_on_exits[exit_cord] = 0;
    }
    
    // Заполняем базовый план
    for (int i = 0; i < n; ++i) {
        if (plan[i] == 'X') {
            continue;
        }
        int nearest_exit = find_nearest_exit(i + 1, exits_cords, people_on_exits, k);
        if (nearest_exit == -1) {
            std::ofstream outfile("output.txt");
            outfile << "NO\n";
            return 0;
        }
        plan[i] = (nearest_exit < i + 1) ? 'L' : 'R';
        people_on_exits[nearest_exit]++;
    }

    // Перестраиваем план на нормальным
    plan = redistribute_people(plan, exits_cords, people_on_exits, k);

    std::ofstream outfile("output.txt");
    if (plan.size() == 2 && plan[0] == 'N' && plan[1] == 'O') {
        outfile << "NO\n";
    } else {
        for (char c : plan) {
            outfile << c;
        }
        outfile << "\n";
    }

    return 0;
}
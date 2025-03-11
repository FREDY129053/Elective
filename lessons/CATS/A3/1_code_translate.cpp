#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

struct Team {
    int solved = 0;
    int total_time = 0;
    std::map<int, int> first_solve;
    std::map<int, int> wrong_attempts;
};

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int C, N;
    input >> C >> N;

    std::vector<std::tuple<int, int, int, int>> attempts(N);
    for (int i = 0; i < N; ++i) {
        int ci, pi, ti, ri;
        input >> ci >> pi >> ti >> ri;
        attempts[i] = {ci, pi, ti, ri};
    }

    // Сортируем попытки по времени отправки (O(N log N))
    std::sort(attempts.begin(), attempts.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });
    
    // Создаем информацию о командах(GPT это пропустил при переводе)
    std::map<int, Team> teams;
    for (int i = 1; i < C + 1; i++) {
       teams[i] = Team();
    }

    for (const auto& attempt : attempts) {
        int ci = std::get<0>(attempt);
        int pi = std::get<1>(attempt);
        int ti = std::get<2>(attempt);
        int ri = std::get<3>(attempt);

        Team& team = teams[ci];

        if (ri == 1) { // Принято
            if (team.first_solve.find(pi) == team.first_solve.end()) {
                team.first_solve[pi] = ti;
                team.solved++;
                team.total_time += ti + team.wrong_attempts[pi] * 1200;
            }
        } else { // Отклонено
            if (team.first_solve.find(pi) == team.first_solve.end()) {
                team.wrong_attempts[pi]++;
            }
        }
    }

    // Сортируем команды по количеству решённых задач, штрафному времени, номеру команды
    std::vector<std::pair<int, Team>> sorted_teams(teams.begin(), teams.end());
    std::sort(sorted_teams.begin(), sorted_teams.end(), [](const auto& a, const auto& b) {
        if (a.second.solved != b.second.solved) return a.second.solved > b.second.solved;
        if (a.second.total_time != b.second.total_time) return a.second.total_time < b.second.total_time;
        return a.first < b.first;
    });

    for (const auto& teams : sorted_teams) {
        int team_id = std::get<0>(teams);
        auto _ = std::get<1>(teams);
        output << team_id << " ";
    }
    output << "\n";
    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int count, talk_time;
    std::cin >> count >> talk_time;

    std::vector<int> arrival_times(count);
    for (int i = 0; i < count; ++i) {
        std::cin >> arrival_times[i];
    }

    int end_talk = 0;
    for (int arrival : arrival_times) {
        int start_talk = std::max(arrival, end_talk);
        end_talk = start_talk + talk_time;
        std::cout << end_talk << std::endl;
    }

    return 0;
}

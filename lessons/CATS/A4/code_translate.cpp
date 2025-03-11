#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Soldier {
    double height;
};

long long merge_and_count(vector<Soldier>& arr, vector<Soldier>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long swaps = 0;

    while (i <= mid && j <= right) {
        if (arr[i].height >= arr[j].height) {
            temp[k++] = arr[i++];
        } else {
            swaps += (mid - i + 1);
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int i = left; i <= right; i++) arr[i] = temp[i];

    return swaps;
}

long long merge_sort_and_count(vector<Soldier>& arr, vector<Soldier>& temp, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long swaps = 0;

    swaps += merge_sort_and_count(arr, temp, left, mid);
    swaps += merge_sort_and_count(arr, temp, mid + 1, right);
    swaps += merge_and_count(arr, temp, left, mid, right);

    return swaps;
}

int main() {
    ifstream input("input.txt");
    if (!input) {
        cerr << "Error opening file" << endl;
        return EXIT_FAILURE;
    }

    int n;
    input >> n;

    vector<Soldier> arr(n);
    vector<Soldier> temp(n);

    for (int i = 0; i < n; i++) {
        string name;
        input >> arr[i].height >> name;
    }
    input.close();

    long long swaps = merge_sort_and_count(arr, temp, 0, n - 1);

    ofstream output("output.txt");
    if (!output) {
        cerr << "Error opening file" << endl;
        return EXIT_FAILURE;
    }

    output << swaps << endl;
    output.close();

    return 0;
}

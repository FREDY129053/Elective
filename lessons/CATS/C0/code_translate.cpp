/*
  Вот GPT сделал перевод задачи + я курировал функции просейки из источников, вроде ответы те же...
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class MinHeap {
private:
    vector<int> heap;
    size_t max_size;

    void heapify_down(size_t i) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;

        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (heap[i] >= heap[parent]) break;
            swap(heap[i], heap[parent]);
            i = parent;
        }
    }

public:
    MinHeap(size_t k) : max_size(k) {}

    void push(int num) {
        if (heap.size() < max_size) {
            heap.push_back(num);
            heapify_up(heap.size() - 1);
        } else if (num > heap[0]) {
            heap[0] = num;
            heapify_down(0);
        }
    }

    vector<int> get_sorted_elements() {
        sort(heap.begin(), heap.end());
        return heap;
    }
};

void max_k_elements(const string& filename) {
    ifstream infile(filename);
    ofstream outfile("output.txt");
    
    int N, K;
    infile >> N >> K;
    
    MinHeap minHeap(K);
    int num;
    for (int i = 0; i < N; i++) {
        infile >> num;
        minHeap.push(num);
    }
    
    vector<int> result = minHeap.get_sorted_elements();
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) outfile << " ";
        outfile << result[i];
    }
    outfile << "\n";
}

int main() {
    max_k_elements("input.txt");
    return 0;
}

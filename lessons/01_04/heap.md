# Куча в программировании

Куча - **полное** двоичное дерево. Понятие *полное* означает, что у каждого родителя есть 2 потомка.

У кучи есть свойства:
- Для кучи **минимумов** каждый узел имеет значение, не превышающее значений его дочерних элементов $\to$ в вершине дерева находится **минимальный** элемент.
- Для кучи **максимумов** каждый узел имеет значение, не меньше значений его дочерних элементов $\to$ в вершине дерева находится **максимальный** элемент.
- Все уровни кучи, кроме, возможно, последнего, полностью заполнены, а все узлы последнего уровня максимально левые. Таким образом заполнение производится по уровням слева направо.

![Примеры куч](https://agorinenko.github.io/data-structures-and-algorithms/img/heap_1.png)

Куча представляется и реализуется в виде **массива**.

Вот несколько функций для работы с кучей в виде массива:
- Получение индекса родителя для i-того элемента:
```c++
int get_parent(int i) {
  return (i - 1) / 2;
}
```

- Получение левого ребенка для i-Того элемента:
```c++
int get_left_child(int i) {
  return 2 * i + 1;
}
```

- Получение правого ребенка для i-Того элемента:
```c++
int get_right_child(int i) {
  return 2 * i + 2;
}
```

## Просеивание

Чтобы сохранить свойство кучи минимума/максимума при вставке или удалении элемента, то используют *просеивание*:
- **Просеивание вверх**
- **Просеивание вниз**

P.S. Куча имеет высоту $log_n$, где $n$ - кол-во элементов

### Просеивание вверх

При вставке в кучу мы запихиваем элемент тупо в конец, НО, тогда ломается свойство кучи(или может сломаться).

Для этого и нужно делать *просеивание вверх*.

Данная операция перемещает вставляемый элемент **вверх** дерева, пока не будет выполняться свойство кучи минимумов/максимумов. Поскольку высота кучи $log_n$, то сложность операции $O(log_n)$.

![Просеивание вверх](https://agorinenko.github.io/data-structures-and-algorithms/img/heap_2.png)

### Просеивание вниз

При удалении максимального/минимального или замене элемента надо восстановить порядок кучи. Для этого используют *просеивание вниз*, чтобы "погрузить" элемент вниз дерева.

- Берем самый правый в последнем ряду элемент и переносим его на место удаляемого элемента, т.е. на вершину кучи. Определяем элемент как просеиваемый.
- Если у просеиваемого элемента два сына, определяем среди них того, у которого меньший ключ. Меняем этот узел с просеиваемым если нужно.
- Если у просеиваемого элемента один сын, меняем этот узел с просеиваемым если нужно.
- Если после перестановки у просеиваемого элемента нет сыновей, то завершаем алгоритм, свойство кучи восстановлено.

![Просеивание вниз](https://agorinenko.github.io/data-structures-and-algorithms/img/heap_3.png)

## Реализация кучи в С++

```c++
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapify_down(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            
            if (left < size && heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            
            if (smallest == index) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapify_up(heap.size() - 1);
    }
    
    int extract_min() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        int min_val = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapify_down(0);
        return min_val;
    }
    
    void replace(int value) {
        if (heap.empty()) throw runtime_error("Heap is empty");
        heap[0] = value;
        heapify_down(0);
    }
    
    int get_min() const {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    void print_heap() const {
        for (int val : heap) cout << val << " ";
        cout << endl;
    }
};

int main() {
    MinHeap heap;
    
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(7);
    heap.insert(30);
    heap.insert(3);
    
    cout << "Heap: ";
    heap.print_heap();
    
    cout << "Min: " << heap.get_min() << endl;
    
    cout << "Extract Min: " << heap.extract_min() << endl;
    heap.print_heap();
    
    heap.replace(15);
    cout << "After Replace: ";
    heap.print_heap();
    
    return 0;
}
```

Выводит код:
```c++
Heap: 3 7 5 20 30 10 

Min: 3

Extract Min: 3
5 7 10 20 30 

After Replace: 7 15 10 20 30 
```
# В Питончке(зайка, имба, любимка) куча реализована через библиотеку и не надо ничего реализовывать
# Через Ctrl + Click по методу кучи можно посмотреть исходный код
import heapq

def max_k_elements(filename):
    with open(filename, 'r') as f:
        data = map(int, f.read().split())
    
    N = next(data)
    K = next(data)
    
    min_heap = []
    for num in data:
        if len(min_heap) < K:
            heapq.heappush(min_heap, num)
        elif num > min_heap[0]:
            heapq.heapreplace(min_heap, num) 

    with open("output.txt", "w") as f:
        f.write(" ".join(map(str, sorted(min_heap))) + "\n")

max_k_elements("input.txt")

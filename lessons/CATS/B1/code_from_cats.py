import bisect

def find_nearest_exit(pos, exits_cords, people_count, k):
    idx = bisect.bisect_left(exits_cords, pos)
    left_exit = exits_cords[idx - 1] if idx > 0 else None
    right_exit = exits_cords[idx] if idx < len(exits_cords) else None
    
    if left_exit is not None and people_count[left_exit] < k:
        return left_exit
    if right_exit is not None and people_count[right_exit] < k:
        return right_exit
    return None

def redistribute_people(plan, exits_cords, people_on_exits, k):
    overfilled = sorted([exit_pos for exit_pos, count in people_on_exits.items() if count > k])
    underfilled = sorted([exit_pos for exit_pos, count in people_on_exits.items() if count < k])
    
    if not overfilled:
        return plan  # Уже корректный план
    
    for exit_pos in overfilled:
        excess = people_on_exits[exit_pos] - k
        for i in range(len(plan)):
            if plan[i] in "LR" and find_nearest_exit(i + 1, exits_cords, people_on_exits, k) == exit_pos:
                new_exit = find_nearest_exit(i + 1, underfilled, people_on_exits, k)
                if new_exit:
                    plan[i] = "L" if new_exit < i + 1 else "R"
                    people_on_exits[exit_pos] -= 1
                    people_on_exits[new_exit] += 1
                    excess -= 1
                    if people_on_exits[new_exit] == k:
                        underfilled.remove(new_exit)  # Если выход заполнился, удаляем из доступных
                if excess == 0:
                    break
    
    return plan if all(count <= k for count in people_on_exits.values()) else "NO"

with open("input.txt", "r") as file:
    n, m, k = map(int, file.readline().split())
    exits_cords = sorted(map(int, file.readline().split()))

plan = ["" for _ in range(n)]
for i in exits_cords:
    plan[i - 1] = "X"

people_on_exits = {exit_cord: 0 for exit_cord in exits_cords}
for i in range(n):
    if plan[i] == "X":
        continue
    nearest_exit = find_nearest_exit(i + 1, exits_cords, people_on_exits, k)
    if nearest_exit is None:
        with open("output.txt", "w") as file:
            file.write("NO\n")
        exit()
    plan[i] = "L" if nearest_exit < i + 1 else "R"
    people_on_exits[nearest_exit] += 1

plan = redistribute_people(plan, exits_cords, people_on_exits, k)

with open("output.txt", "w") as file:
    file.write("NO\n" if plan == "NO" else "".join(plan) + "\n")
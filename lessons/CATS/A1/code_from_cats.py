def min_time_to_unload_all_planes(n, l, flight_times):
    flight_times.sort()
    
    current_time = 0
    
    for flight_time in flight_times:
        current_time = max(current_time, flight_time) + l
    
    return current_time

with open("input.txt", "r") as f:
    n, l = map(int, f.readline().split())
    flight_times = list(map(int, f.readline().split()))

result = min_time_to_unload_all_planes(n, l, flight_times)

with open("output.txt", "w") as f:
    f.write(str(result) + "\n")

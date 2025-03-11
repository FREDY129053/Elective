def main():
    with open("input.txt", "r") as file:
        C, N = map(int, file.readline().split())

        attempts = [tuple(map(int, file.readline().split())) for _ in range(N)]

    # Сортируем попытки по времени отправки(по времени от начала контеста)
    attempts.sort(key=lambda x: x[2])

    # Формируем map(словарь) для хранения информации о каждой команды
    teams = {
        i: {"solved": 0, "total_time": 0, "first_solve": {}, "wrong_attempts": {}}
        for i in range(1, C + 1)
    }

    # Расставляем попытки по командам и подсчитываем время выполнения
    for ci, pi, ti, ri in attempts:
        team = teams[ci]  # Берем нужную команду

        # Если решение верное, добавляем его в результаты, иначе увеличиваем счетчик неверных попыток
        if ri == 1:
            if pi not in team["first_solve"]:
                team["first_solve"][pi] = ti
                team["solved"] += 1
                # get(key, val) - берем значение по ключу и, если такого ключа нет еще, то возвращает val
                team["total_time"] += ti + team["wrong_attempts"].get(pi, 0) * 1200  # Штраф +20 минут
        else:
            if pi not in team["first_solve"]:
                team["wrong_attempts"][pi] = team["wrong_attempts"].get(pi, 0) + 1

    # Сортируем команды по результатам 
    sorted_teams = sorted(teams.items(), key=lambda x: (-x[1]["solved"], x[1]["total_time"], x[0]))
    # Сортируем сразу по нескольким значения: 
    # 1) Количество решенных задач в порядке убывания
    # 2) Суммарное время выполнения в порядке возрастания
    # 3) ID команды в порядке возрастания
    
    #  Массив teams.items() выглядит так:
    # [
    #   (1, {'solved': 1, 'total_time': 4300, 'first_solve': {2: 3100}, 'wrong_attempts': {2: 1}}), 
    #   (2, {'solved': 1, 'total_time': 4200, 'first_solve': {1: 4200}, 'wrong_attempts': {}}), 
    #   (3, {'solved': 0, 'total_time': 0, 'first_solve': {}, 'wrong_attempts': {}})
    # ]


    with open("output.txt", "w") as file:
        file.write(" ".join(str(team_id) for team_id, _ in sorted_teams) + "\n")


if __name__ == "__main__":
    main()

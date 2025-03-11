#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *Open = fopen("input.txt", "r");

//  считываем кол-во фонарей
    int count_of_lamp;
    fscanf(Open, "%d ", &count_of_lamp);

//  создаем массивы: на каком расстоянии каждый фонарь, высота каждого фонаря, участок который освещает каждый фонарь
    int distance_from_start[count_of_lamp];
    int height_of_each_lamp[count_of_lamp];
    double uchastok_of_light[count_of_lamp * 2];

//  создаем масси-ответ(последовательность чисел: сколько фонарей освещают)
    int answer[100];

//  считываем расстояние от начала и высоту фонарей
    for (int i = 0; i < count_of_lamp; i++)
    {
        int a, b;
        fscanf(Open, "%d %d", &a, &b);
        distance_from_start[i] = a;
        height_of_each_lamp[i] = b;
    }

//  заполняем массив участков освещения
    for (int i = 0; i < count_of_lamp*2; i++)
    {
        uchastok_of_light[i] = distance_from_start[i/2] - ((double)height_of_each_lamp[i/2]);
        uchastok_of_light[i+1] = distance_from_start[i/2] + ((double)height_of_each_lamp[i/2]);
        i++;
    }
    


    for (int i = 0; i < 100; ++i){
        int count = 0;
        for (int j = 1; j < sizeof(uchastok_of_light)/sizeof(uchastok_of_light[0]); j+=2){
            double start = uchastok_of_light[j-1], stop = uchastok_of_light[j];
            if (i >= start && i < stop)
            {
                count++;

            } else {
                count += 0;
            }
        }
        answer[i] = count;
    }

    fclose(Open);
    FILE *Close = fopen("output.txt", "w");

    int max = -1;
    for (int i = 0; i < 100; i++) {
        if (answer[i] > max)
            max = answer[i];
    }
    fprintf(Close, "%d", max);

    fclose(Close);
    printf(" ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣦⠈⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⠆⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⡅⠀⠀⠻⣿⣿⠿⠛⠋⠉⠉⠉⠀⠀⢈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⡇⠀⠀⠀⠊⠀⠀⠠⠀⠀⠐⠒⢲⠛⠻⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⡇⠀⡠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡀⠀⠂⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⣷⠀⠁⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠄⣀⣠⣼⡿⢿⠿⠟⠛⠉⢹⣿\n \
⣿⣿⣿⣿⣿⠀⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣶⣿⣿\n \
⣿⣿⣿⣿⣿⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣾⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⢠⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⣿⣿⣿⣿⣿⣿⣷⣴⣴⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n \
⠀⡖⢦⢰⠖⣦⠀⣶⠀⢲⡖⢲⡆⠀⠀⠀⡖⢲⠀⡖⠒⣶⢰⡆⣶⢰⡆⡴⢲⡄\n \
⠀⡇⠀⢸⠤⠟⢰⢻⡄⢸⡇⢸⡗⢦⠀⠀⡗⢾⠀⡷⠆⠻⣼⡇⣿⢾⡇⡇⢸⡇\n \
⠀⠷⠞⠸⠀⠀⠾⠉⠷⠸⠇⠸⠷⠞⠀⠀⠷⠾⠀⠷⠶⠀⠸⠇⠿⠸⠇⠳⠼⠃\n \ ");

    return 0;
}


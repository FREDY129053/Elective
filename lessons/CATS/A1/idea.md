## Быстрая помощь

### Условие
В городе В случилась катастрофа: неожиданно наступила зима. Чтобы облегчить судьбу жителей $В$, из города $М$ решено направить $N$ самолётов с тёплой одеждой.

Самолёты имеют различную скорость, так что самолёт номер $i$ затратит на полёт в точности $a_i$ минут. Разгрузка любого самолёта в аэропорту В занимает $L$ минут, после чего аэропорт готов к приёму следующего самолёта.

Аэропорт города $М$ большой, и способен оправлять любое необходимое количество самолётов одновременно. Аэропорт города $В$, напротив, может принимать и разгружать самолёты только по одному.

Самолёты могут взлетать в любом порядке, но не должны обгонять друг друга в воздухе, т. е. если самолёт 1 взлетел раньше самолёта 2, то и приземлиться он должен раньше.

Требуется определить минимальное время в минутах, требуемое на перелёт и разгрузку всех самолётов.

### Решение

Мы эту задачу буквально разбирали на ознакомительной паре((Та задача)[lessons/20_02/task_condition.md]).

Только тут надо (отсортировать)[lessons/11_03/quick_sort.md] еще в порядке возрастания.

Когда отсиртируем, мы получим оптимальный порядок вылета самолетов(выгоднее маленькие запускать первыми). На примере из теста можно убедиться:
- если запустим 8 первым, то время суммарное будет 28 (8 минут летит + 10 разгружается(2ой летит, пока разгружают) + 10 минут на разгрузку 2го).

Поэтому, запускаем сначала 2го(5 минут полета), а потом 1го.

Суть задачи - делать "прыжки" во времени.

- Мы не можем обслуживать самолет сразу, мы должны начать его разгружать, когда он прилетел("прыжок").

- Мы, так же, не можем разгружать 2 самолета одновременно, поэтому нужно дождаться разгрузки текущего самолета и начать разгружать новый("прыжок").

Такой прыжок реализует функция ```std::max```, которая должна принимать время полета $i$-го самолета и текущее время
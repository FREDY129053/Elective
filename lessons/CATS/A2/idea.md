## Bucket sort (LETTERS ONLY)

### Условие
Подаются $N$ строк и нужно отсортировать в лексикографическом порядке.

### Решение

Это обычная (Bucket sort)[lessons/11_03/bucket_sort.md], но с приколом при создании ведер.

У нас в английском алфавите 26 букв(A-Z), поэтому ведер делаем 26.

Но как закинуть строки, начинающиеся с определенной буквы в нужно ведро?

Есть такая таблица кодировки ASCII. Она кодирует множество символов, присваивая определенный код.

Если посмотреть в Интернете, то букве A соответствует код 65, букве B код 66 и т.д.

У нас подаются строки из больших букв(да, хоть в условии не сказано), тогда можно брать первый символ каждой строки, переводить его в ASCII код и вычитать 65 и получим индекс ведра.

Так для строки "ASS" получится:
- ```"ASS"[0]``` = "A"
- ASCII код "A" = 65
- Индекс ведра = 65 - 65 = 0(первое ведро)

Все, дальше быстрая сортировка и все(строки можно же сравнивать), вывод ответа.
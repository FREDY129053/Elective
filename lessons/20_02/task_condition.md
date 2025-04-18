## Вова и друзья
У Вовы есть $n$ друзей, и каждый хочет поговорить с ним лично. Друзья будут приходить по очереди, а именно $i$-ый друг придет в момент времени $t_i$. Гарантируется, что для всех $1 \leq i \leq n$ выполняется условие $t_i \leq t_{i+1}$.

Каждому другу нужно $a$ минут на разговор. Вова будет разговаривать со всеми по порядку, но он не может одновременно общаться с двумя друзьями, так как разговор все-таки личный!

Определите для каждого друга, когда он закончит свой диалог с Вовой.

Обратите внимание, что Вова может начать общаться со следующим другом в тот же момент времени, когда закончил с другим. Более того, иногда друзьям придется ждать начала разговора, но **начать разговор с $i$-ым другом раньше времени $t_i$ нельзя**.
### Формат ввода
В первой строке входных данных содержаться два целых числа $n$ и $a$ $(1 \leq n \leq 100, 1 \leq a \leq 10^6)$.

Во второй строке входных данных содержится $n$ целых чисел $t_1, t_2, ..., t_n (0 \leq t_i \leq 10^6)$.
### Формат вывода
Выведите $n$ целых чисел. В $i$-й строке выведите момент времени, когда Вова закончит общаться с $i$-м другом.
### Тесты
#### Тест 1
$$
\begin{align}
	\begin{aligned}
		\text{3 4}\\
		\text{0 2 10}
	\end{aligned}
	& \quad \to \quad
	\begin{array}{c}
		\text{4}\\
		\text{8}\\
		\text{14}
	\end{array}
\end{align}
$$
#### Тест 2
$$
\begin{align}
	\begin{aligned}
		\text{3 3}\\
		\text{1 4 7}
	\end{aligned}
	& \quad \to \quad
	\begin{array}{c}
		\text{4}\\
		\text{7}\\
		\text{10}
	\end{array}
\end{align}
$$

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 300005;

vector<long long> fact(MAX), inv_fact(MAX);

// Быстрое возведение в степень
long long mod_pow(long long a, long long b) {
    long long result = 1;
    a %= MOD;
    while (b > 0) {
        if (b % 2) result = result * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return result;
}

// Факториалы и обратные факториалы
void init_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
        inv_fact[i] = mod_pow(fact[i], MOD - 2); // по модулю MOD
    }
}

// Вычисление бинома C(n, k)
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// Подсчет числа маршрутов
long long count_paths(int dx, int dy, int dz) {
    int total = dx + dy + dz;
    long long res = fact[total];
    res = res * inv_fact[dx] % MOD;
    res = res * inv_fact[dy] % MOD;
    res = res * inv_fact[dz] % MOD;
    return res;
}

int main() {
    int xM = 1;
    int yM = 1;
    int zM = 1;
    int xB = 1000;
    int yB = 1000;
    int zB = 1;

    int dx = abs(xM - xB);
    int dy = abs(yM - yB);
    int dz = abs(zM - zB);

    init_factorials();
    cout << count_paths(dx, dy, dz) << '\n';

    return 0;
}

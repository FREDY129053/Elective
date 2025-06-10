#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigNumber {
  private:
    vector<int> digits;
    bool is_negative = false;
    static const int BASE = 10;

    // Удаление незначащих нулей
    void trim() {
      while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
      }
      if (digits.size() == 1 && digits[0] == 0) {
        is_negative = false;
      }
    }
    
    static bool abs_less(const BigNumber& a, const BigNumber& b) {
      if (a.digits.size() != b.digits.size()) {
        return a.digits.size() < b.digits.size();
      }
      for (int i = a.digits.size() - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i]) {
          return a.digits[i] < b.digits[i];
        }
      }

      return false;
    }
  public:
    // Начальное значение 0
    BigNumber() { digits.push_back(0); }

    // Преобразование строки в число
    BigNumber(const string& number) {
      int start = 0;
      is_negative = false;

      if (number[0] == '-') {
        is_negative = true;
        start = 1;  // Пропускаем минус, т.к. мы уже запомнили, что число отрицательное
      }

      for (int i = number.size() - 1; i >= start; --i) {
        if (!isdigit(number[i])) {
          throw invalid_argument("Все символы числа должны быть цифрами!!!");
        }
        digits.push_back(number[i] - '0');
      }
      trim();
    }
    
    // Преобразование числа в длинное число
    BigNumber(int number) {
      if (number < 0) {
        is_negative = true;
        number = -number;
      } else {
        is_negative = false;
      }

      if (number == 0) {
        digits.push_back(0);
      }

      while (number > 0) {
        digits.push_back(number % BASE);
        number /= BASE;
      }
    }

    // Преобразование длинного числа в строку
    string to_string() const {
      string result = is_negative ? "-" : "";
      for (int i = digits.size() - 1; i >= 0; --i) {
        result += ('0' + digits[i]);
      }

      return result;
    }

    // Сложение
    BigNumber operator+(const BigNumber& other) const {
      if (this->is_negative == other.is_negative) {
        BigNumber result;
        result.is_negative = this->is_negative;
        result.digits.clear();

        int carry = 0;
        size_t max_len = max(digits.size(), other.digits.size());

        for (int i = 0; i < max_len || carry; ++i) {
          int t1 = (i < digits.size()) ? digits[i] : 0;
          int t2 = (i < other.digits.size()) ? other.digits[i] : 0;
          int sum = t1 + t2 + carry;
          result.digits.push_back(sum % BASE);
          carry = sum / BASE;
        }
        result.trim();

        return result;
      } else {
        if (this->is_negative) {
          return other - (-*this);
        } else {
          return *this - (-other);
        }
      }
    }

    // Отрицание числа(унарный минус)
    BigNumber operator-() const {
      BigNumber result = *this;
      if (!(digits.size() == 1 && digits[0] == 0)) {
        result.is_negative = !is_negative;
      }

      return result;
    }

    // Вычитание чисел
    BigNumber operator-(const BigNumber& other) const {
      if (this->is_negative != other.is_negative) {
        return *this + (-other);
      }

      if (abs_less(*this, other)) {
        BigNumber result = (other - *this);
        result.is_negative = !this->is_negative;
        return result;
      }

      BigNumber result;
      result.digits.clear();
      result.is_negative = is_negative;

      int carry = 0;
      for (int i = 0; i < digits.size(); ++i) {
        int t1 = digits[i];
        int t2 = (i < other.digits.size()) ? other.digits[i] : 0;
        int sub = t1 - t2 - carry;
        if (sub < 0) {
          sub += BASE;
          carry = 1;
        } else {
          carry = 0;
        }
        result.digits.push_back(sub);
      }
      result.trim();

      return result;
    }

    // Умножение чисел
    BigNumber operator*(const BigNumber& other) const {
      BigNumber result;
      result.digits.assign(digits.size() + other.digits.size(), 0);
      result.is_negative = is_negative != other.is_negative;

      for (int i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (int j = 0; j < other.digits.size() || carry; ++j) {
          long long mul = result.digits[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
          result.digits[i + j] = int(mul % BASE);
          carry = int(mul / BASE);
        }
      }
      result.trim();

      return result;
    }

    // Деление чисел
    BigNumber operator/(const BigNumber& other) const {
      if (other == BigNumber(0)) {
        throw runtime_error("Деление на ноль нельзя, неуч! INF будет");
      }

      BigNumber divined = *this;
      BigNumber divisor = other;
      divined.is_negative = divisor.is_negative = false;

      BigNumber result, current;
      result.digits.resize(digits.size());

      for (int i = digits.size() - 1; i >= 0; --i) {
        current.digits.insert(current.digits.begin(), digits[i]);
        current.trim();
        int x = 0, l = 0, r = 9;

        while (l <= r) {
          int m = (l + r) / 2;
          BigNumber t = divisor * m;
          if (t <= current) {
            x = m;
            l = m + 1;
          } else {
            r = m - 1;
          }
        }

        result.digits[i] = x;
        current = current - (divisor * x);
      }

      result.is_negative = is_negative != other.is_negative;
      result.trim();

      return result;
    }

    // Остаток от деления
    BigNumber operator%(const BigNumber& other) const {
      if (other == BigNumber(0))
          throw std::runtime_error("На 0 нельзя");

      BigNumber quotient = *this / other;
      BigNumber remainder = *this - (quotient * other);

      if (remainder.is_negative) {
          remainder = remainder + other;
      }

      return remainder;
    }
    
    bool operator<=(const BigNumber& other) const {
      if (is_negative != other.is_negative) {
        return is_negative;
      }

      if (digits.size() != other.digits.size()) {
        return is_negative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();
      }

      for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
          return is_negative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
      }

      return true;
    }

    bool operator==(const BigNumber& other) const {
      return is_negative == other.is_negative && digits == other.digits;
    }

    // Оператор "меньше" (<)
    bool operator<(const BigNumber& other) const {
        if (is_negative != other.is_negative) {
            return is_negative;  // Отрицательные числа меньше положительных
        }
        
        if (is_negative) {
            // Для отрицательных чисел сравнение обратное
            return abs_less(other, *this);
        } else {
            return abs_less(*this, other);
        }
    }

    // Оператор "больше" (>)
    bool operator>(const BigNumber& other) const {
        return !(*this <= other);
    }
};

ostream& operator<<(std::ostream& os, const BigNumber& num) {
  os << num.to_string();
  return os;
}

// const int MOD = 1e9;

BigNumber binom(int n, int k) {
    if (k < 0 || k > n) return BigNumber(0);
    BigNumber res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1);
        res = res / i;
    }
    return res;
}

BigNumber countWays(int A, int B, int N, int L) {
    int target = B - A;
    BigNumber total(0);

    // Перебираем количество прыжков k от 1 до N
    for (int k = 1; k <= N; ++k) {
        // Перебираем суммарную длину прыжков s от k до L
        // (минимум k прыжков по 1 дают сумму k)
        for (int s = k; s <= L; ++s) {
            // Нам нужно, чтобы сумма прыжков = target
            // и сумма модулей = s
            // Это возможно только если s >= |target|
            if (s < abs(target)) continue;

            // Количество положительных прыжков p должно удовлетворять:
            // p - (k - p) = target => 2p = target + k => p = (target + k)/2
            if ((target + k) % 2 != 0) continue;
            int p = (target + k) / 2;
            if (p < 0 || p > k) continue;

            // Количество способов выбрать p положительных прыжков из k
            BigNumber choose_signs = binom(k, p);

            // Количество способов разложить s на k натуральных слагаемых
            // (по 1 на каждый прыжок) с суммой s
            BigNumber ways = binom(s - 1, k - 1);

            total = total + choose_signs * ways;
        }
    }

    // Добавляем вариант с 0 прыжками, если A == B
    if (A == B) {
        total = total + BigNumber(1);
    }

    return total;
}

// int main() {
    // int A = 0;
    // int B = 10;
    // int N = 20;
    // int L = 40;

//     int delta = B - A;
//     BigNumber total_ways = 0;

//     for (int k = 1; k <= N; ++k) {
//         for (int sum_abs = k; sum_abs <= L; ++sum_abs) {
//             if ((sum_abs + delta) % 2 != 0) continue;

//             int pos = (sum_abs + delta) / 2;
//             int neg = (sum_abs - delta) / 2;

//             if (pos < 0 || neg < 0 || pos > sum_abs || neg > sum_abs) continue;

//             // Кол-во способов выбрать положительные шаги среди k
//             BigNumber choose_signs = binom(k, pos);
//             // Кол-во способов разложить sum_abs на k положительных чисел >= 1
//             BigNumber ways = binom(sum_abs - 1, k - 1);

//             total_ways = total_ways + (choose_signs * ways);
//         }
//     }

//     cout << (total_ways % BigNumber(MOD)) << '\n';
//     cout << (total_ways) << '\n';

//     BigNumber result = countWays(A, B, N, L);
//     cout << "Total ways: " << result << endl;
//     cout << "Modulo result: " << (result % BigNumber(MOD)) << endl;
//     return 0;
// }

const int MOD = 1000000000;

// 2 tests passed
int main() {
    int A = 0;
    int B = 10;
    int N = 20;
    int L_val = 40;

    int target = B - A;

    if (abs(target) > L_val) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(2 * L_val + 1, vector<int>(L_val + 1, 0)));
    dp[0][L_val][0] = 1;

    for (int k = 1; k <= N; k++) {
        for (int d = -L_val; d <= L_val; d++) {
            for (int s_val = 0; s_val <= L_val; s_val++) {
                for (int x = -L_val; x <= L_val; x++) {
                    if (x == 0) continue;
                    int abs_x = abs(x);
                    if (abs_x > s_val) continue;
                    int s_prev = s_val - abs_x;
                    int d_prev = d - x;
                    if (d_prev < -L_val || d_prev > L_val) continue;
                    dp[k][d + L_val][s_val] = (dp[k][d + L_val][s_val] + dp[k-1][d_prev + L_val][s_prev]) % MOD;
                }
            }
        }
    }

    int total = 0;
    for (int k = 0; k <= N; k++) {
        for (int s_val = 0; s_val <= L_val; s_val++) {
            if (target >= -L_val && target <= L_val) {
                total = (total + dp[k][target + L_val][s_val]) % MOD;
            }
        }
    }

    cout << total << endl;
    return 0;
}

// int main() {
//   int A = 0;
//   int B = 10;
//   int N = 20;
//   int L = 40;

//   int count = 0;
//   for (int x = 0; x <= L; x++) {
//     for (int y = 0; y <= L; y++) {
//       if (A + x - y == B) {
//         count++;
//       }
//     }
//   }
//   cout << count;
// }
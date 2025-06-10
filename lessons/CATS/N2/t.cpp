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

};

ostream& operator<<(std::ostream& os, const BigNumber& num) {
  os << num.to_string();
  return os;
}

const int MOD = 1e9 + 7;

BigNumber count_paths(int dx, int dy, int dz) {
    int total = dx + dy + dz;

    BigNumber fact_total = 1;
    BigNumber fact_dx = 1, fact_dy = 1, fact_dz = 1;

    for (int i = 2; i <= total; ++i) {
        fact_total = fact_total * i;
        if (i == dx) fact_dx = fact_total;
        if (i == dy) fact_dy = fact_total;
        if (i == dz) fact_dz = fact_total;
    }

    if (dx == 0) fact_dx = 1;
    if (dy == 0) fact_dy = 1;
    if (dz == 0) fact_dz = 1;

    return fact_total / (fact_dx * fact_dy * fact_dz);
}

// Вычисление мультиномиального коэффициента (n! / (a! b! c!))
BigNumber multinomial(int a, int b, int c) {
    int total = a + b + c;
    vector<int> numerator(total + 1, 0);
    vector<int> denominator(total + 1, 0); 

//     numerator[p] — сколько раз простое число p встречается в числителе (total!).

//     denominator[p] — сколько раз p встречается в знаменателе (a! * b! * c!).

    for (int i = 2; i <= total; ++i) {
        int n = i;
        for (int p = 2; p * p <= n; ++p) {
            while (n % p == 0) {
                numerator[p]++;
                n /= p;
            }
        }
        if (n > 1) numerator[n]++;
    }

    for (int i = 0; i <= numerator.size(); i++) {
      if (numerator[i] != 0)
        cout << i << "^" << numerator[i] << endl;
    }

    auto factorize_factorial = [&](int x) {
        for (int i = 2; i <= x; ++i) {
            int n = i;
            for (int p = 2; p * p <= n; ++p) {
                while (n % p == 0) {
                    denominator[p]++;
                    n /= p;
                }
            }
            if (n > 1) denominator[n]++;
        }
    };

    factorize_factorial(a);
    factorize_factorial(b);
    factorize_factorial(c);

    BigNumber result = 1;
    for (int p = 2; p <= total; ++p) {
        int exponent = numerator[p] - denominator[p];
        if (exponent > 0) {
            BigNumber power = 1;
            for (int i = 0; i < exponent; ++i) {
                power = power * p;
            }
            result = result * power;
        }
    }

    return result;
}

int main() {
    int xM = 1, yM = 1, zM = 1;
    int xB = 1000, yB = 1000, zB = 1;

    int dx = abs(xM - xB);
    int dy = abs(yM - yB);
    int dz = abs(zM - zB);

    // BigNumber result = count_paths(dx, dy, dz);
    BigNumber result = multinomial(dx, dy, dz);

    cout << "Exact result (BigNumber):\n" << result << "\n\n";
    cout << "Modulo result:\n" << (result % BigNumber(MOD)) << "\n";

    return 0;
}
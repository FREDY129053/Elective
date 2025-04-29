#include <iostream>
#include <string>
using namespace std;

// Двойное хэширование только для строковых ключей
const int TABLE_SIZE = 5;

struct Pair {
  string key;
  string value;
  bool occupied = false;
  bool deleted = false;

  void __repr__() {
    string boolStr = this->occupied ? "true" : "false";
    string boolStr2 = this->deleted ? "true" : "false";
    cout << "Pair(" << "key=" << this->key << ", value=" << this->value << ", occupied=" << boolStr << ", deleted=" << boolStr2 << ")" << endl << endl;
  }
};

class HashTable {
private:
    Pair* table;
    int size;
    int elements_count;

    int hash1(string key, bool is_print_info = false) {
      int sum = 0;
      for (char c : key) sum += c;

      if (is_print_info) {
        cout << "key - " << key << " | sum = " << sum << " | hash = " << sum % TABLE_SIZE << endl << endl;
      }
      return sum % size;
    }

    int hash2(string key, bool is_print_info = false) {
      int sum = 0;
      for (char c : key) sum += (c * c);

      if (is_print_info) {
        cout << "key - " << key << " | sum = " << sum << " | hash = " << sum % TABLE_SIZE << endl << endl;
      }
      
      return (sum % (size - 1)) + 1;
    }

    void resize_table() {
      cout << "RESIZE" << endl << endl;
      int prev_size = size;
      size *= 2;
      size++;
      Pair* prev_table = table;
      table = new Pair[size];
      int step = 0;

      for (int i = 0; i < prev_size; i++) {
        if (prev_table[i].occupied && !prev_table[i].deleted) {
          int hash_first = hash1(prev_table[i].key);
          int step = hash2(prev_table[i].key);
          int j = 0;

          while (table[(hash_first + j * step) % size].occupied) {
            j++;
          }

          table[(hash_first + j * step) % size] = prev_table[i];
        }
      }

      delete[] prev_table;
    }

public:
    // Конструктор
    HashTable() {
      size = TABLE_SIZE;
      table = new Pair[size];
      elements_count = 0;
    }

    // Деструктор
    ~HashTable() {
      delete[] table;
    }

    void insert(string key, string value) {
      if ((elements_count + 1) / double(size) > 0.75) {
        resize_table();
      }

      int index = hash1(key);
      int step = hash2(key);
      int i = 0;

      cout << key << " " << index << " " << step << endl;

      while (table[(index + i * step) % size].occupied && !table[(index + i * step) % size].deleted) {
        if (table[(index + i * step) % size].key == key) {
          table[(index + i * step) % size].value = value;
          return;
        }
        i++;
      }

      int final_index = (index + i * step) % size;

      if (!table[final_index].occupied || table[final_index].deleted) {
        elements_count++;
      }

      table[final_index].key = key;
      table[final_index].value = value;
      table[final_index].occupied = true;
      table[final_index].deleted = false;
    }

    string search(string key) {
      int index = hash1(key);
      int step = hash2(key);
      int i = 0;

      while (table[(index + i * step) % size].occupied) {
        int current_index = (index + i * step) % size;
        if (table[current_index].key == key && !table[current_index].deleted) {
          return table[current_index].value;
        }
        i++;
      }

      return "Not found";
    }

    bool remove(string key) {
      int index = hash1(key);
      int step = hash2(key);
      int i = 0;

      while (table[(index + i * step) % size].occupied) {
        int current_index = (index + i * step) % size;
        if (table[current_index].key == key && !table[current_index].deleted) {
          table[current_index].key = "";
          table[current_index].value = "";
          table[current_index].occupied = false;
          table[current_index].deleted = true;
          elements_count--;
          return true;
        }
        i++;
      }

      return false;
    }

    void display() {
      cout << "-----------------------------------------------" << endl;
      for (int i = 0; i < size; i++) {
        cout << "i = " << i << ": ";
        table[i].__repr__();
      }
      cout << "-----------------------------------------------" << endl;
    }
};

int main() {
    HashTable ht;
    ht.insert("apple", "яблоко");
    ht.insert("banana", "банан");
    ht.insert("grape", "виноград");

    cout << ht.search("banana") << endl;
    cout << ht.search("cherry") << endl;
    ht.display();

    ht.insert("grape", "яйца");
    ht.display();

    ht.remove("grape");
    ht.display();

    ht.insert("eappl", "один хэш0");
    ht.display();

    ht.insert("eappl", "один хэш1");
    ht.insert("pplea", "один хэш 2");
    ht.insert("pleap", "один хэш 3");
    ht.insert("leapp", "один хэш 4");
    ht.insert("epapl", "один хэш 5");
    ht.display();
}

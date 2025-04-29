#include <iostream>
#include <string>
using namespace std;

// Квадратичное пробирование только для строковых ключей
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

    int hash(string key, bool is_print_info = false) {
      int sum = 0;
      for (char c : key) sum += c;

      if (is_print_info) {
        cout << "key - " << key << " | sum = " << sum << " | hash = " << sum % TABLE_SIZE << endl << endl;
      }
      return sum % size;
    }

    void resize_table() {
      int prev_size = size;
      size *= 2;
      size++;
      Pair* prev_table = table;
      table = new Pair[size];

      for (int i = 0; i < prev_size; i++) {
        if (prev_table[i].occupied && !prev_table[i].deleted) {
          int index = hash(prev_table[i].key);
          int step = 0;
        
          while (table[(index + step * step) % size].occupied) {
            step++;
          }

          int new_index = (index + step * step) % size;
          table[new_index] = prev_table[i];
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
      /* 
        При квадратичном пробировании размер ВСЕГДА простое число
        Иначе возможен скип свободных мест и гг табличке
      */
      if ((elements_count + 1) / double(size) > 0.75) {
        resize_table();
      }

      int index = hash(key);
      int step = 0;
      
      while (table[(index + step * step) % size].occupied && !table[(index + step * step) % size].deleted) {
        if (table[(index + step * step) % size].key == key) {
          table[(index + step * step) % size].value = value;
          return;
        }
        step++;
      }

      cout << "key = " << key << endl;
      cout << "step = " << step << endl;
      cout << "index = " << index << endl;
      cout << "step ^ 2 = " << step * step << endl;
      cout << "size = " << size << endl;
      cout << "final index = " << (index + step * step) % size << endl << endl;

      int final_index = (index + step * step) % size;

      if (!table[final_index].occupied || table[final_index].deleted) {
        elements_count++;
      }

      table[final_index].key = key;
      table[final_index].value = value;
      table[final_index].occupied = true;
      table[final_index].deleted = false;
    }

    string search(string key) {
      int index = hash(key);
      int step = 0;

      while (table[(index + step * step) % size].occupied) {
        int current_index = (index + step * step) % size;

        if (!table[current_index].deleted && table[current_index].key == key) {
          return table[current_index].value;
        }

        step++;
      }

      return "Not found";
    }

    bool remove(string key) {
      int index = hash(key);
      int step = 0;

      while (table[(index + step * step) % size].occupied) {
        int current_index = (index + step * step) % size;

        if (!table[current_index].deleted && table[current_index].key == key) {
          table[index].key = "";
          table[index].value = "";
          table[index].occupied = false;
          table[current_index].deleted = true;
          elements_count--;
          return true;
        }

        step++;
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

    // cout << ht.search("banana") << endl;
    // cout << ht.search("cherry") << endl;
    // ht.display();

    ht.insert("grape", "яйца");
    // ht.display();

    ht.remove("grape");
    // ht.display();

    ht.insert("eappl", "один хэш 1");
    // ht.display();

    ht.insert("pplea", "один хэш 2");
    ht.insert("pleap", "один хэш 3");
    ht.insert("leapp", "один хэш 4");
    ht.insert("epapl", "один хэш 5");
    cout << "Inserted" << endl;
    ht.display();
}

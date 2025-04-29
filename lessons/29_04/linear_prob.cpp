#include <iostream>
#include <string>
using namespace std;

// Линейное пробирование только для строковых ключей
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

      return sum % size;
    }

    void resize_table() {
      // cout << "RESIZE" << endl << endl;
      int prev_size = size;
      size *= 2;
      Pair* prev_table = table;
      table = new Pair[size];

      for (int i = 0; i < prev_size; i++) {
        if (prev_table[i].occupied && !prev_table[i].deleted) {
          // insert(prev_table[i].key, prev_table[i].value);
          int index = hash(prev_table[i].key);
          while (table[index].occupied) {
            index = (index + 1) % size;
          }
          table[index] = prev_table[i];
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

      int index = hash(key);
      
      while (table[index].occupied && table[index].key != key) {
        index = (index + 1) % size;
      }

      if (!table[index].occupied || table[index].deleted) {
        elements_count++;
      }

      table[index].key = key;
      table[index].value = value;
      table[index].occupied = true;
      table[index].deleted = false;
      // elements_count++;
    }

    string search(string key) {
      int index = hash(key);

      while (table[index].occupied) {
        if (table[index].key == key && !table[index].deleted)
          return table[index].value;

        index = (index + 1) % size;
      }

      return "Not found";
    }

    bool remove(string key) {
      int index = hash(key);

      while (table[index].occupied) {
        if (table[index].key == key) {
          table[index].key = "";
          table[index].value = "";
          table[index].occupied = false;
          table[index].deleted = true;

          elements_count--;
          return true;
        }

        index = (index + 1) % size;
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

    ht.insert("eappl", "один хэш");
    ht.display();

    ht.insert("eappl", "один хэш");
    ht.insert("das", "один хэш");
    ht.insert("qtwyeruti", "один хэш");
    ht.insert("cbznxcbnzbcnzc", "один хэш");
    ht.display();

    ht.insert("12345", "f*uck");
    ht.insert("54321", "f*uck2");
    ht.display();
}

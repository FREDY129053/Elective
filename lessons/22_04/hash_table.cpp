#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 5;

struct Entry {
  string key;
  string value;
  bool occupied = false;
};

class HashTable {
private:
    Entry table[TABLE_SIZE];

    int hash(string key, bool is_print_info = false) {
      int sum = 0;
      for (char c : key) sum += c;

      if (is_print_info) {
        cout << "key - " << key << " | sum = " << sum << " | hash = " << sum % TABLE_SIZE << endl;
      }
      return sum % TABLE_SIZE;
    }

public:
    void insert(string key, string value) {
      int index = hash(key, true);
      
      while (table[index].occupied && table[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
      }

      table[index].key = key;
      table[index].value = value;
      table[index].occupied = true;
    }

    string search(string key) {
      int index = hash(key);

      while (table[index].occupied) {
        if (table[index].key == key)
          return table[index].value;

        index = (index + 1) % TABLE_SIZE;
      }

      return "Not found";
    }

    bool remove(string key) {
      int index = hash(key);

      while (table[index].occupied) {
        if (table[index].key == key) {
          string t;
          table[index].key = t;
          table[index].value = t;
          table[index].occupied = false;
          return true;
        }

        index = (index + 1) % TABLE_SIZE;
      }

      return false;
    }

    void display() {
      cout << "-----------------------------------------------" << endl;
      for (int i = 0; i < TABLE_SIZE; i++) {
        string t = table[i].occupied ? "True" : "False";
        cout << i << " --> " << "key = " << "'" << table[i].key << "'" << " | value = " << table[i].value << " | occupied = " << t;
        cout << endl << endl;
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
}

#include <iostream>
#include <string>
using namespace std;

// Метод цепочек только для строковых ключей
const int TABLE_SIZE = 5;

struct ListNode {
  string key;
  string value;
  ListNode* next;

  ListNode(string k, string v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    ListNode** table;
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
      ListNode** prev_table = table;
      table = new ListNode*[size];
      for (int i = 0; i < size; i++) {
        table[i] = nullptr;
      }

      for (int i = 0; i < prev_size; i++) {
        ListNode* current_node = prev_table[i];
        while (current_node) {
          int index = hash(current_node->key);
          ListNode* new_node = new ListNode(current_node->key, current_node->value);
          new_node->next = table[index];
          table[index] = new_node;

          ListNode* to_delete = current_node;
          current_node = current_node->next;
          delete to_delete;
        }
      }

      delete[] prev_table;
    }

public:
    // Конструктор
    HashTable() {
      size = TABLE_SIZE;
      elements_count = 0;

      table = new ListNode*[size];
      for (int i = 0; i < size; i++) {
        table[i] = nullptr;
      }
    }

    // Деструктор
    ~HashTable() {
      for (int i = 0; i < size; i++) {
        ListNode* curr = table[i];
        while (curr) {
          auto next = curr->next;
          delete curr;
          curr = next;
        }
      }

      delete[] table;
    }

    void insert(string key, string value) {if ((elements_count + 1) / double(size) > 0.95) {
        resize_table();
      }

      int index = hash(key);
      ListNode* curr = table[index];
      
      while (curr) {
        if (curr->key == key) {
          curr->value = value;
          return;
        }
        curr = curr->next;
      }

      ListNode* new_item = new ListNode(key, value);
      new_item->next = table[index];
      table[index] = new_item;
      elements_count = elements_count + 1;
    }

    string search(string key) {
      int index = hash(key);
      ListNode* curr = table[index];

      while (curr) {
        if (curr->key == key) {
          return curr->value;
        }
        curr = curr->next;
      }

      return "Not found";
    }

    bool remove(string key) {
      int index = hash(key);
      ListNode* curr = table[index];
      ListNode* prev = nullptr;
      
      while (curr) {
        if (curr->key == key) {
          if (prev) {
            prev->next = curr->next;
          } else {
            table[index] = curr->next;
          }

          delete curr;
          elements_count--;
          return true;
        }
        prev = curr;
        curr = curr->next;
      }

      return false;
    }

    void display() {
      for (int i = 0; i < size; i++) {
        cout << "[" << i << "]: ";
        ListNode* current = table[i];
        while (current) {
          cout << "(" << current->key << ", " << current->value << ") -> ";
          current = current->next;
        }
        cout << "nullptr\n";
      }
      cout << endl << endl;
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

    ht.insert("pplea", "один хэш 2");
    ht.insert("pleap", "один хэш 3");
    ht.insert("leapp", "один хэш 4");
    ht.insert("epapl", "один хэш 5");
    ht.display();

    cout << ht.search("leapp") << endl;
    cout << ht.search("epapl") << endl;
    cout << ht.search("pleap") << endl;
}

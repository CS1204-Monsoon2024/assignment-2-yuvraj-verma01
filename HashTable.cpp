#include <iostream>
#include <string>

class HashTable {
private:
    std::string* table;
    int table_size;
    int current_size;
    const float load_factor;
    


    int hash(int key) {
        return key % table_size;
    }


    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }


    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }


    void resizeTable() {
        int old_size = table_size;
        table_size = nextPrime(2 * table_size); 
        std::string* old_table = table;
        table = new std::string[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot";
        }
        for (int i = 0; i < old_size; i++) {
            if (old_table[i] != "Empty Slot" && old_table[i] != "Deleted Slot") {  
                insert(std::stoi(old_table[i]));
            }
        }
        delete[] old_table;
    }

public:
    HashTable(int size) {
        load_factor = 0.8;
        table_size = nextPrime(size); 
        table = new std::string[table_size];
        current_size = 0;
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot";  
        }
    }

    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if ((float)current_size / table_size >= load_factor) {
            resizeTable();  
        }

        int index = hash(key);
        int i = 0;

        while (table[(index + i * i) % table_size] != "Empty Slot" && table[(index + i * i) % table_size] != "Deleted Slot") {  
            i++;
            if (i == table_size) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }

        table[(index + i * i) % table_size] = std::to_string(key); 
        current_size++;
    }


    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (table[(index + i * i) % table_size] != "Empty Slot") {  
            if (table[(index + i * i) % table_size] != "Deleted Slot" && std::stoi(table[(index + i * i) % table_size]) == key) {
                return (index + i * i) % table_size;  
            }
            i++;
            if (i == table_size) {
                break;
            }
        }
        return -1; 
    }


    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = "Deleted Slot";  
            current_size--;
        }
    }


    void printTable() {
        for (int i = 0; i < table_size; i++) {
            if (table[i] == "Empty Slot") {
                std::cout << "- ";
            } else if (table[i] == "Deleted Slot") {
                std::cout << "- ";  
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    ~HashTable() {
        delete[] table;
    }
};



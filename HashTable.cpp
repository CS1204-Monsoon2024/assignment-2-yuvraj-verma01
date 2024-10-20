#include <iostream>
#include <string>
using namespace std;

class HashTable {
private:
    string* table;
    int table_size;
    int current_size;
    double load_factor;
    


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
        string* old_table = table;
        table = new string[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot";
        }
        current_size=0;
        for (int i = 0; i < old_size; i++) {
            if (old_table[i] != "Empty Slot" && old_table[i] != "Deleted Slot") {  
                insert(stoi(old_table[i]));
            }
        }
        delete[] old_table;
    }

public:
    HashTable(int size) {
        load_factor = 0.8;
        table_size = nextPrime(size); 
        table = new string[table_size];
        current_size = 0;
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot";  
        }
    }

    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        if ((double)current_size / table_size > load_factor) {
            resizeTable();  
        }

        int index = hash(key);
        int i = 0;

        while (table[(index + i * i) % table_size] != "Empty Slot" && table[(index + i * i) % table_size] != "Deleted Slot") {  
            i++;
            if (i == table_size) {
                std::cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[(index + i * i) % table_size] = to_string(key); 
        current_size++;
    }


    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (table[(index + i * i) % table_size] != "Empty Slot") {  
            if (table[(index + i * i) % table_size] != "Deleted Slot" && stoi(table[(index + i * i) % table_size]) == key) {
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
            cout << "Element not found" << endl;
        } else {
            table[index] = "Deleted Slot";  
            current_size--;
        }
    }


    void printTable() {
        for (int i = 0; i < table_size; i++) {
            if (table[i] == "Empty Slot") {
                cout << "- ";
            } else if (table[i] == "Deleted Slot") {
                cout << "- ";  
            } else {
                cout << table[i] << " ";
            }
        }
        cout << std::endl;
    }
};

// int main(){
//     HashTable h = HashTable(3);
//     h.insert(1);
//     h.printTable();
//     h.insert(2);
//     h.printTable();
//     h.insert(3);
//     h.printTable();
//     return 0;
// };

#include <iostream>
#include <string>

class HashTable {
private:
    std::string* table; // Pointer to the hash table
    int table_size;     // Current size of the table
    int current_size;   // Current number of elements in the table
    const double load_factor; // Load factor threshold

    // Hash function: key mod table size
    int hash(int key) {
        return key % table_size;
    }

    // Check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    // Get the next prime number greater than n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Resize the table when the load factor exceeds the threshold
    void resizeTable() {
        int old_size = table_size;
        table_size = nextPrime(2 * table_size); 
        std::string* old_table = table;
        table = new std::string[table_size];

        // Initialize the new table
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot"; // Initialize new slots as empty
        }

        // Rehash existing keys
        for (int i = 0; i < old_size; i++) {
            if (old_table[i] != "Empty Slot" && old_table[i] != "Deleted Slot") {  
                insert(std::stoi(old_table[i]));
            }
        }
        delete[] old_table; // Free the old table memory
    }

public:
    // Constructor
    HashTable(int size) : load_factor(0.8), current_size(0) {
        table_size = nextPrime(size); // Set initial size to a prime number
        table = new std::string[table_size];

        // Initialize the table
        for (int i = 0; i < table_size; i++) {
            table[i] = "Empty Slot";  // Mark all slots as empty
        }
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        // Resize the table if necessary
        if ((double)current_size / table_size >= load_factor) {
            resizeTable();  
        }

        int index = hash(key);
        int i = 0;

        // Handle collisions with quadratic probing
        while (table[(index + i * i) % table_size] != "Empty Slot" && table[(index + i * i) % table_size] != "Deleted Slot") {  
            i++;
            if (i >= table_size) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }

        // Insert the key into the calculated index
        table[(index + i * i) % table_size] = std::to_string(key); 
        current_size++;
    }

    // Search for a key in the hash table
    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (table[(index + i * i) % table_size] != "Empty Slot") {  
            if (table[(index + i * i) % table_size] != "Deleted Slot" && std::stoi(table[(index + i * i) % table_size]) == key) {
                return (index + i * i) % table_size;  // Return the index where the key is found
            }
            i++;
            if (i >= table_size) {
                break;
            }
        }
        return -1; // Key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = "Deleted Slot"; // Mark the slot as deleted
            current_size--;
        }
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < table_size; i++) {
            if (table[i] == "Empty Slot") {
                std::cout << "- "; // Print empty slot
            } else if (table[i] == "Deleted Slot") {
                std::cout << "- "; // Print deleted slot as empty
            } else {
                std::cout << table[i] << " "; // Print the stored key
            }
        }
        std::cout << std::endl;
    }

    // Destructor
    ~HashTable() {
        delete[] table; // Free the table memory
    }
};


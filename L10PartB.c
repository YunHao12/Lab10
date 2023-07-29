#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 100

// Hash table structure
typedef struct HashTable {
    int size;
    int* table;
} HashTable;

// Function to initialize the hash table
void initializeHashTable(HashTable* table, int size) {
    table->size = size;
    table->table = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        table->table[i] = -1; // -1 indicates an empty slot
    }
}

// Hash function: k mod size
int hashFunction(int key, int size) {
    return key % size;
}

// Probing function: linear probing
int linearProbing(int index, int i, int size) {
    return (index + i) % size;
}

// Probing function: quadratic probing
int quadraticProbing(int index, int i, int size) {
    return (index + i * i) % size;
}

// Probing function: double hashing
int doubleHashing(int key, int i, int size) {
    int h1 = hashFunction(key, size);
    int h2 = 7 - (key % 7);
    return (h1 + i * h2) % size;
}

// Function to insert a value into the hash table using the selected probing function
void insert(HashTable* table, int value, int (*probingFunction)(int, int, int)) {
    int index = hashFunction(value, table->size);
    int i = 0;

    while (table->table[index] != -1) {
        i++;
        index = probingFunction(index, i, table->size);
    }

    table->table[index] = value;
}

// Function to print the content of the hash table
void printHashTable(const HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        printf("Slot[%d] -> ", i);
        if (table->table[i] != -1) {
            printf("%d", table->table[i]);
        }
        printf("\n");
    }
}

int main() {
    HashTable table;
    int tableSize, numValues, value;
    int probingChoice;

    printf("Table Size: ");
    scanf("%d", &tableSize);

    if (tableSize <= 0 || tableSize > MAX_TABLE_SIZE) {
        printf("Invalid table size. Please choose a value between 1 and %d\n", MAX_TABLE_SIZE);
        return 1;
    }

    initializeHashTable(&table, tableSize);

    printf("Probing Choices:\n");
    printf("1. Linear Probing\n");
    printf("2. Quadratic Probing\n");
    printf("3. Double Hashing\n");
    printf("Enter your choice (1, 2, or 3): ");
    scanf("%d", &probingChoice);

    if (probingChoice < 1 || probingChoice > 3) {
        printf("Invalid probing choice. Please choose 1, 2, or 3\n");
        return 1;
    }

    int (*probingFunction)(int, int, int);

    switch (probingChoice) {
        case 1:
            probingFunction = linearProbing;
            break;
        case 2:
            probingFunction = quadraticProbing;
            break;
        case 3:
            probingFunction = doubleHashing;
            break;
        default:
            printf("Invalid probing choice.\n");
            return 1;
    }

    printf("Number of values: ");
    scanf("%d", &numValues);

    printf("Input Values:\n");
    for (int i = 0; i < numValues; i++) {
        scanf("%d", &value);
        insert(&table, value, probingFunction);
    }

    printf("The table:\n");
    printHashTable(&table);

    free(table.table);

    return 0;
}

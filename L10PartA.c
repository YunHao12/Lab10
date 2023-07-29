#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAIN_SIZE 100

// Node structure for chaining
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Hash table structure
typedef struct HashTable {
    int size;
    Node* chain[MAX_CHAIN_SIZE];
} HashTable;

// Hash function: k mod size
int hashFunction(int key, int size) {
    return key % size;
}

// Function to insert a value into the hash table with chaining
void insert(HashTable* table, int value) {
    int index = hashFunction(value, table->size);

    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // Insert the new node at the head of the chain
    if (table->chain[index] == NULL) {
        table->chain[index] = newNode;
    } else {
        Node* current = table->chain[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the content of the hash table with chaining
void printHashTable(const HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        printf("Chain[%d] -> ", i);
        Node* current = table->chain[i];
        while (current != NULL) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    HashTable table;
    int chainSize, numValues, value;

    printf("Chain Size: ");
    scanf("%d", &chainSize);

    if (chainSize <= 0 || chainSize > MAX_CHAIN_SIZE) {
        printf("Invalid chain size. Please choose a value between 1 and %d\n", MAX_CHAIN_SIZE);
        return 1;
    }

    table.size = chainSize;

    printf("Number of values: ");
    scanf("%d", &numValues);

    printf("Input Values:\n");
    for (int i = 0; i < numValues; i++) {
        scanf("%d", &value);
        insert(&table, value);
    }

    printf("The table:\n");
    printHashTable(&table);

    return 0;
}

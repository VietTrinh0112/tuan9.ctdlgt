#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char fileName[100];
    long long fileSize;
    long long timestamp;
    struct Node* next;
} Node;

Node* head = NULL;

void StringCopy(char* begin, const char* start, size_t destSize) {
    if (begin == NULL || start == NULL) {
        return;
    }
    
    size_t i;
    for (i = 0; i < destSize - 1 && start[i] != '\0'; i++) {
        begin[i] = start[i];
    }
    
    begin[i] = '\0';
}

Node* createNode(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    StringCopy(newNode->fileName, fileName, sizeof(newNode->fileName));
    newNode->fileSize = fileSize;
    newNode->timestamp = timestamp;
    newNode->next = NULL;
    return newNode;
}

void insertFile(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = createNode(fileName, fileSize, timestamp);
    if (head == NULL || head->timestamp > timestamp) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL && current->next->timestamp < timestamp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

long long calculateTotalSize() {
    long long totalSize = 0;
    Node* current = head;
    while (current != NULL) {
        totalSize += current->fileSize;
        current = current->next;
    }

    return totalSize;
}

void printFiles() {
    Node* current = head;
    printf("Danh sach cac file:\n");
    while (current != NULL) {
        printf("File: %s, Size: %lld bytes, Timestamp: %lld\n", current->fileName, current->fileSize, current->timestamp);
        current = current->next;
    }
}

int main() {
    insertFile("file1.txt", 500000, 1609459200);
    insertFile("file2.txt", 1200000, 1609545600);
    insertFile("file3.txt", 2000000, 1609632000);
    insertFile("file4.txt", 30000000, 1609718400);

    printf("Danh sach file ban dau:\n");
    printFiles();

    printf("\nCopy file 'newfile.txt' (15MB, 05-01-2021) vao thu muc...\n");
    insertFile("newfile.txt", 15000000, 1609804800);

    printFiles();

    printf("\nTong kich thuoc cac file: %lld bytes\n", calculateTotalSize());

    printf("\nDanh sach file sau khi sao luu:\n");
    printFiles();

    printf("\nTong kich thuoc sau khi sao luu: %lld bytes\n", calculateTotalSize());

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORDS 100

typedef struct Node {
    char word[100];
    struct Node* next;
} Node;

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

Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    StringCopy(newNode->word, word, sizeof(newNode->word));  
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, char* word) {
    Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int countWord(Node* head, char* word) {
    int count = 0;
    Node* temp = head;
    
    while (temp != NULL) {
        int i = 0;
        while (word[i] != '\0' && temp->word[i] != '\0') {
            if (word[i] != temp->word[i]) {
                break;
            }
            i++;
        }

        if (word[i] == '\0' && temp->word[i] == '\0') {
            count++;
        }

        temp = temp->next;
    }
    return count;
}

void findMostFrequentWord(Node* head) {
    Node* temp = head;
    char mostFrequentWord[100];
    int maxCount = 0;

    while (temp != NULL) {
        int count = countWord(head, temp->word);
        if (count > maxCount) {
            maxCount = count;
            StringCopy(mostFrequentWord, temp->word, sizeof(mostFrequentWord));
        }
        temp = temp->next;
    }

    printf("Tu xuat hien nhieu nhat: %s\n", mostFrequentWord);
}

void removeWords(Node* head) {
    Node* temp = head;

    while (temp != NULL && temp->next != NULL) {
        int i = 0;
        while (temp->word[i] != '\0' && temp->next->word[i] != '\0') {
            if (temp->word[i] != temp->next->word[i]) {
                break;
            }
            i++;
        }

        if (temp->word[i] == '\0' && temp->next->word[i] == '\0') {
            Node* redundantNode = temp->next;
            temp->next = temp->next->next;
            free(redundantNode);
        } else {
            temp = temp->next;
        }
    }
}

int countVocabulary(Node* head) {
    Node* temp = head;
    char Words[MAX_WORDS][100];
    int Count = 0;

    while (temp != NULL) {
        int a = 1;
        for (int i = 0; i < Count; i++) {
            int j = 0;
            while (temp->word[j] != '\0' && Words[i][j] != '\0') {
                if (temp->word[j] != Words[i][j]) {
                    break;
                }
                j++;
            }

            if (temp->word[j] == '\0' && Words[i][j] == '\0') {
                a = 0;
                break;
            }
        }

        if (a) {
            StringCopy(Words[Count], temp->word, sizeof(Words[Count]));
            Count++;
        }
        temp = temp->next;
    }

    return Count;
}

void writeSentence(Node* head) {
    Node* temp = head;
    printf("Cau moi: ");
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    insertNode(&head, "xanh");
    insertNode(&head, "xanh");
    insertNode(&head, "do");
    insertNode(&head, "vang");
    insertNode(&head, "vang");

    removeWords(head);

    findMostFrequentWord(head);

    int vocabularyCount = countVocabulary(head);
    printf("So tu vung trong cau: %d\n", vocabularyCount);

    writeSentence(head);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct data
{
    int angka; // 4
    // char nama[10];      // 10
    struct data *next; // 8
} *head = NULL;

void pushHead(int angka1) {
    struct data *node = (struct data *)malloc(sizeof(struct data));
    node->angka = angka1;
    node->next = head;
    head = node;
}

void pushTail(int angka) {
    struct data *curr = head;
    while (curr->next != NULL) { // pindah selama curr->next tidak null
        curr = curr->next;
    }
    // printf("Tail: %d\n", curr->angka);
    data *node = (data *)malloc(sizeof(data));
    // printf("H:%d C:%d N:%d\n", head, curr, node);
    node->angka = angka;
    node->next = NULL;
    curr->next = node;
}

void popHead() {
    if (head != 0) { // head != NULL
        struct data *node = head;
        head = head->next;
        free(node);
    } else {
        printf("Data empty.");
    }
}

void popTail() {
    if (head != 0) {
        if (head->next == 0) { // cuma 1 data
            free(head);
            head = 0;
        } else { // lebih dari 1 data
            struct data *curr = head;
            while (curr->next->next != 0) {
                curr = curr->next;
            }
            free(curr->next);
            curr->next = 0;
        }
    } else {
        printf("Data empty.");
    }
}

void popAll() {
    while (head != 0) {
        struct data *curr = head;
        head = head->next;
        free(curr);
    }
}

void printAll() {
    struct data *curr = head;
    while (curr != 0) {
        printf("%d", curr->angka);
        if (curr->next != 0) {
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf("\n");
}

int main()
{
    // 5 -> 2 -> 10 -> NULL
    // printf("%lu\n", sizeof(struct data));
    pushHead(10);                       // 10
    pushHead(2);                        // 2 -> 10
    pushHead(5);                        // 5 -> 2 -> 10
    printf("Head: %d\n", head->angka);  // Head: 5
    popHead();                          // 2 -> 10
    printf("Head: %d\n", head->angka);  // Head: 2                
    pushTail(8);                        // 2 -> 10 -> 8
    printAll();                         // 2 -> 10 -> 8
    popTail();                          // 2 -> 10
    printAll();                         // 2 -> 10
    popAll();                           // empty
    printAll();                         // empty
    return 0;
}
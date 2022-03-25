#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    int angka;
    char nama[20];
    struct data *next;
    struct data *prev;
} *head = 0, *tail = 0;

/**
 * Print all data from head to tail
 */
void printAll() {
    struct data * node = head;
    while (node) {
        printf("%d,%s", node->angka, node->nama);
        if(node->next){
            printf(" -> ");
        }
        node = node->next;
    }
    printf("\n");
}

/**
 * Print all data from tail to head
 */
void printAllBackward() {
    struct data * node = tail;
    while (node) {
        printf("%d,%s", node->angka, node->nama);
        if(node->prev){
            printf(" -> ");
        }
        node = node->prev;
    }
    printf("\n");
}

/**
 * Create new node
 * @param angka1 
 * @param nama1 
 * @return struct data* 
 */
struct data* createNode(int angka1, char nama1[20]) {
    struct data *node = (struct data*)malloc(sizeof(struct data));
    node->angka = angka1;
    strcpy(node->nama, nama1);
    node->next = node->prev = 0;
    return node;
}

void pushHead(int angka1, char nama1[20]) {
    struct data *node = createNode(angka1, nama1);
    if (!head) { // linkedList is empty
        head = tail = node;
    } else { // linkedList is not empty
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void pushTail(int angka1, char nama1[20]) {
    struct data *node = createNode(angka1, nama1);
    if (!head) { // linkedList is empty
        head = tail = node;
    } else { // linkedList is not empty
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
}


void pushMid(int angka1, char nama1[20]) {
    if (!head) {
        head = tail = createNode(angka1, nama1);
    } else {
        if (angka1 < head->angka) {
            pushHead(angka1, nama1);
        } else if (angka1 >= tail->angka) {
            pushTail(angka1, nama1);
        } else {
            struct data *curr = head;
            while (curr->angka <= angka1) {
                curr = curr->next; 
            }
            struct data *node = createNode(angka1, nama1);
            node->next = curr;
            node->prev = curr->prev;
            curr->prev->next = node;
            curr->prev = node;
        }
    }
}

void popHead() {
    if (head) { // not empty
        if (head == tail) { // last node / only a node
            free(head);
            head = tail = 0;
        } else { // more than a node
            head = head->next;
            free(head->prev);
            head->prev = 0;
        }
    }
}

void popTail() {
    if (head) { // not empty
        if (head == tail) { // last node / only a node
            free(head);
            head = tail = 0;
        } else { // more than a node
            tail = tail->prev;
            free(tail->next);
            tail->next = 0;
        }
    }
}

void popAll() {
    while (head) {
        popHead();
    }
}

int main() {
    pushHead(7, "Budi");
    printAll(); // 7,Budi
    pushHead(5, "Ani");
    printAll(); // 5,Ani -> 7,Budi
    pushTail(12, "Yanto");
    printAll(); // 5,Ani -> 7,Budi -> 12,Yanto
    printAllBackward(); // 12,Yanto -> 7,Budi -> 5,Ani
    popHead();
    printAll(); // 7,Budi -> 12,Yanto
    popTail();
    printAll(); // 7,Budi
    popAll();
    printAll(); // empty

    pushMid(7, "Budi");
    printAll(); // 7,Budi
    pushMid(2, "Andi");
    printAll(); // 2,Andi -> 7,Budi
    pushMid(30, "Yanto");
    printAll(); // 2,Andi -> 7,Budi -> 30,Yanto
    pushMid(15, "Jeff");
    printAll(); // 2,Andi -> 7,Budi -> 15,Jeff -> 30,Yanto
    pushMid(5, "Ani");
    printAll(); // 2,Andi -> 5,Ani -> 7,Budi -> 15,Jeff -> 30,Yanto
    pushMid(15, "Jefta");
    printAll(); // 2,Andi -> 5,Ani -> 7,Budi -> 15,Jeff -> 15,Jefta -> 30,Yanto
    popAll();
    printAll(); // empty
    return 0;
}
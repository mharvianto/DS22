#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    char kata[20];
    struct data *next;
} *table[10];

int sumdigit(int k) {
    int x = 0;
    while(k > 0) {
        x += k%10;
        k /= 10;
    }
    return x;
}

int hash(char kata[20]) {
    int l = strlen(kata), t = 0;
    for (int i = 0; i < l; i++) {
        t += kata[i];
    }
    while (t >= 10) {
        t = sumdigit(t);
    }
    return t;
}

void push(int key, char kata[]) {
    struct data *node = (struct data*)malloc(sizeof(struct data));
    strcpy(node->kata, kata);
    node->next = 0;
    if (!table[key]) {
        table[key] = node;
    } else {
        struct data *temp = table[key];
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }
} 

void add(char kata[]) {
    int key = hash(kata);
    push(key, kata);
    printf("Add %d: %s\n", key, kata);
}

void find(char kata[]) {
    int key = hash(kata), i = 1;
    struct data *temp = table[key];
    while(temp) {
        if (strcmp(temp->kata, kata) == 0) {
            printf("Found %d: %s, Loop %d\n", key, kata, i);
            return;
        }
        temp = temp->next;
        i++;
    }
    printf("Not found %d: %s, Loop %d\n", key, kata, i);
}

void clear() {
    for (int i = 0; i < 10; i++) {
        struct data * node = table[i];
        while (node) {
            struct data *temp = node;
            node = node->next;
            free(temp);
        }
        table[i] = 0;
    }
}

int main() {
    add("ani");
    add("budi");
    add("kevin");
    add("jessica");
    add("indra");
    add("cleo");
    add("johan");
    find("jono");
    find("johan");
    find("kevin");
    clear();
    return 0;
}
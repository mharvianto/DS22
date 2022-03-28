#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    char kata[20];
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

struct data * createNode(char kata[]){
    struct data *node = (struct data*)malloc(sizeof(struct data));
    strcpy(node->kata, kata);
    return node;
}

void add(char kata[]) {
    int key = hash(kata);
    while (table[key]) {
        key++;
        if(key >= 10) {
            printf("Full\n");
            return;
        }
    }
    table[key] = createNode(kata);
    printf("Add %d: %s\n", key, kata);
}

void find(char kata[]) {
    int key = hash(kata), i=1;
    while(table[key]){
        if(strcmp(table[key]->kata, kata) == 0){
            printf("Found %d: %s, Loop %d\n", key, kata, i);
            return;
        }
        key++;
        i++;
    }
    printf("Not found %d: %s, Loop %d\n", key, kata, i);
}

void clear() {
    for (int i = 0; i < 10; i++) {
        if (table[i]) {
            free(table[i]);
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
    return 0;
}
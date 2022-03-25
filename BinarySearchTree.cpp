#include <stdio.h>
#include <stdlib.h>

struct data {
    int angka;
    struct data *left;
    struct data *right;
} *root = 0;

struct data *createNode(int angka) {
    struct data *node = (struct data *)malloc(sizeof(struct data));
    node->angka = angka;
    node->left = node->right = 0;
    return node;
}

struct data *push(struct data *curr, int angka) {
    if (!curr) {
        return createNode(angka);
    } else {
        if (angka < curr->angka) {
            curr->left = push(curr->left, angka);
        } else if (angka > curr->angka) {
            curr->right = push(curr->right, angka);
        } else {
            printf("Duplicate key\n");
        }
        return curr;
    }
}

void inOrder(struct data *curr) {
    if (curr) {
        inOrder(curr->left);
        printf("%d, ", curr->angka);
        inOrder(curr->right);
    }
}

void popAll(struct data *curr) {
    if(curr){
        popAll(curr->left);
        popAll(curr->right);
        free(curr);
    }
}

int main() {
    root = push(root, 1);
    root = push(root, 2);
    root = push(root, 3);
    root = push(root, 4);
    root = push(root, 5);
    inOrder(root);
    printf("\n");
    popAll(root);
    return 0;
}
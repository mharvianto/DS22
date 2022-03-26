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
        printf("push %d\n", angka);
        return createNode(angka);
    } else {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            curr->left = push(curr->left, angka);
        } else if(opt == 2) {
            curr->right = push(curr->right, angka);
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

void preOrder(struct data *curr) {
    if (curr) {
        printf("%d, ", curr->angka);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void postOrder(struct data *curr) {
    if (curr) {
        postOrder(curr->left);
        postOrder(curr->right);
        printf("%d, ", curr->angka);
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
    printf("Inorder:\n");
    inOrder(root);
    printf("\nPreorder:\n");
    preOrder(root);
    printf("\nPostorder:\n");
    postOrder(root);
    printf("\n");
    popAll(root);
    return 0;
}
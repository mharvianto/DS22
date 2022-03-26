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

struct data *rightMost(struct data *curr) {
    if (curr->right) {
        return rightMost(curr->right);
    }
    return curr;
}

struct data *pop(struct data *curr, int angka) {
    if (curr) {
        if (curr->angka == angka) {
            struct data *temp;
            if (!curr->left && !curr->left) {
                // printf("Pop %d NoChild\n", angka);
                free(curr);
                return 0;
            } else if (curr->left && curr->right) {
                temp = rightMost(curr->left);
                curr->angka = temp->angka;
                curr->left = pop(curr->left, temp->angka);
            } else if (curr->left == 0) {
                temp = curr->right;
                free(curr);
                // printf("Pop %d RightChild\n", angka);
                return temp;
            } else {
                temp = curr->left;
                free(curr);
                // printf("Pop %d LeftChild\n", angka);
                return temp;
            }
        } else if (angka < curr->angka) {
            curr->left = pop(curr->left, angka); 
        } else {
            curr->right = pop(curr->right, angka);
        }
        return curr;
    }
    return 0;
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
    root = push(root, 5);
    root = push(root, 2);
    root = push(root, 1);
    root = push(root, 3);
    root = push(root, 7);
    root = push(root, 6);
    root = push(root, 8);
    printf("Infix:\n");
    inOrder(root);
    printf("\nPrefix:\n");
    preOrder(root);
    printf("\nPostfix:\n");
    postOrder(root);
    printf("\n");
    
    printf("Pop\n");
    root = pop(root, 8);
    root = pop(root, 5);
    root = pop(root, 7);
    inOrder(root);
    printf("\n");

    popAll(root);
    return 0;
}
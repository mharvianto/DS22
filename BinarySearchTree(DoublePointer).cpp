#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
    int angka;
    struct data *left;
    struct data *right;
} *root;

struct data *createNode(int angka) {
    struct data *node = (struct data*)malloc(sizeof(struct data));
    node->angka = angka;
    node->left = node->right = 0;
    return node;
}

void push(struct data **curr, int angka) {
    if (!(*curr)) {
        *curr = createNode(angka);
    } else {
        if (angka < (*curr)->angka) {
            push(&(*curr)->left, angka);
        } else if(angka > (*curr)->angka) {
            push(&(*curr)->right, angka);
        } else {
            printf("Duplicate key\n");
        }
    }
}

struct data *rightMost(struct data *curr) {
    if (curr->right) {
        return rightMost(curr->right);
    }
    return curr;
}

void pop(struct data **curr, int angka) {
    if (*curr) {
        if ((*curr)->angka == angka) {
            struct data *temp;
            if (!(*curr)->left && !(*curr)->right) {
                // printf("Pop %d NoChild\n", angka);
                free(*curr);
                *curr = 0;
            } else if ((*curr)->left && (*curr)->right) {
                temp = rightMost((*curr)->left);
                (*curr)->angka = temp->angka; // cara ini mudah tapi tidak baik apabila size datanya besar
                pop(&(*curr)->left, temp->angka);
            } else if ((*curr)->left == 0) {
                temp = (*curr)->right;
                free(*curr);
                // printf("Pop %d RightChild\n", angka);
                *curr = temp;
            } else {
                temp = (*curr)->left;
                free(*curr);
                // printf("Pop %d LeftChild\n", angka);
                *curr = temp;
            }
        } else if (angka < (*curr)->angka) {
            pop(&(*curr)->left, angka); 
        } else {
            pop(&(*curr)->right, angka);
        }
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

void viewTree(struct data *curr, int level = 0) {
    if (curr) {
        viewTree(curr->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("%d\n", curr->angka);
        viewTree(curr->left, level + 1);
    }
}

void popAll(struct data **curr) {
    if (*curr) {
        popAll(&(*curr)->left);
        popAll(&(*curr)->right);
        free(*curr);
        *curr = 0;
    } 
}

int main() {
    for (int i = 0; i < 10; i++) {
        int angka = rand() % 111;
        push(&root, angka);
        printf("%d, ", angka);
    }
    // 46, 7, 14, 32, 73, 65, 6, 77, 50, 67,
    printf("\nInfix:\n");
    inOrder(root);
    printf("\nPrefix:\n");
    preOrder(root);
    printf("\nPostfix:\n");
    postOrder(root);
    printf("\nViewTree:\n");
    viewTree(root);
    

    printf("Pop:\n");
    pop(&root, 46);
    viewTree(root);
    printf("----------\n");
    pop(&root, 50);
    viewTree(root);
    printf("----------\n");
    pop(&root, 65);
    viewTree(root);
    // printf("\n");

    popAll(&root);
    return 0;
}
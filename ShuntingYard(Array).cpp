#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char stack[100];
int n = 0;

void push(char op) {
    stack[n++] = op;
}

char top() {
    if (n >= 1) return stack[n-1];
    return '\0';
}

char pop() {
    --n;
    return stack[n];
}

void clear() {
    n = 0;
}

int precedence(char op) {
    switch (op) {
        case '(':
        case ')': return 3;
        case '*':
        case '/': return 2;
        case '-':
        case '+': return 1;
        default: return -1;
    }
} 



char *infixToPostfix(char *infix) {
    int l = strlen(infix), k = 0;
    clear();
    char *result = (char*)malloc(100);
    for (int i = 0; i < l; i++) {
        char a = infix[i];
        if (('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z')) {
            result[k++] = a;
        } else {
            if (a == ')') {
                while(top() != '(') {
                    result[k++] = pop();
                }
                pop();
            } else {
                if(top() != '('){
                    while(precedence(top()) >= precedence(a)) {
                        result[k++] = pop();
                    }
                }
                push(a);
            }
        }
    }
    while(k < l) {
        result[k++] = pop();
    }
    result[k] = '\0';
    return result;
}

char *reverse(char *str) {
    int l = strlen(str);
    char *result = (char*)malloc(100);
    for (int i = 0; i < l; i++) {
        result[l-i-1] = str[i];
    }
    result[l] = '\0';
    return result;
}

char *infixToPrefix(char *infix) {
    char *rev = reverse(infix);
    int l = strlen(infix), k = 0;
    char *result = (char*)malloc(100);
    clear();
    for (int i = 0; i < l; i++) {
        char a = rev[i];
        if (('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z')) {
            result[k++] = a;
        } else {
            if (a == '(') {
                while(top() != ')') {
                    result[k++] = pop();
                }
                pop();
            } else {
                if(top() != ')'){
                    while(precedence(top()) > precedence(a)) {
                        result[k++] = pop();
                    }
                }
                push(a);
            }
        }
    }
    while(k < l) {
        result[k++] = pop();
    }
    result[k] = '\0';
    return reverse(result);
}

int main() {
    char infix[] = "A+(B-C)*D/(E+F)";
    /*
    A+(B-C)*D/(E+F)
    A+BC-*D/(E+F)
    A+BC-*D/EF+
    A+BC-D* /EF+
    A+BC-D*EF+/
    ABC-D*EF+/+
    */
    printf("Postfix: %s\n", infixToPostfix(infix));
    /*
    A+(B-C)*D/(E+F)
    A+-BC*D/(E+F)
    A+-BC*D/+EF
    A+*-BCD/+EF
    A+/*-BCD+EF
    +A/*-BCD+EF
    */
    printf("Prefix : %s\n", infixToPrefix(infix));
    return 0;
}
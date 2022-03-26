#include<stdio.h>
#include<string.h>

int sumAscii(char kata[20]) {
    int l = strlen(kata), t = 0;
    for (int i = 0; i < l; i++) {
        t += kata[i];
    }
    return t;
}

int midSquare(int x, int n) {
    int l = 0;
    int t = x * x, digit = 1;
    while (t > 0) {
        t /= 10;
        l++;
    }
    t = x * x;
    for (int i = 0; i < (l-n)/2; i++) {
        t /= 10;
    }
    for (int i = 0; i < n; i++) {
        digit *= 10;
    }
    return t % digit;
}

int division(int x, int n){
    return x % n;
}

int folding(int k, int n) {
    int x = 0, digit = 1;
    for (int i = 0; i < n; i++) {
        digit *= 10;
    }
    while(k > 0) {
        x += k % digit;
        k /= digit;
    }
    return x;
}

int digitExtraction(int x) { // odd
    int t = 0, i = 0, j = 1;
    while (x > 0) {
        if (i % 2 == 0) {
            t += (x % 10) * j;
            j *= 10;
        }
        x /= 10;
        i++;
    }
    return t;
}

int mirror(int x) { // odd
    int t = 0;
    while (x > 0) {
        t *= 10;
        t += (x % 10);
        x /= 10;
    }
    return t;
}

/*
0 1 2 3 4 5 6 7 8 9
a b c d e f g h i j
k l m n o p q r s t
u v w x y z
*/
char *myHash (char kata[]) {
    int l = strlen(kata);
    char result[2000];
    for (int i = 0; i < l; i++) {
        int x = kata[i];
        if ('A' <= x && x <= 'Z') {
            result[i] = ((x - 'A') % 10) + '0';
        } else if ('a' <= x && x <= 'z') {
            result[i] = ((x - 'a') % 10) + '0';
        } else {
            result[i] = x;
        }
    }
    result[l] = '\0';
    return result;
}

int main(){
    int key = sumAscii("Binus");
    printf("Sum ASCII: %d\n", key);
    printf("Square %d: %d\n", key, key * key);
    printf("Mid Square 2: %d\n", midSquare(key, 2));
    printf("Mid Square 3: %d\n", midSquare(key, 3));
    printf("Division 100: %d\n", division(key, 100));
    printf("Folding 1 digit: %d\n", folding(key, 1));
    printf("Folding 2 digit: %d\n", folding(key, 2));
    printf("Digit Extraction: %d\n", digitExtraction(key));
    printf("Digit Extraction: %d\n", digitExtraction(key * key));
    printf("Mirror: %d\n", mirror(key));
    printf("Mirror: %d\n", mirror(key * key));
    printf("MyHash: %s\n", myHash("Binus University"));
    return 0;
}
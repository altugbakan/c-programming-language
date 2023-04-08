#include <stdio.h>

int main() {
    int c, space;
    space = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!space)
                putchar(c);
        }
        
        if (c != ' ') {
            putchar(c);
        }
        
        space = c == ' ';
    }
}
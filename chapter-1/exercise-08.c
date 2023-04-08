#include <stdio.h>

int main() {
    int c, bc, tc, nl;

    bc = tc = nl = 0;

    /* use Ctrl+D to send EOF */
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++bc;
        if (c == '\t')
            ++tc;
        if (c == '\n')
            ++nl;
    }

    printf("blank: %d, tab: %d, newline: %d\n", bc, tc, nl);
}
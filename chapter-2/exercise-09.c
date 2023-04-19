#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    unsigned x = 0xAB92;

    printf("Calculating x &= (x - 1) deletes the rightmost 1-bit, as if the rightmost bit");
    printf(" is 0, the subtraction converts the rightmost and the following 0s to 1s.");
    printf(" Since all the 0s are now 1s, the calculation deletes bits until reaching a 1-bit, as the");
    printf(" converted bits are now opposite (x & ~x == 0). If the rightmost bit is 1, subtraction");
    printf(" converts it to 0, and & operation deletes the rightmost bit only, as the remaining");
    printf(" parts are equal (x & x == x).\n");

    printf("\nThe bitcount of 0x%X is %d\n", x, bitcount(x));

    return 0;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= x - 1)
        b++;

    return b;
}

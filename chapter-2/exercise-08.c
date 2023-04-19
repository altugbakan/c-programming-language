#include <stdio.h>

unsigned rightrot(unsigned x, int n);
int unsignedbits();

int main()
{
    int x = 0x12345678;

    printf("size of unsigned int: %d bits\n", unsignedbits());
    printf("x: 0x%02X\nrightrot(x, 8): 0x%02X\n", x, rightrot(x, 8));

    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    return (x >> n) | (x << (unsignedbits() - n));
}

int unsignedbits()
{
    unsigned max = ~0;
    int i;

    for (i = 0; max != 0; ++i)
    {
        max = max >> 1;
    }

    return i;
}
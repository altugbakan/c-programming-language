#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x = 0xABAB;

    printf("x: 0x%X\ninvert(x, 11, 8): 0x%X\n", x, invert(x, 11, 8));

    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p - n + 1));
}
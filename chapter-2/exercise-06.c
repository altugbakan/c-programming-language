#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    unsigned x = 0xAB, y = 0xCD;

    printf("x: 0x%X\ny: 0x%X\nsetbits(x, 7, 4, y): 0x%X\n", x, y, setbits(x, 7, 4, y));

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n) << p - n + 1)) | ((y & ~(~0 << n)) << p - n + 1);
}